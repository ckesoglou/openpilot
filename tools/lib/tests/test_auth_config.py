import pytest

from openpilot.tools.lib import api
from openpilot.tools.lib.auth_config import DEFAULT_API_HOST, KONIK_API_HOST, get_token, normalize_api_host, set_token


def test_set_token_preserves_comma_token_when_adding_konik(mocker, tmp_path):
  mocker.patch("openpilot.tools.lib.auth_config.Paths.config_root", return_value=str(tmp_path))

  set_token("comma-token", DEFAULT_API_HOST)
  set_token("konik-token", KONIK_API_HOST)

  assert get_token(DEFAULT_API_HOST) == "comma-token"
  assert get_token(KONIK_API_HOST) == "konik-token"
  assert get_token() == "comma-token"


@pytest.mark.parametrize("host, expected", [
  ("https://api.comma.ai/", DEFAULT_API_HOST),
  ("API.Example.com", "https://api.example.com"),
  ("https://example.com/op-api/", "https://example.com/op-api"),
])
def test_normalize_api_host(host, expected):
  assert normalize_api_host(host) == expected


@pytest.mark.parametrize("configured, expected", [
  (DEFAULT_API_HOST, [DEFAULT_API_HOST, KONIK_API_HOST]),
  (KONIK_API_HOST, [DEFAULT_API_HOST, KONIK_API_HOST]),
  ("https://api.example.com", ["https://api.example.com", DEFAULT_API_HOST, KONIK_API_HOST]),
])
def test_route_api_hosts_tries_custom_server_first(monkeypatch, configured, expected):
  monkeypatch.delenv("API_HOST", raising=False)
  monkeypatch.setattr(api, "API_HOST", configured)
  assert api.route_api_hosts() == expected
