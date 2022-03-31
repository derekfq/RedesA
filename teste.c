#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
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




FILE MountJsonResponse(JsonResposta JR){
	FILE *arq = fopen("json_response.json", "w");
	if(!arq){
		printf("\n Erro ao criar o arquivo Json de resposta");
		exit(1);	
	}
	fprintf(arq, "{\n\t\"OriginalIP\":\"%s\",", JR.IpOrigem);
	fprintf(arq, "\n\t\"DestinationIP\":\"%s\",", JR.IpDestino);
	fprintf(arq, "\n\t\"OriginalPort\":\"%d\",", JR.PortaOrigem);
	fprintf(arq, "\n\t\"DestinationPort\":\"%d\",", JR.PortaDestino);
	fprintf(arq, "\n\t\"OriginalTimestamp\":\"%ld\",", JR.TimestampResposta);
	fprintf(arq, "\n\t\"DestinationTimestamp\":\"%ld\",", JR.TimestampOriginal);
	fprintf(arq, "\n\t\"OriginalMessage\":\"%s\",", JR.MensagemOriginal);
	fprintf(arq, "\n\t\"ResponseMessage\":\"%s\"", JR.MensagemResposta);
	fprintf(arq, "\n}");
	
	fclose(arq);
}

int main(){
	JsonResposta JS;
	strcpy(JS.IpOrigem, "123.456.789.0");
	strcpy(JS.IpDestino, "123.456.789.0");
	JS.PortaOrigem = 1;
	JS.PortaDestino =32;
	JS.TimestampOriginal = clock();
	JS.TimestampResposta = clock() + 1;
	strcpy(JS.MensagemOriginal, "TESTANDO");
	strcpy(JS.MensagemResposta, "Testado");
	MountJsonResponse(JS);
}
