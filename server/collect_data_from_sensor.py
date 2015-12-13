
import socket
import datetime

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind(('', 16000))

data = sock.recvfrom(2)

print(data)
