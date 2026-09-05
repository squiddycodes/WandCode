from settings import RECEIVER_IP, UDP_PORT, getSocket
from spellbook import spells
import random

SPELL = random.choice(list(spells)) #get random spell

sock = getSocket()

try:
    sock.sendto(SPELL.encode("utf-8"), (RECEIVER_IP, UDP_PORT)) #send spell
    print(f"Sent '{SPELL}' to {RECEIVER_IP}:{UDP_PORT}")
except Exception:
    print("Transmission Failed: \nMake sure to set your IP in settings.py (don't commit to git)")
finally:
    sock.close()
