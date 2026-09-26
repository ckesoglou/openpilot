import json
import shutil
from types import SimpleNamespace

import pytest
from PIL import Image

from openpilot.starpilot.common import connect_server as cs
from openpilot.starpilot.common.connect_hosts import CONNECT_SERVER_COMMA, CONNECT_SERVER_CUSTOM, CONNECT_SERVER_KONIK, CONNECT_SERVER_PARAM_KEYS
from openpilot.starpilot.common import starpilot_functions as sf


class FakeParams:
  def __init__(self, values=None):
    self.values = dict(values or {})

  def get(self, key):
    return self.values.get(key)

  def get_bool(self, key):
    return self.values.get(key) in (True, 1, "1", b"1")

  def put(self, key, value):
    self.values[key] = value

  def put_bool(self, key, value):
    self.values[key] = b"1" if value else b"0"

  def put_int(self, key, value):
    self.values[key] = int(value)

  def remove(self, key):
    self.values.pop(key, None)


class FakeThreadManager:
  def is_thread_alive(self, name):
    return False


def test_publish_maps_progress_uses_mapd_file_progress_without_synthetic_storage(monkeypatch):
  params_memory = FakeParams()
  progress = SimpleNamespace(
    active=True,
    cancelled=False,
    downloadedFiles=2,
    totalFiles=10,
    locationDetails=[],
    locations=[],
  )
  monkeypatch.setattr(sf.time, "monotonic", lambda: 110.0)

  payload = sf._publish_maps_progress(
    params_memory,
    "country:CA",
    baseline_storage_bytes=1_000,
    started_at=100.0,
    progress=progress,
    cached_estimate_bytes=800,
  )

  assert payload["storageBytes"] == 1_000
  assert payload["storageKnown"] is True
  assert payload["downloadedBytes"] == 0
  assert payload["bytesPerSecond"] == 0
  assert payload["etaSeconds"] == 40
  assert payload["estimateSource"] == "previous_additional_storage"
  assert json.loads(params_memory.get(sf.MAPS_DOWNLOAD_PROGRESS_PARAM))["storageBytes"] == 1_000


def test_reconcile_maps_storage_records_selection_delta(monkeypatch):
  params = FakeParams()
  cache = sf.load_maps_storage_cache("")
  monkeypatch.setattr(sf, "storage_bytes", lambda _path: 18_000)

  total_storage = sf._reconcile_maps_storage(
    params,
    cache,
    selected_key="country:CA",
    baseline_storage_bytes=10_000,
    total_files=80,
    updated_at="2026-08-31T00:00:00",
  )

  persisted = sf.load_maps_storage_cache(params.get(sf.MAPS_DOWNLOAD_SIZE_CACHE_PARAM))
  assert total_storage == 18_000
  assert persisted.storage_bytes == 18_000
  assert persisted.selection_estimate_bytes("country:CA") == 8_000
  assert persisted.selection_total_files("country:CA") == 80


@pytest.mark.parametrize("extension,image_format", [("jpg", "JPEG"), ("png", "PNG")])
def test_update_boot_logo_writes_agnos_jpeg_and_png(monkeypatch, tmp_path, extension, image_format):
  themes_path = tmp_path / "themes"
  custom_logo = themes_path / "bootlogos" / f"custom.{extension}"
  custom_logo.parent.mkdir(parents=True)
  Image.new("RGBA" if image_format == "PNG" else "RGB", (24, 12), (12, 34, 56, 255)).save(custom_logo, format=image_format)

  jpeg_destination = tmp_path / "usr" / "comma" / "bg.jpg"
  png_destination = tmp_path / "usr" / "comma" / "bg.png"
  jpeg_destination.parent.mkdir(parents=True)
  jpeg_destination.write_bytes(b"old jpeg")
  png_destination.write_bytes(b"old png")

  commands = []

  def fake_run_cmd(command, *_args, **_kwargs):
    commands.append(command)
    if command[0] == "findmnt":
      return "ro,relatime"
    if command[:2] == ["sudo", "cp"]:
      shutil.copy2(command[2], command[3])
    return ""

  monkeypatch.setattr(sf.HARDWARE, "get_device_type", lambda: "mici")
  monkeypatch.setattr(sf, "THEME_SAVE_PATH", themes_path)
  monkeypatch.setattr(sf, "BOOT_LOGO_JPEG_PATH", jpeg_destination)
  monkeypatch.setattr(sf, "BOOT_LOGO_PNG_PATH", png_destination)
  monkeypatch.setattr(sf, "BOOT_LOGO_MAGIC_PATH", tmp_path / "usr" / "comma" / "magic.py")
  monkeypatch.setattr(sf, "run_cmd", fake_run_cmd)

  sf.update_boot_logo(starpilot=True, selected_logo="custom")

  with Image.open(jpeg_destination) as jpeg_logo:
    assert jpeg_logo.format == "JPEG"
    assert jpeg_logo.mode == "RGB"
    assert jpeg_logo.size == (12, 24)
  with Image.open(png_destination) as png_logo:
    assert png_logo.format == "PNG"
    assert png_logo.mode == "RGB"
    assert png_logo.size == (24, 12)

  assert [command for command in commands if command[:2] == ["sudo", "mount"]] == [
    ["sudo", "mount", "-o", "remount,rw", "/"],
    ["sudo", "mount", "-o", "remount,ro,relatime", "/"],
  ]
  assert len([command for command in commands if command[:2] == ["sudo", "cp"]]) == 2


def test_update_boot_logo_does_not_create_png_on_legacy_agnos(monkeypatch, tmp_path):
  themes_path = tmp_path / "themes"
  custom_logo = themes_path / "bootlogos" / "custom.png"
  custom_logo.parent.mkdir(parents=True)
  Image.new("RGB", (24, 12), (12, 34, 56)).save(custom_logo, format="PNG")

  jpeg_destination = tmp_path / "usr" / "comma" / "bg.jpg"
  png_destination = tmp_path / "usr" / "comma" / "bg.png"
  jpeg_destination.parent.mkdir(parents=True)
  jpeg_destination.write_bytes(b"old jpeg")

  def fake_run_cmd(command, *_args, **_kwargs):
    if command[0] == "findmnt":
      return "ro,relatime"
    if command[:2] == ["sudo", "cp"]:
      shutil.copy2(command[2], command[3])
    return ""

  monkeypatch.setattr(sf.HARDWARE, "get_device_type", lambda: "tici")
  monkeypatch.setattr(sf, "THEME_SAVE_PATH", themes_path)
  monkeypatch.setattr(sf, "BOOT_LOGO_JPEG_PATH", jpeg_destination)
  monkeypatch.setattr(sf, "BOOT_LOGO_PNG_PATH", png_destination)
  monkeypatch.setattr(sf, "BOOT_LOGO_MAGIC_PATH", tmp_path / "usr" / "comma" / "magic.py")
  monkeypatch.setattr(sf, "run_cmd", fake_run_cmd)

  sf.update_boot_logo(starpilot=True, selected_logo="custom")

  with Image.open(jpeg_destination) as jpeg_logo:
    assert jpeg_logo.format == "JPEG"
    assert jpeg_logo.size == (12, 24)
  assert not png_destination.exists()


def test_update_boot_logo_rotates_legacy_stock_for_raylib(monkeypatch, tmp_path):
  stock_logo = tmp_path / "starpilot" / "assets" / "other_images" / "stock_bg.jpg"
  stock_logo.parent.mkdir(parents=True)
  Image.new("RGB", (12, 24), (12, 34, 56)).save(stock_logo, format="JPEG")

  comma_path = tmp_path / "usr" / "comma"
  jpeg_destination = comma_path / "bg.jpg"
  png_destination = comma_path / "bg.png"
  comma_path.mkdir(parents=True)
  jpeg_destination.write_bytes(b"old jpeg")
  png_destination.write_bytes(b"old png")

  def fake_run_cmd(command, *_args, **_kwargs):
    if command[0] == "findmnt":
      return "ro,relatime"
    if command[:2] == ["sudo", "cp"]:
      shutil.copy2(command[2], command[3])
    return ""

  monkeypatch.setattr(sf.HARDWARE, "get_device_type", lambda: "mici")
  monkeypatch.setattr(sf, "BASEDIR", str(tmp_path))
  monkeypatch.setattr(sf, "BOOT_LOGO_JPEG_PATH", jpeg_destination)
  monkeypatch.setattr(sf, "BOOT_LOGO_PNG_PATH", png_destination)
  monkeypatch.setattr(sf, "BOOT_LOGO_MAGIC_PATH", comma_path / "magic.py")
  monkeypatch.setattr(sf, "run_cmd", fake_run_cmd)

  sf.update_boot_logo(stock=True)

  with Image.open(jpeg_destination) as jpeg_logo:
    assert jpeg_logo.size == (12, 24)
  with Image.open(png_destination) as png_logo:
    assert png_logo.size == (24, 12)


def test_update_boot_logo_uses_landscape_jpeg_for_current_magic(monkeypatch, tmp_path):
  themes_path = tmp_path / "themes"
  custom_logo = themes_path / "bootlogos" / "custom.png"
  custom_logo.parent.mkdir(parents=True)
  Image.new("RGB", (12, 24), (12, 34, 56)).save(custom_logo, format="PNG")

  comma_path = tmp_path / "usr" / "comma"
  jpeg_destination = comma_path / "bg.jpg"
  png_destination = comma_path / "bg.png"
  magic_path = comma_path / "magic.py"
  comma_path.mkdir(parents=True)
  jpeg_destination.write_bytes(b"old jpeg")
  magic_path.write_text(f'BACKGROUND = "{jpeg_destination.as_posix()}"\n')

  def fake_run_cmd(command, *_args, **_kwargs):
    if command[0] == "findmnt":
      return "ro,relatime"
    if command[:2] == ["sudo", "cp"]:
      shutil.copy2(command[2], command[3])
    return ""

  monkeypatch.setattr(sf.HARDWARE, "get_device_type", lambda: "mici")
  monkeypatch.setattr(sf, "THEME_SAVE_PATH", themes_path)
  monkeypatch.setattr(sf, "BOOT_LOGO_JPEG_PATH", jpeg_destination)
  monkeypatch.setattr(sf, "BOOT_LOGO_PNG_PATH", png_destination)
  monkeypatch.setattr(sf, "BOOT_LOGO_MAGIC_PATH", magic_path)
  monkeypatch.setattr(sf, "run_cmd", fake_run_cmd)

  sf.update_boot_logo(starpilot=True, selected_logo="custom")

  with Image.open(jpeg_destination) as jpeg_logo:
    assert jpeg_logo.format == "JPEG"
    assert jpeg_logo.size == (24, 12)
  assert not png_destination.exists()


def test_automatic_update_requests_guarded_reboot(monkeypatch):
  params = FakeParams({
    "UpdaterState": "idle",
    "UpdaterFetchAvailable": True,
    "UpdateAvailable": False,
    "IsOnroad": False,
  })
  state_reads = 0
  update_checks = 0

  def get(key):
    nonlocal state_reads
    if key == "UpdaterState" and params.values[key] == "checking...":
      state_reads += 1
      if state_reads % 2 == 0:
        params.values[key] = "idle"
    return params.values.get(key)

  def run_cmd(command, *args, **kwargs):
    nonlocal update_checks
    if "-SIGUSR1" in command:
      update_checks += 1
      params.values["UpdaterState"] = "checking..."
      params.values["UpdaterFetchAvailable"] = update_checks == 1
    elif "-SIGHUP" in command:
      params.values["UpdateAvailable"] = True

  params.get = get
  monkeypatch.setattr(sf, "run_cmd", run_cmd)
  monkeypatch.setattr(sf.HARDWARE, "reboot", lambda: (_ for _ in ()).throw(AssertionError("direct reboot called")))

  sf.update_openpilot(FakeThreadManager(), params)

  assert params.get("DoReboot") == b"1"


def test_sync_connect_dongle_id_preserves_stock_id_before_switching(monkeypatch, tmp_path):
  monkeypatch.setattr(cs.Paths, "persist_root", staticmethod(lambda: str(tmp_path)))
  monkeypatch.setattr(cs, "get_connect_server", lambda params=None: CONNECT_SERVER_KONIK)
  monkeypatch.setattr(cs, "register", lambda **kwargs: "konik-dongle")

  params = FakeParams({"DongleId": "stock-dongle"})

  cs.sync_connect_dongle_id(params)

  assert params.get("StockDongleId") == "stock-dongle"
  assert params.get("KonikDongleId") == "konik-dongle"
  assert params.get("DongleId") == "konik-dongle"


def test_sync_connect_dongle_id_restores_stock_id_from_persist(monkeypatch, tmp_path):
  persist_root = tmp_path / "persist"
  persisted_dongle_id_path = persist_root / "comma" / "dongle_id"
  persisted_dongle_id_path.parent.mkdir(parents=True, exist_ok=True)
  persisted_dongle_id_path.write_text("stock-dongle")

  monkeypatch.setattr(cs.Paths, "persist_root", staticmethod(lambda: str(persist_root)))
  monkeypatch.setattr(cs, "get_connect_server", lambda params=None: CONNECT_SERVER_COMMA)

  params = FakeParams({
    "DongleId": "konik-dongle",
    "KonikDongleId": "konik-dongle",
  })

  cs.sync_connect_dongle_id(params)

  assert params.get("StockDongleId") == "stock-dongle"
  assert params.get("DongleId") == "stock-dongle"


def test_sync_connect_dongle_id_skips_missing_stock_backup(monkeypatch, tmp_path):
  monkeypatch.setattr(cs.Paths, "persist_root", staticmethod(lambda: str(tmp_path)))
  monkeypatch.setattr(cs, "get_connect_server", lambda params=None: CONNECT_SERVER_COMMA)

  params = FakeParams({
    "DongleId": "konik-dongle",
    "KonikDongleId": "konik-dongle",
  })

  cs.sync_connect_dongle_id(params)

  assert params.get("DongleId") == "konik-dongle"
  assert params.get("StockDongleId") is None


def test_sync_connect_dongle_id_registers_custom_server_separately(monkeypatch, tmp_path):
  monkeypatch.setattr(cs.Paths, "persist_root", staticmethod(lambda: str(tmp_path)))
  monkeypatch.setattr(cs, "get_connect_server", lambda params=None: CONNECT_SERVER_CUSTOM)
  monkeypatch.setattr(cs, "register", lambda **kwargs: "custom-dongle")

  params = FakeParams({
    "DongleId": "konik-dongle",
    "KonikDongleId": "konik-dongle",
    "StockDongleId": "stock-dongle",
  })

  cs.sync_connect_dongle_id(params)

  assert params.get("CustomDongleId") == "custom-dongle"
  assert params.get("DongleId") == "custom-dongle"
  assert params.get("KonikDongleId") == "konik-dongle"
  assert params.get("StockDongleId") == "stock-dongle"


def test_sync_connect_dongle_id_restores_stock_id_from_custom(monkeypatch, tmp_path):
  monkeypatch.setattr(cs.Paths, "persist_root", staticmethod(lambda: str(tmp_path)))
  monkeypatch.setattr(cs, "get_connect_server", lambda params=None: CONNECT_SERVER_COMMA)

  params = FakeParams({
    "DongleId": "custom-dongle",
    "CustomDongleId": "custom-dongle",
    "StockDongleId": "stock-dongle",
  })

  cs.sync_connect_dongle_id(params)

  assert params.get("DongleId") == "stock-dongle"


def test_prepare_connect_server_switch_clears_cached_konik_id():
  params = FakeParams({"KonikDongleId": "konik-dongle"})
  params_cache = FakeParams({"KonikDongleId": "konik-dongle"})

  cs.prepare_connect_server_switch(CONNECT_SERVER_KONIK, params, params_cache)

  assert params.get("ConnectServer") == CONNECT_SERVER_KONIK
  assert params.get("UseKonikServer") == b"1"
  assert params.get("KonikDongleId") is None
  assert params_cache.get("KonikDongleId") is None


def test_prepare_connect_server_switch_clears_cached_custom_id():
  params = FakeParams({"CustomDongleId": "custom-dongle", "KonikDongleId": "konik-dongle"})
  params_cache = FakeParams({"CustomDongleId": "custom-dongle"})

  cs.prepare_connect_server_switch(CONNECT_SERVER_CUSTOM, params, params_cache)

  assert params.get("ConnectServer") == CONNECT_SERVER_CUSTOM
  assert params.get("UseKonikServer") == b"0"
  assert params.get("CustomDongleId") is None
  assert params_cache.get("CustomDongleId") is None
  assert params.get("KonikDongleId") == "konik-dongle"


def test_prepare_connect_server_switch_clears_cached_stock_id():
  params = FakeParams({"DongleId": "konik-dongle"})
  params_cache = FakeParams({"DongleId": "konik-dongle"})

  cs.prepare_connect_server_switch(CONNECT_SERVER_COMMA, params, params_cache)

  assert params.get("ConnectServer") == CONNECT_SERVER_COMMA
  assert params.get("UseKonikServer") == b"0"
  assert params.get("DongleId") is None
  assert params_cache.get("DongleId") is None


@pytest.fixture
def log_root_markers(monkeypatch, tmp_path):
  markers = {CONNECT_SERVER_KONIK: tmp_path / "use_konik", CONNECT_SERVER_CUSTOM: tmp_path / "use_custom_server"}
  monkeypatch.setattr(cs, "LOG_ROOT_MARKERS", markers)
  return markers


CUSTOM_HOSTS = cs.ConnectHosts("https://api.example.com", "wss://athena.example.com", "https://connect.example.com")


def test_switch_connect_server_to_custom_writes_hosts_and_requests_reboot(log_root_markers):
  params = FakeParams({"CustomDongleId": "old-custom-dongle", "IsOnroad": b"0"})

  cs.switch_connect_server(CONNECT_SERVER_CUSTOM, params, custom_hosts=CUSTOM_HOSTS, params_cache=FakeParams())

  assert params.get("ConnectServer") == CONNECT_SERVER_CUSTOM
  assert params.get("CustomApiHost") == "https://api.example.com"
  assert params.get("CustomAthenaHost") == "wss://athena.example.com"
  assert params.get("CustomConnectHost") == "https://connect.example.com"
  assert params.get("CustomDongleId") is None
  assert params.get("DoReboot") == b"1"
  assert log_root_markers[CONNECT_SERVER_CUSTOM].is_file()
  assert not log_root_markers[CONNECT_SERVER_KONIK].exists()


def test_switch_connect_server_stores_blank_connect_host_when_it_matches_api(log_root_markers):
  params = FakeParams()
  hosts = cs.ConnectHosts("https://api.example.com", "wss://athena.example.com", "https://api.example.com")

  cs.switch_connect_server(CONNECT_SERVER_CUSTOM, params, custom_hosts=hosts, params_cache=FakeParams())

  assert params.get("CustomConnectHost") == ""


def test_switch_connect_server_moves_log_root_marker(log_root_markers):
  log_root_markers[CONNECT_SERVER_KONIK].touch()
  params = FakeParams({"ConnectServer": CONNECT_SERVER_KONIK})

  cs.switch_connect_server(CONNECT_SERVER_COMMA, params, params_cache=FakeParams())

  assert params.get("ConnectServer") == CONNECT_SERVER_COMMA
  assert not log_root_markers[CONNECT_SERVER_KONIK].exists()
  assert not log_root_markers[CONNECT_SERVER_CUSTOM].exists()


@pytest.mark.parametrize("server, values, custom_hosts", [
  (CONNECT_SERVER_KONIK, {"IsOnroad": b"1"}, None),
  (7, {}, None),
  (CONNECT_SERVER_CUSTOM, {}, None),
  (CONNECT_SERVER_KONIK, {}, CUSTOM_HOSTS),
  (CONNECT_SERVER_CUSTOM, {}, cs.ConnectHosts("https://api.example.com", "https://athena.example.com", "")),
])
def test_switch_connect_server_rejects_invalid_switches(log_root_markers, server, values, custom_hosts):
  params = FakeParams({"ConnectServer": CONNECT_SERVER_COMMA, **values})
  before = dict(params.values)

  with pytest.raises(cs.ConnectServerSwitchError):
    cs.switch_connect_server(server, params, custom_hosts=custom_hosts, params_cache=FakeParams())

  assert params.values == before
  assert not any(marker.exists() for marker in log_root_markers.values())


def test_every_dongle_id_is_protected_from_generic_writers():
  dongle_id_keys = {"DongleId", "StockDongleId", *cs.ALTERNATE_DONGLE_ID_KEYS.values()}
  assert dongle_id_keys <= CONNECT_SERVER_PARAM_KEYS
