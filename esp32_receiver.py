import socket
from spellbook import spells

#ESP CONNECTION
UDP_IP = "0.0.0.0"  # Listens on all available network interfaces
UDP_PORT = 5005 #change to be esp32's port

# Create and bind the UDP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind((UDP_IP, UDP_PORT))
#END ESP CONNECTION
print(f"ESP Listener active on port {UDP_PORT}...")

# Get a spell common name from spellbook, given an input HEX
def getSpell(ir_hex):
    if ir_hex in spells:
        return spells[ir_hex][0]
    return None

# Get a spell's Output Device IP from spellbook, given an input HEX
def getIP(ir_hex):
    if ir_hex in spells:
        return spells[ir_hex][1]
    return None

# Send package to IP
def sendPackage(package, IP):
    print(f'Sending {package} to {IP}...')
    #TODO add send logic

try:
    while True:
        # Buffer size of 1024 bytes
        data, addr = sock.recvfrom(1024)

        ir_hex = data.decode("utf-8") #DECODE AS HEX
        
        print(f"Received IR Code: {ir_hex} from {addr[0]}")

        spell = getSpell(ir_hex)
        if spell: #IF THE SPELL IS IN SPELLBOOK
            sendPackage(spell, getIP(ir_hex))

except KeyboardInterrupt:
    print("\nListener stopped.")
finally:
    sock.close()