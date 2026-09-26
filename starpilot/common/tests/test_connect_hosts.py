import pytest

from openpilot.starpilot.common import connect_hosts as ch


class FakeParams:
  def __init__(self, values=None):
    self.values = dict(values or {})

  def get(self, key):
    return self.values.get(key)

  def get_bool(self, key):
    return self.values.get(key) in (True, 1, "1", b"1")

  def put_int(self, key, value):
    self.values[key] = int(value)


CUSTOM = {
  "ConnectServer": ch.CONNECT_SERVER_CUSTOM,
  "CustomApiHost": "https://api.example.com",
  "CustomAthenaHost": "wss://athena.example.com",
  "CustomConnectHost": "https://connect.example.com",
}


@pytest.mark.parametrize("use_konik, expected", [(b"1", ch.CONNECT_SERVER_KONIK), (b"0", ch.CONNECT_SERVER_COMMA), (None, ch.CONNECT_SERVER_COMMA)])
def test_falls_back_to_legacy_konik_toggle(use_konik, expected):
  params = FakeParams({"UseKonikServer": use_konik})
  assert ch.get_connect_server(params) == expected


@pytest.mark.parametrize("server", [ch.CONNECT_SERVER_COMMA, ch.CONNECT_SERVER_KONIK])
def test_preset_hosts(server):
  params = FakeParams({"ConnectServer": server, "UseKonikServer": b"1"})
  assert ch.get_connect_hosts(params) == ch.PRESET_HOSTS[server]


def test_custom_hosts():
  hosts = ch.get_connect_hosts(FakeParams(CUSTOM))
  assert hosts == ch.ConnectHosts("https://api.example.com", "wss://athena.example.com", "https://connect.example.com")
  assert hosts.connect_hostname == "connect.example.com"


def test_custom_hosts_are_normalized():
  params = FakeParams({**CUSTOM, "CustomApiHost": b" api.example.com/ ", "CustomAthenaHost": "athena.example.com:8443/", "CustomConnectHost": ""})
  hosts = ch.get_connect_hosts(params)
  assert hosts.api == "https://api.example.com"
  assert hosts.athena == "wss://athena.example.com:8443"
  # Connect is optional and falls back to the API host
  assert hosts.connect == "https://api.example.com"


@pytest.mark.parametrize("overrides", [
  {"CustomApiHost": ""},
  {"CustomAthenaHost": ""},
  {"CustomApiHost": "wss://api.example.com"},
  {"CustomAthenaHost": "https://athena.example.com"},
  {"CustomApiHost": "https://"},
])
def test_incomplete_custom_server_falls_back_to_comma(overrides):
  params = FakeParams({**CUSTOM, **overrides})
  assert ch.get_connect_server(params) == ch.CONNECT_SERVER_COMMA
  assert ch.get_connect_hosts(params) == ch.PRESET_HOSTS[ch.CONNECT_SERVER_COMMA]


@pytest.mark.parametrize("value", [b"7", "garbage"])
def test_invalid_server_value_falls_back_to_comma(value):
  assert ch.get_connect_server(FakeParams({"ConnectServer": value})) == ch.CONNECT_SERVER_COMMA


def test_migration_only_runs_once():
  params = FakeParams({"UseKonikServer": b"0"})
  assert ch.migrate_connect_server(params)
  assert params.get("ConnectServer") == ch.CONNECT_SERVER_COMMA

  params.values["UseKonikServer"] = b"1"
  assert not ch.migrate_connect_server(params)
  assert params.get("ConnectServer") == ch.CONNECT_SERVER_COMMA
