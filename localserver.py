import socket
from random import randint
HOST, PORT = '', 8888

listen_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
listen_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
listen_socket.bind((HOST, PORT))
listen_socket.listen(5)
print ('Serving HTTP on port %s ...' % PORT)

a = [randint(0,50) for x in range(10)]
b = [randint(100,500) for x in range(10)]
c = [randint(1000,5000) for x in range(10)]

print "Array a:"
print(a)
print "Array b:"
print(b)
print "Array c:"
print(c)

i = 0  # counter for selecting a
j = 0
k = 0
while True:
    client_connection, client_address = listen_socket.accept()
    if (i > 10):
      i = 0
    if (j > 10):
      j = 0
    if (k > 10):
      k = 0
    
    while True:
      request = client_connection.recv(1024).decode()
      print(request)
      if request == "a":
        print(i)
        astr = a[i%10]
        http_response = str(astr)
        client_connection.sendall(http_response.encode())
        i += 1
      elif request == "b":
        print(j)
        bstr = b[j%10]
        http_response = str(bstr)
        client_connection.sendall(http_response.encode())
        j += 1
      elif request == "c":
        print(k)
        cstr = c[k%10]
        http_response = str(cstr)
        client_connection.sendall(http_response.encode())
        k += 1
      else:
        # client_connection.sendall("Q".encode())
        client_connection.close()
        break
