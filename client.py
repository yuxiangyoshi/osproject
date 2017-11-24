#client example
import socket
import threading

def foo():
    print("foo")

def testconnect():
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect(('localhost', 8888))
    print("inthread")

    # send 10 request for each range, then stop and close connection
    for i in range(10):
        client_socket.send("cpu".encode())
        data = client_socket.recv(1024).decode()
        print(data)

    for j in range(10):
        # client_socket.connect(('localhost', 8888))
        client_socket.send("balanced".encode())
        data = client_socket.recv(1024).decode()
        print(data)

    for k in range(10):
        # client_socket.connect(('localhost', 8888))
        client_socket.send("io".encode())
        data = client_socket.recv(1024).decode()
        print(data)
        
    client_socket.send("end".encode())
    client_socket.close()

threads = []
for i in range(5):
    threads.append(threading.Thread(target=testconnect, args=()))

for t in threads:
    t.start()
for t in threads:
    t.join()
