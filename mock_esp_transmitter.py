import socket
from settings import MY_IP
from spellbook import spells
import random

LAPTOP_IP = MY_IP
UDP_PORT = 5005 #change to be same as esp32

SPELL = random.choice(list(spells))

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

try:
    sock.sendto(SPELL.encode("utf-8"), (LAPTOP_IP, UDP_PORT))
    print(f"Sent '{SPELL}' to {LAPTOP_IP}:{UDP_PORT}")
finally:
    sock.close()
