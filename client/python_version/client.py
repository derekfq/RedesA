import socket
import json
import time

#Pegando ip host 
ip = socket.gethostbyname(socket.gethostname())


#UDP_ip = "127.0.0.1"
udp_port = 8080
#message = b"Hello, World!"

ip_DEST = input("Insira o ip destino:");
#ip_DEST = "127.0.0.1"

#print("UDP target ip: %s" % ip)
#print("UDP target port: %s" % udp_port)
#print("message: %s" % message)
message = input("Insira a Mensagem:");

T = time.time()

json_message = '{ "IP_origem":"%s", "IP_destino":"%s", "Porta_origem":%s, "Porta_destino":8080, "Timestamp":"%s","Mensagem":"%s"}' %(ip, ip_DEST, udp_port, T, message)

byte_message = bytes(json.dumps(json_message),'UTF-8');

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) # UDP
sock.sendto(byte_message, (ip, udp_port))

#Esperando ACK
data, addr = sock.recvfrom(1024) # buffer size is 1024 bytes

#Json do ACK
ack = json.loads(json.loads(data.decode("utf-8")))
print("\n");
print(ack)
print("ACK: %s" % ack['ACK'])

tempo_resp = float(ack["Timestamp da mensagem de resposta"]) - float(ack["Timestamp da mensagem original"])
print("Tempo de Resposta: %fs" % (tempo_resp))

#Esperando Resposta
print("\n\nAguardando Resposta:")
data, addr = sock.recvfrom(1024) # buffer size is 1024 bytes
response = json.loads(json.loads(data.decode("utf-8")))
print("\n")
if(not (response['Mensagem de resposta'] == '0')):
    print(response)
    print("Mensagem Resposta: %s" % response['Mensagem de resposta'])
    tempo_resp = float(response["Timestamp da mensagem de resposta"]) - float(response["Timestamp da mensagem original"])
    print("Tempo de Resposta: %fs" % (tempo_resp))
else:
    print("O Servidor não digitou uma mensagem de resposta.")


