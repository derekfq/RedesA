import socket
import json
import time

UDP_PORT = 1500

#Pegando IP host
IP = socket.gethostbyname(socket.gethostname())

sock = socket.socket(socket.AF_INET,socket.SOCK_DGRAM) # UDP
sock.bind((IP, UDP_PORT))

while True:
    data, addr = sock.recvfrom(1024) # buffer size is 1024 bytes
    #print(data.decode("utf-8"))
    decode = data.decode("utf-8")
    response = json.loads(json.loads(decode))
    print("\n\n",response,"\n")
    men = response["Mensagem"]
    print("Mensagem do Client: %s\n" %(men))


    IP_O = response['Ip_origem']
    P_O = response['Porta_origem']
    M = response['Mensagem']
    T = response['Timestamp da mensagem']
    T_RESP = time.time()


    #Enviar ACK
    ACK = '{ "Ip_origem":"%s", "Ip_destino":"%s", "Porta_origem":1500, "Porta_destino":%s, "Timestamp da mensagem original":"%s", "Timestamp da mensagem de resposta":"%s", "ACK":true}' %(IP, IP_O, P_O, T, T_RESP)

    BYTE_ACK = bytes(json.dumps(ACK),'UTF-8')
    sock.sendto(BYTE_ACK, addr)


    T_RESP = time.time()
    #Enviar Mensagem de reposta
    response = input("Digite uma mensagem de resposta (0 - para cancelar):")
    RESPOSTA = '{ "Ip_origem":"%s", "Ip_destino":"%s", "Porta_origem":1500, "Porta_destino":%s, "Timestamp da mensagem original":"%s", "Timestamp da mensagem de resposta":"%s", "Mensagem original":"%s", "Mensagem de resposta":"%s"}' %(IP, IP_O, P_O, T, T_RESP, M, response)
    resposta_byte = bytes(json.dumps(RESPOSTA),'UTF-8')
    sock.sendto(resposta_byte, addr)
