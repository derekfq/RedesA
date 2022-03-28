#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

/*Ip_origem
o Ip_destino
o Porta_origem
o Porta_destino
o Timestamp da mensagem
o Mensagem*/
typedef struct jsonE{
    char IpOrigem[15];
    char IpDestino[15];
    int PortaOrigem;
    int PortaDestino;
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
    char IpOrigem[15];
    char IpDestino[15];
    int PortaOrigem;
    int PortaDestino;
    clock_t TimestampOriginal;
    clock_t TimestampResposta;
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
    char IpOrigem[15];
    char IpDestino[15];
    int PortaOrigem;
    int PortaDestino;
    clock_t TimestampOriginal;
    clock_t TimestampResposta;
    char MensagemOriginal[1000];
    char MensagemResposta[1000];
}JsonResposta;