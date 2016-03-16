__author__ = 'cuican01'

import BaseHTTPServer
import json
from urlparse import parse_qs

class HttpMock:
    required_req_headers = {}
    optional_req_headers = {}
    request_body = ""
    response_headers = {}
    response_body = ""
    response_code = 200

    def ParseMockFile(self, mock_file):
        print mock_file
        print open(mock_file, "r").readlines();
        file_handle = open(mock_file, "r")
        json_data = json.load(file_handle)
        file_handle.close()


        self.required_req_headers = json_data["req"]["header"]["required"]
        self.optional_req_headers = json_data["req"]["header"]["optional"]
        self.request_body = json_data["req"]["body"]

        self.response_headers = json_data["res"]["header"]
        self.response_body = json_data["res"]["body"]
        self.response_code = json_data["res"]["code"]

    def MatchHeader(self, req_header):
        for (key, value) in self.required_req_headers.items():
            if not key in req_header:
                print "key x%sx not exist in req header" % (key)
                return False
            if req_header[key] != value:
                print "key_%s req_value:%s, expect_value:%s" % (key, req_header[key], value)
                return False

        for (key, value) in self.optional_req_headers.items():
            if not key in req_header:
                continue
            if req_header[key] != value:
                print "key_%s req_value:%s, expect_value:%s" % (key, req_header[key], value)
                return False

        return True

    def MatchBody(self, req_body):
        if self.request_body != req_body:
            return False
        return True



class HttpMockHandler(BaseHTTPServer.BaseHTTPRequestHandler):
    def do_GET(self):
        return self.DoMock()

    def do_POST(self):
        return self.DoMock()

    def do_PUT(self):
        return self.DoMock()

    def DoMock(self):
        http_mock_obj = HttpMock()
        mock_file_name = self.path.strip("/").split("?")[0].replace("/", "_")
        http_mock_obj.ParseMockFile(mock_file_name)
        print "=" * 80
        print self.headers
        print "=" * 80

        if not http_mock_obj.MatchHeader(self.headers):
            self.send_error(600, "header not match")
            return

        if "Content-Length" in self.headers:
            length = int(self.headers.getheader('Content-Length'))
            print length
            if not http_mock_obj.MatchBody(self.rfile.read(length)):
                self.send_error(600, "body not match")
                return

        self.send_response(http_mock_obj.response_code)
        print http_mock_obj.response_headers.items()
        for (key, value) in http_mock_obj.response_headers.items():
            self.send_header(key, value)
        self.end_headers()

        if http_mock_obj.response_body != "":
            print http_mock_obj.response_body
            self.wfile.write(http_mock_obj.response_body)
        self.wfile.close()
        return

if __name__ == '__main__':
    from BaseHTTPServer import HTTPServer
    server = HTTPServer(('localhost', 12349), HttpMockHandler)
    print 'Starting server, use <Ctrl-C> to stop'
    server.serve_forever()
