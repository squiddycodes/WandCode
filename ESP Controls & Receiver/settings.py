import socket

#IP OF LAPTOP HOSTING THE RECEIVER
RECEIVER_IP="192.XXX.X.XXX"

#ESP Transmission/Receiving
UDP_PORT=5005
UDP_IP = "0.0.0.0"  # Listens on all available network interfaces #change to be esp32's port

def getSocket():
    return socket.socket(socket.AF_INET, socket.SOCK_DGRAM)