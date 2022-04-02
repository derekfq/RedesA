#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>

/*
Ip_origem
Ip_destino
Porta_origem
Porta_destino
Timestamp da mensagem
Mensagem*/
typedef struct jsonE{
    char Ip_origem[15];
    char Ip_destino[15];
    int Porta_origem;
    int Porta_destino;
    time_t Timestamp;
    char Mensagem[1000];
}JsonEnvio;
/*
Ip_origem
Ip_destino
Porta_origem
Porta_destino
Timestamp da mensagem original
Timestamp da mensagem de resposta
ACK (true ou false)*/
typedef struct jsonA{
    char Ip_origem[15];
    char Ip_destino[15];
    int Porta_origem;
    int Porta_destino;
    time_t Timestamp_original;
    time_t Timestamp_resposta;
    bool Ack;
}JsonAck;
/*
Ip_origem
Ip_destino
Porta_origem
Porta_destino
Timestamp da mensagem original
Timestamp da mensagem de resposta
Mensagem original
Mensagem de resposta*/
typedef struct jsonR{
    char Ip_origem[15];
    char Ip_destino[15];
    int Porta_origem;
    int Porta_destino;
    time_t Timestamp_original;
    time_t Timestamp_resposta;
    char Mensagem_original[1000];
    char Mensagem_resposta[1000];
}JsonResposta;

JsonEnvio RecebeJsonEnvio();

void MountJsonACK(JsonAck JA);

void MountJsonResponse(JsonResposta JR);

char *ColetarIP();
