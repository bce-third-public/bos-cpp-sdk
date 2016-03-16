#! /bin/sh
mock_http_server=mock_http_server_for_boss_sdk.py
cp http_server.py $mock_http_server
python $mock_http_server &
