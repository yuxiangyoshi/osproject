#!/usr/bin/env python3

import socket
import time
import thread
from random import randint, uniform, seed

HOST, PORT = '', 8888

seed(0)

def handle(client_connection):
    while True:
        request = client_connection.recv(1024).decode().strip()
        #print("request:", request)
        if request == "cpu":
            num = 200000
            latency = uniform(0.00, 0.01)
        elif request == "balanced":
            num = 20000
            latency = 0.5
        elif request == "io":
            num = 20
            latency = 2.5
        elif request.startswith("end"):
            client_connection.close()
            break
        else:
            print("bad request:", request)

        time.sleep(float(latency)/1000)
        response = str(num) + "\n"
        client_connection.sendall(response.encode())

listen_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
listen_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
listen_socket.bind((HOST, PORT))
listen_socket.listen(10)
print ('Serving TCP on port %s ...' % PORT)


while True:
    client_connection, client_address = listen_socket.accept()
    #print("before thread")
    thread.start_new_thread(handle, (client_connection,))
