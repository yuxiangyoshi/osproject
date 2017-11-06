#client example
import socket

client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect(('localhost', 8888))

# send 10 request for each range, then stop and close connection
for i in range(10): 
    client_socket.send("a".encode())
    data = client_socket.recv(1024).decode()
    print(data)

for j in range(10):
    client_socket.send("b".encode())
    data = client_socket.recv(1024).decode()
    print(data)

for k in range(10):
    client_socket.send("c".encode())
    data = client_socket.recv(1024).decode()
    print(data)

client_socket.send("bye".encode())
client_socket.close()

