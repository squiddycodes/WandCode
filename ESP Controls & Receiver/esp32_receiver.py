from settings import UDP_PORT, UDP_IP, getSocket
from spellbook import spells


# Create and bind the UDP socket
sock = getSocket()
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
    sock.sendto(package.encode("utf-8"), (IP, UDP_PORT)) #send to IP over UDP_PORT
    print(f"Sent '{package}' to {IP}:{UDP_PORT}")

try:
    while True:
        data, addr = sock.recvfrom(1024) #1024 byte buffer max

        ir_hex = data.decode("utf-8") #DECODE AS HEX
        
        print(f"Received IR Code: {ir_hex} from {addr[0]}")

        spell = getSpell(ir_hex)
        if spell: #IF THE SPELL IS IN SPELLBOOK
            sendPackage(spell, getIP(ir_hex))

except KeyboardInterrupt:
    print("\nListener stopped.")
finally:
    sock.close()