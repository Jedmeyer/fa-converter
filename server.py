#!/usr/bin/env python

import os
from http.server import BaseHTTPRequestHandler, HTTPServer
from urllib.parse import urlparse
from urllib.parse import parse_qsl
# HTTPRequestHandler class
class testHTTPServer_RequestHandler(BaseHTTPRequestHandler):

  # GET
  def do_GET(self):
        intermed_args = []
        com_args = []
        query = urlparse(self.path).query
        print (query)
        
        diction = parse_qsl(query)
        
        for key, value in diction:
            print(key, " and value: " , value)
            com_args.append(value)
        for x in com_args:
            print(x)

        print(query.split("?"))
        fin_query = query.split("?")

        s = 0

        for x in fin_query:
            print(intermed_args.append(x.split("&")))
            

        for x in intermed_args:
            for y in x:
                
                if y.split("=")[0] == "trans":
                    com_args[4] = y.split("=")[1]
            
        
        print(com_args)
        file_html = open("./html-pages/front-page.html", "r")
        query.split("?")


        command = " "
        send_data = 1

        if (len(query) < 4):
            send_data = 0
            self.send_response(200)
            self.send_header('Content-type','text/html')
            self.end_headers()
            self.wfile.write(bytes(file_html.read(), "utf8"))
        elif (com_args[5] == "simulate"):
            command = "./simulate "
            for x in com_args:
                command+=('\"')
                command = command + x 
                command+=('\" ')
        elif (com_args[5] == "DFA"):
            command = "./translate "
            for x in com_args:
                command+=('\"')
                command = command + x
                command+=('\" ')
            command = command + "\"fake-in\" "


        print(command)
        myCmd = os.popen(command).read()
        # Send response status code
        self.send_response(200)

        # Send headers
       
        # Send message back to client
        message = "Hello world!"
        # Write content as utf-8 data
        if(send_data == 1):
            self.send_response(200)

            self.wfile.write(bytes(myCmd, "utf8"))
            self.send_header('Content-type','text/html')
            self.end_headers()


        return

def run():
  print('starting server...')

  # Server settings
  # Choose port 8080, for port 80, which is normally used for a http server, you need root access
  server_address = ('127.0.0.1', 8081)
  httpd = HTTPServer(server_address, testHTTPServer_RequestHandler)
  print('running server...')
  httpd.serve_forever()


run()