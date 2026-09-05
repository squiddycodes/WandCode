import socket
from settings import MY_IP

LAPTOP_IP = MY_IP  ##### CHANGE - run ipconfig on cmd terminal then look for "IPv4 Address"
UDP_PORT = 5005 #change to be same as esp32

# Sample msg your listener is expecting
MESSAGE = "FF30CF"

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

try:
    sock.sendto(MESSAGE.encode("utf-8"), (LAPTOP_IP, UDP_PORT))
    print(f"Sent '{MESSAGE}' to {LAPTOP_IP}:{UDP_PORT}")
finally:
    sock.close()
