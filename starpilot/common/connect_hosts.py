from dataclasses import dataclass
from urllib.parse import urlparse

from openpilot.common.params import Params

CONNECT_SERVER_COMMA = 0
CONNECT_SERVER_KONIK = 1
CONNECT_SERVER_CUSTOM = 2

CONNECT_SERVERS = (CONNECT_SERVER_COMMA, CONNECT_SERVER_KONIK, CONNECT_SERVER_CUSTOM)

# Only switch_connect_server() may write these. Generic writers (backups, profiles, resets,
# cloud sync, Galaxy, favorites) must skip them or the dongle ID and log root go stale.
CONNECT_SERVER_PARAM_KEYS = frozenset({
  "ConnectServer",
  "UseKonikServer",
  "CustomApiHost",
  "CustomAthenaHost",
  "CustomConnectHost",
  # A restored dongle ID would be reused without re-registering
  "DongleId",
  "CustomDongleId",
  "KonikDongleId",
  "StockDongleId",
})

API_SCHEMES = ("https", "http")
ATHENA_SCHEMES = ("wss", "ws")
CONNECT_SCHEMES = ("https", "http")


@dataclass(frozen=True)
class ConnectHosts:
  api: str
  athena: str
  connect: str

  @property
  def connect_hostname(self) -> str:
    return urlparse(self.connect).netloc or self.connect


PRESET_HOSTS = {
  CONNECT_SERVER_COMMA: ConnectHosts("https://api.commadotai.com", "wss://athena.comma.ai", "https://connect.comma.ai"),
  CONNECT_SERVER_KONIK: ConnectHosts("https://api.konik.ai", "wss://athena.konik.ai", "https://stable.konik.ai"),
}


def _decode(value) -> str:
  if isinstance(value, bytes):
    value = value.decode("utf-8", errors="ignore")
  return str(value).strip() if value is not None else ""


def normalize_host(value, default_scheme: str) -> str:
  url = _decode(value)
  if url and "://" not in url:
    url = f"{default_scheme}://{url}"
  return url.rstrip("/")


def is_valid_host(url: str, schemes: tuple[str, ...]) -> bool:
  parsed = urlparse(url)
  return parsed.scheme in schemes and bool(parsed.netloc) and not parsed.query and not parsed.fragment


def get_custom_hosts(params: Params | None = None) -> ConnectHosts | None:
  """Returns the user supplied hosts, or None if the API or Athena host is missing/invalid."""
  params = params or Params()
  api = normalize_host(params.get("CustomApiHost"), API_SCHEMES[0])
  athena = normalize_host(params.get("CustomAthenaHost"), ATHENA_SCHEMES[0])
  connect = normalize_host(params.get("CustomConnectHost"), CONNECT_SCHEMES[0])

  if not is_valid_host(api, API_SCHEMES) or not is_valid_host(athena, ATHENA_SCHEMES):
    return None
  if not is_valid_host(connect, CONNECT_SCHEMES):
    connect = api
  return ConnectHosts(api, athena, connect)


def get_connect_server(params: Params | None = None) -> int:
  params = params or Params()
  value = params.get("ConnectServer")
  if value is None:
    # Devices that haven't booted since ConnectServer was added only have the legacy toggle
    return CONNECT_SERVER_KONIK if params.get_bool("UseKonikServer") else CONNECT_SERVER_COMMA

  try:
    server = int(_decode(value))
  except ValueError:
    return CONNECT_SERVER_COMMA

  if server == CONNECT_SERVER_CUSTOM and get_custom_hosts(params) is None:
    return CONNECT_SERVER_COMMA
  return server if server in CONNECT_SERVERS else CONNECT_SERVER_COMMA


def get_connect_hosts(params: Params | None = None) -> ConnectHosts:
  params = params or Params()
  server = get_connect_server(params)
  if server == CONNECT_SERVER_CUSTOM:
    return get_custom_hosts(params) or PRESET_HOSTS[CONNECT_SERVER_COMMA]
  return PRESET_HOSTS[server]


def migrate_connect_server(params: Params) -> bool:
  if params.get("ConnectServer") is not None:
    return False
  params.put_int("ConnectServer", CONNECT_SERVER_KONIK if params.get_bool("UseKonikServer") else CONNECT_SERVER_COMMA)
  return True
