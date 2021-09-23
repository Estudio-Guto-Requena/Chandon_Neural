import socket
import time
import json
import random

HOST, PORT = "192.168.0.161", 5005
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
min_t = 0
max_t = 50000
while True:
    a = {'signal':100, 'lAplha':random.randint(min_t, max_t), 'hAplha':random.randint(min_t, max_t)}
    b = json.dumps(a).encode('utf-8')
    print(b)
    sock.sendto(b,(HOST, PORT))
    time.sleep(1)
