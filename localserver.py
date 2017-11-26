#!/usr/bin/env python3

import socket
import time
import _thread
from random import randint, uniform, seed

HOST, PORT = '', 8888

seed(0)

def handle(client_connection):
    while True:
        request = client_connection.recv(1024).decode().strip()
        #print("request:", request)
        if request == "cpu":
            num = randint(19000000, 20000000)
            latency = uniform(0.0, 0.1)
        elif request == "balanced":
            num = randint(1900000, 2000000)
            latency = uniform(5, 6)
        elif request == "io":
            num = randint(1900, 2000)
            latency = uniform(20, 25)
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
    _thread.start_new_thread(handle, (client_connection,))
