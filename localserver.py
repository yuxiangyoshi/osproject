import socket
import time
import thread
from random import randint

HOST, PORT = '', 8888

def handle(client_connection):
    while True:
        request = client_connection.recv(1024).decode()
        print(request)
        if request == "cpu":
            num = randint(190, 200)
            latency = randint(0, 1)
        elif request == "balanced":
            num = randint(1800000, 1900000)
            latency = randint(300, 500)
        elif request == "io":
            num = randint(19000000, 20000000)
            latency = randint(1000, 2000)
        elif request == "end":
            client_connection.close()
            break
        else:
            print("bad request")

        time.sleep(float(latency)/1000)
        http_response = str(num)
        client_connection.sendall(http_response.encode())

            
listen_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
listen_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
listen_socket.bind((HOST, PORT))
listen_socket.listen(10)
print ('Serving HTTP on port %s ...' % PORT)


while True:
    client_connection, client_address = listen_socket.accept()
    #print("before thread")
    thread.start_new_thread(handle, (client_connection,))
