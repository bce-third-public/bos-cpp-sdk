ps aux | grep mock_http_server_for_boss_sdk.py | awk '{print $2}' | xargs kill -9
