#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>

/*Ip_origem
o Ip_destino
o Porta_origem
o Porta_destino
o Timestamp da mensagem
o Mensagem*/
typedef struct jsonE{
    char Ip_origem[15];
    char Ip_destino[15];
    int Porta_origem;
    int Porta_destino;
    clock_t Timestamp;
    char Mensagem[1000];
}JsonEnvio;
/*Ip_origem
o Ip_destino
o Porta_origem
o Porta_destino
o Timestamp da mensagem original
o Timestamp da mensagem de resposta
o ACK (true ou false)*/
typedef struct jsonA{
    char Ip_origem[15];
    char Ip_destino[15];
    int Porta_origem;
    int Porta_destino;
    clock_t Timestamp_original;
    clock_t Timestamp_resposta;
    bool Ack;
}JsonAck;
/*Ip_origem
o Ip_destino
o Porta_origem
o Porta_destino
o Timestamp da mensagem original
o Timestamp da mensagem de resposta
o Mensagem original
o Mensagem de resposta*/
typedef struct jsonR{
    char Ip_origem[15];
    char Ip_destino[15];
    int Porta_origem;
    int Porta_destino;
    clock_t Timestamp_original;
    clock_t Timestamp_resposta;
    char Mensagem_original[1000];
    char Mensagem_resposta[1000];
}JsonResposta;


void MountJsonEnvio(JsonEnvio JE);

JsonEnvio RecebeJsonEnvio();

void MountJsonACK(JsonAck JA);

JsonAck RecebeJsonACK();

void MountJsonResponse(JsonResposta JR);

JsonResposta RecebeJsonResponse();