import socket
import json



message={
    "id":256,
    "data":[1,2,3,4,5,6,7,8],
    "timestamp":12345678
}

SERVER_IP="127.0.0.1"
PORT=12345

sock=socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.sendto(json.dumps(message).encode(), (SERVER_IP, PORT))
sock.close()