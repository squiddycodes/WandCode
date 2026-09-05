'''
SPELLS
KEY: Hex value of packet for a given spell sequence EX: Triange Triange Square => "FF30CF"

Value: Tuple (Common Name, Output IP)
    Common Name: Common name of spell -> "Fireball"
    Output IP: IP of ESP to send the data back out to
'''
spells = { #"HEX": (spellname, outputIP) TODO add full spell list
    "FF30CF": ("Fireball", "192.100.1.200"),
    "FF30CC": ("Magic Missile", "192.100.1.201"),
    "FF30CD": ("Poopie diapie", "192.100.1.202"),
}