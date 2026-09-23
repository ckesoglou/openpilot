#!/usr/bin/env bash
#
# Build StarPilot's device (larch64) binaries off-device, restore the
# `prebuilt` marker, and commit the result so a comma can run this branch
# without compiling on boot.
#
# StarPilot's C++ sources can't be compiled on the comma itself (current AGNOS
# lacks the Eigen/ZeroMQ/zstd/libusb dev headers), so binaries have to be built
# with scripts/laptop_device_build.sh and committed. This wraps that flow.
#
# Requirements on the build machine:
#   - git, with push access to the fork (for --push) and user.name/user.email set
#   - Docker (Docker Desktop, OrbStack, or Docker Engine), or Podman with
#     DOCKER_HOST pointing at the Podman API socket
#   - ~30 GB free disk (AGNOS image download + extraction + build caches)
#   - An arm64 host is strongly recommended (Apple Silicon, arm64 Linux).
#     x86_64 works through qemu emulation but is much slower; on x86_64 Linux,
#     register arm64 emulation first:
#       docker run --privileged --rm tonistiigi/binfmt --install arm64
#
# Usage:
#   scripts/build_prebuilt_commit.sh [--push]
#
# Run it from a checkout of the branch, or from anywhere with WORKDIR set to
# where the branch should be cloned. Environment overrides:
#   WORKDIR     checkout to build in (default: the repo containing this script,
#               or ~/starpilot-build/openpilot when run standalone)
#   REPO_URL    fork to clone (default: https://github.com/ckesoglou/openpilot.git)
#   BRANCH      branch to build (default: StarPilot-dev-asl-aol)
#   COMMA_HOST  comma IP/hostname; if set, copy the sysroot from the device over
#               SSH instead of downloading the AGNOS system image (~4.7 GB)
#   JOBS        parallel build jobs (default: all CPUs)

set -euo pipefail

REPO_URL="${REPO_URL:-https://github.com/ckesoglou/openpilot.git}"
BRANCH="${BRANCH:-StarPilot-dev-asl-aol}"
COMMA_HOST="${COMMA_HOST:-}"
PUSH=0

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
if [[ -z "${WORKDIR:-}" ]]; then
  if [[ -f "${SCRIPT_DIR}/laptop_device_build.sh" ]] && git -C "${SCRIPT_DIR}/.." rev-parse --git-dir >/dev/null 2>&1; then
    WORKDIR="$(cd "${SCRIPT_DIR}/.." && pwd)"
  else
    WORKDIR="${HOME}/starpilot-build/openpilot"
  fi
fi

for arg in "$@"; do
  case "${arg}" in
    --push) PUSH=1 ;;
    -h|--help) sed -n '2,33p' "${BASH_SOURCE[0]}" | sed 's/^# \{0,1\}//'; exit 0 ;;
    *) echo "Unknown argument: ${arg}" >&2; exit 1 ;;
  esac
done

step() { echo; echo "==> $*"; }
die() { echo "ERROR: $*" >&2; exit 1; }

step "Preflight checks"
command -v git >/dev/null || die "git is not installed"
if command -v docker >/dev/null; then
  docker info >/dev/null 2>&1 || die "docker CLI found but no engine reachable (start Docker, or set DOCKER_HOST for Podman)"
elif command -v podman >/dev/null; then
  podman info >/dev/null 2>&1 || die "podman found but not running (podman machine start)"
else
  die "no container runtime found (install Docker or Podman)"
fi
git config user.name >/dev/null && git config user.email >/dev/null \
  || die "set git identity first: git config --global user.name ... && git config --global user.email ..."
case "$(uname -m)" in
  arm64|aarch64) ;;
  *) echo "WARN: $(uname -m) host; the build runs under arm64 emulation and will be slow" ;;
esac

step "Preparing checkout at ${WORKDIR} (${BRANCH})"
if [[ -d "${WORKDIR}/.git" ]]; then
  cd "${WORKDIR}"
  [[ -z "$(git status --porcelain --untracked-files=no)" ]] || die "checkout has uncommitted changes; commit or stash them first"
  git fetch origin "${BRANCH}"
  git checkout "${BRANCH}"
  git merge --ff-only "origin/${BRANCH}"
else
  mkdir -p "$(dirname "${WORKDIR}")"
  git clone --single-branch -b "${BRANCH}" "${REPO_URL}" "${WORKDIR}"
  cd "${WORKDIR}"
fi
[[ -x scripts/laptop_device_build.sh ]] || die "scripts/laptop_device_build.sh missing; is this a StarPilot tree?"

step "Building the arm64 builder container image"
scripts/laptop_device_build.sh build-image

if [[ -d .comma_sysroot/usr/include && -d .comma_sysroot/system/vendor/lib64 ]]; then
  step "Reusing existing sysroot in .comma_sysroot"
elif [[ -n "${COMMA_HOST}" ]]; then
  step "Copying sysroot from comma at ${COMMA_HOST} over SSH"
  scripts/laptop_device_build.sh setup-sysroot "${COMMA_HOST}" comma 22
else
  step "Extracting sysroot from the AGNOS system image (~4.7 GB download)"
  scripts/laptop_device_build.sh setup-sysroot-agnos
fi

step "Building device binaries (this takes a while)"
if [[ -n "${JOBS:-}" ]]; then
  scripts/laptop_device_build.sh build "${JOBS}"
else
  scripts/laptop_device_build.sh build
fi

step "Verifying build output"
[[ -f prebuilt ]] || die "build finished without creating the prebuilt marker"
deleted="$(git ls-files --deleted)"
[[ -z "${deleted}" ]] || die "tracked files are missing after the build; not committing:"$'\n'"${deleted}"
for f in selfdrive/pandad/pandad system/loggerd/loggerd common/params_pyx.so; do
  [[ -f "${f}" ]] || die "expected artifact missing: ${f}"
  if command -v file >/dev/null; then
    file -b "${f}" | grep -q aarch64 || die "${f} is not an aarch64 binary: $(file -b "${f}")"
  fi
done
# This branch adds these Mazda params in common/params_keys.h; make sure the
# compiled params library knows them (otherwise the toggles silently read False).
for key in TorqueInterceptorEnabled BlendedACC ManualTransmission; do
  grep -aq "${key}" common/params_pyx.so || die "compiled params library is missing ${key}"
done
echo "OK: aarch64 binaries present, custom params compiled in"

step "Committing binaries"
git add -u
git add prebuilt
if git diff --cached --quiet; then
  echo "Nothing changed; binaries were already up to date."
else
  git diff --cached --stat | tail -1
  git commit -q -m "Compile StarPilot

Device binaries built off-device with scripts/laptop_device_build.sh and
prebuilt marker restored, so the comma runs them without compiling on boot."
  git log --oneline -1
fi

untracked="$(git status --porcelain | grep '^??' || true)"
if [[ -n "${untracked}" ]]; then
  echo "NOTE: the build left untracked files (not committed); review if any should be:"
  echo "${untracked}" | head -20
fi

if [[ "${PUSH}" == 1 ]]; then
  step "Pushing ${BRANCH}"
  git push origin "${BRANCH}"
else
  echo
  echo "Done. Push when ready:"
  echo "  git -C \"${WORKDIR}\" push origin ${BRANCH}"
fi
echo "Then on the comma (discards the failed on-device build output):"
echo "  cd /data/openpilot && git fetch origin ${BRANCH} && git reset --hard origin/${BRANCH} && sudo reboot"
