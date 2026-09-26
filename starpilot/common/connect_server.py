from pathlib import Path

from openpilot.common.params import Params
from openpilot.system.athena.registration import register
from openpilot.system.hardware.hw import Paths

from openpilot.starpilot.common.connect_hosts import (
  CONNECT_SERVER_CUSTOM, CONNECT_SERVER_KONIK, CONNECT_SERVERS, ConnectHosts, get_connect_server, get_custom_hosts, is_valid_host,
  API_SCHEMES, ATHENA_SCHEMES, CONNECT_SCHEMES,
)
from openpilot.starpilot.common.starpilot_variables import CUSTOM_SERVER_PATH, KONIK_PATH

# Each alternate server registers its own dongle ID so the stock comma one is preserved
ALTERNATE_DONGLE_ID_KEYS = {
  CONNECT_SERVER_KONIK: "KonikDongleId",
  CONNECT_SERVER_CUSTOM: "CustomDongleId",
}

LOG_ROOT_MARKERS = {
  CONNECT_SERVER_KONIK: KONIK_PATH,
  CONNECT_SERVER_CUSTOM: CUSTOM_SERVER_PATH,
}


def _cache_params_path() -> str:
  return Paths.params_cache_root()


def _normalize_dongle_id(value):
  if isinstance(value, bytes):
    value = value.decode("utf-8", errors="ignore")
  if value is None:
    return None
  value = str(value).strip()
  return value or None


def _read_persisted_stock_dongle_id():
  persisted_dongle_id_path = Path(Paths.persist_root()) / "comma" / "dongle_id"
  if not persisted_dongle_id_path.is_file():
    return None
  return _normalize_dongle_id(persisted_dongle_id_path.read_text())


def _remove_param_from_live_and_cache(key, params, params_cache=None):
  if params_cache is None:
    params_cache = Params(_cache_params_path())
  params.remove(key)
  params_cache.remove(key)


def prepare_connect_server_switch(server, params, params_cache=None):
  params.put_int("ConnectServer", server)
  # Keep the legacy toggle in sync for tools that still read it
  params.put_bool("UseKonikServer", server == CONNECT_SERVER_KONIK)

  alternate_key = ALTERNATE_DONGLE_ID_KEYS.get(server)
  if alternate_key is not None:
    _remove_param_from_live_and_cache(alternate_key, params, params_cache)
  else:
    _remove_param_from_live_and_cache("DongleId", params, params_cache)


class ConnectServerSwitchError(Exception):
  pass


def switch_connect_server(server, params, custom_hosts: ConnectHosts | None = None, params_cache=None):
  """The only supported way to change servers. Requests a reboot, since athenad, the uploader and
  registration only read the server on startup. Raises ConnectServerSwitchError if not allowed."""
  if params.get_bool("IsOnroad"):
    raise ConnectServerSwitchError("Can't change the Connect server while driving.")
  if server not in CONNECT_SERVERS:
    raise ConnectServerSwitchError("Unknown Connect server.")

  if custom_hosts is not None:
    if server != CONNECT_SERVER_CUSTOM:
      raise ConnectServerSwitchError("Custom URLs can only be set when switching to a custom server.")
    connect = custom_hosts.connect if custom_hosts.connect != custom_hosts.api else ""
    if not (is_valid_host(custom_hosts.api, API_SCHEMES) and is_valid_host(custom_hosts.athena, ATHENA_SCHEMES) and
            (not connect or is_valid_host(connect, CONNECT_SCHEMES))):
      raise ConnectServerSwitchError("Invalid custom server URLs.")
    params.put("CustomApiHost", custom_hosts.api)
    params.put("CustomAthenaHost", custom_hosts.athena)
    params.put("CustomConnectHost", connect)
  elif server == CONNECT_SERVER_CUSTOM and get_custom_hosts(params) is None:
    raise ConnectServerSwitchError("Set the custom server URLs on the device first.")

  prepare_connect_server_switch(server, params, params_cache)
  sync_log_root_markers(server)
  params.put_bool("DoReboot", True)


def sync_log_root_markers(server):
  for marker_server, marker_path in LOG_ROOT_MARKERS.items():
    try:
      if marker_server == server:
        marker_path.parent.mkdir(parents=True, exist_ok=True)
        marker_path.touch(exist_ok=True)
      else:
        marker_path.unlink(missing_ok=True)
    except OSError:
      pass


def _alternate_dongle_ids(params):
  return {_normalize_dongle_id(params.get(key)) for key in ALTERNATE_DONGLE_ID_KEYS.values()} - {None}


def _ensure_stock_dongle_id(params):
  current_dongle_id = _normalize_dongle_id(params.get("DongleId"))
  stock_dongle_id = _normalize_dongle_id(params.get("StockDongleId"))
  alternate_dongle_ids = _alternate_dongle_ids(params)

  if stock_dongle_id is not None and stock_dongle_id not in alternate_dongle_ids:
    return stock_dongle_id

  candidate = _read_persisted_stock_dongle_id()
  if candidate is None or candidate in alternate_dongle_ids:
    candidate = current_dongle_id if current_dongle_id not in alternate_dongle_ids else None

  if candidate is not None and candidate != stock_dongle_id:
    params.put("StockDongleId", candidate)

  return candidate


def sync_connect_dongle_id(params):
  current_dongle_id = _normalize_dongle_id(params.get("DongleId"))
  stock_dongle_id = _ensure_stock_dongle_id(params)

  alternate_key = ALTERNATE_DONGLE_ID_KEYS.get(get_connect_server(params))
  if alternate_key is not None:
    alternate_dongle_id = _normalize_dongle_id(params.get(alternate_key))
    if alternate_dongle_id is None:
      alternate_dongle_id = _normalize_dongle_id(register(show_spinner=True, register_alternate=True))
      if alternate_dongle_id is not None:
        params.put(alternate_key, alternate_dongle_id)
    if alternate_dongle_id is not None and current_dongle_id != alternate_dongle_id:
      params.put("DongleId", alternate_dongle_id)
  elif (current_dongle_id is None or current_dongle_id in _alternate_dongle_ids(params)) and stock_dongle_id is not None:
    params.put("DongleId", stock_dongle_id)
