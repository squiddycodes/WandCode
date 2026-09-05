import socket

#ESP CONNECTION
UDP_IP = "0.0.0.0"  # Listens on all available network interfaces
UDP_PORT = 5005 #change to be esp32's port

# Create and bind the UDP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind((UDP_IP, UDP_PORT))
#END ESP CONNECTION
print(f"ESP Listener active on port {UDP_PORT}...")

spellbook = { #HEX: (spellname, outputIP)
    "FF30CF": ("Fireball", "192.100.1.200"),
    "FF30CC": ("Magic Missile", "192.100.1.201"),
    "FF30CD": ("Poopie diapie", "192.100.1.202"),
}

try:
    while True:
        # Buffer size of 1024 bytes
        data, addr = sock.recvfrom(1024)

        ir_hex = data.decode("utf-8")
        
        print(f"Received IR Code: {ir_hex} from {addr[0]}")
        
        # ROOM CONTROL LOGIC - if A received from addr[A], send signal to turn on light
        if ir_hex == "FF30CF":
            #send signal to a 
            print("Fireball!")

except KeyboardInterrupt:
    print("\nListener stopped.")
finally:
    sock.close()