#!/usr/bin/env python3
import os
import shutil
import threading
from openpilot.system.hardware.hw import Paths
from openpilot.common.swaglog import cloudlog
from openpilot.system.loggerd.config import get_available_bytes, get_available_percent
from openpilot.system.loggerd.uploader import listdir_by_creation
from openpilot.system.loggerd.xattr_cache import getxattr

MIN_BYTES = 5 * 1024 * 1024 * 1024
MIN_PERCENT = 10

DELETE_LAST = ['boot', 'crash']

# set by loggerd on the segment a bookmark was pressed in
PRESERVE_ATTR_NAME = 'user.preserve'
PRESERVE_ATTR_VALUE = b'1'
# set by The Galaxy on every segment of a route the user preserved
ROUTE_PRESERVE_ATTR_NAME = 'user.preserve_route'

# a bookmark keeps the segment it was pressed in, the two before it and the one after it
PRESERVE_SEGMENTS_BEFORE = 2
PRESERVE_SEGMENTS_AFTER = 1


def has_xattr(d: str, attr_name: str) -> bool:
  # read fresh on every pass, The Galaxy can add or clear flags while the deleter runs
  return getxattr(os.path.join(Paths.log_root(), d), attr_name, refresh=True) == PRESERVE_ATTR_VALUE


def has_preserve_xattr(d: str) -> bool:
  return has_xattr(d, PRESERVE_ATTR_NAME)


def preserved_segment_nums(seg_num: int) -> range:
  return range(max(0, seg_num - PRESERVE_SEGMENTS_BEFORE), seg_num + PRESERVE_SEGMENTS_AFTER + 1)


def get_preserved_segments(dirs_by_creation: list[str]) -> set[str]:
  # every bookmark window and preserved route is kept; they are deleted last, oldest first
  preserved = set()
  preserved_routes = set()
  for d in dirs_by_creation:
    route_name, _, seg_str = d.rpartition("--")

    # ignore non-segment directories
    if not route_name:
      continue
    try:
      seg_num = int(seg_str)
    except ValueError:
      continue

    if has_preserve_xattr(d):
      preserved.update(f"{route_name}--{n}" for n in preserved_segment_nums(seg_num))
    if has_xattr(d, ROUTE_PRESERVE_ATTR_NAME):
      preserved_routes.add(route_name)

  preserved.update(d for d in dirs_by_creation if d.rpartition("--")[0] in preserved_routes)
  return preserved


def deleter_thread(exit_event: threading.Event):
  while not exit_event.is_set():
    out_of_bytes = get_available_bytes(default=MIN_BYTES + 1) < MIN_BYTES
    out_of_percent = get_available_percent(default=MIN_PERCENT + 1) < MIN_PERCENT

    if out_of_percent or out_of_bytes:
      dirs = listdir_by_creation(Paths.log_root())
      preserved_dirs = get_preserved_segments(dirs)

      # remove the earliest directory we can
      for delete_dir in sorted(dirs, key=lambda d: (d in DELETE_LAST, d in preserved_dirs)):
        delete_path = os.path.join(Paths.log_root(), delete_dir)

        if any(name.endswith(".lock") for name in os.listdir(delete_path)):
          continue

        try:
          cloudlog.info(f"deleting {delete_path}")
          shutil.rmtree(delete_path)
          break
        except OSError:
          cloudlog.exception(f"issue deleting {delete_path}")
      exit_event.wait(.1)
    else:
      exit_event.wait(30)


def main():
  deleter_thread(threading.Event())


if __name__ == "__main__":
  main()
