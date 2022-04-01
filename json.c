#include "json.h"

void MountJsonEnvio(JsonEnvio JE){
	FILE *arq = fopen("Request.json", "w");
	if(!arq){
		printf("\n Erro ao criar o arquivo Json de envio");
		exit(1);
	}
	fprintf(arq, "{\n\t\"Ip_origem\":\"%s\",", JE.Ip_origem);
	fprintf(arq, "\n\t\"Ip_destino\":\"%s\",", JE.Ip_destino);
	fprintf(arq, "\n\t\"Porta_origem\":\"%d\",", JE.Porta_origem);
	fprintf(arq, "\n\t\"Porta_destino\":\"%d\",", JE.Porta_destino);
	fprintf(arq, "\n\t\"Timestamp\":\"%ld\",", JE.Timestamp);
	fprintf(arq, "\n\t\"Mensagem\":\"%s\"", JE.Mensagem);
	fprintf(arq, "\n\t}");
	fclose(arq);
}

JsonEnvio RecebeJsonEnvio(){
	JsonEnvio JE;
	FILE *arq = fopen("Request.json", "r");
	fscanf(arq, "{\n\t\"Ip_origem\":\"%s\",", &JE.Ip_origem);
	fscanf(arq, "\n\t\"Ip_destino\":\"%s\",", &JE.Ip_destino);
	fscanf(arq, "\n\t\"Porta_origem\":\"%d\",", &JE.Porta_origem);
	fscanf(arq, "\n\t\"Porta_destino\":\"%d\",", &JE.Porta_destino);
	fscanf(arq, "\n\t\"Timestamp\":\"%ld\",", &JE.Timestamp);
	fscanf(arq, "\n\t\"Mensagem\":\"%s\"", &JE.Mensagem);
	fscanf(arq, "\n\t}");
	if(arq)
		fclose(arq);
	return JE;
}


void MountJsonACK(JsonAck JA){
	FILE *arq = fopen("Ack.json", "w");
	if(!arq){
		printf("\n Erro ao criar o arquivo Json ACK");
		exit(1);
	}
	fprintf(arq, "{\n\t\"Ip_origem\":\"%s\",", JA.Ip_origem);
	fprintf(arq, "\n\t\"Ip_destino\":\"%s\",", JA.Ip_destino);
	fprintf(arq, "\n\t\"Porta_origem\":\"%d\",", JA.Porta_origem);
	fprintf(arq, "\n\t\"Porta_destino\":\"%d\",", JA.Porta_destino);
	fprintf(arq, "\n\t\"Timestamp_original\":\"%ld\",", JA.Timestamp_original);
	fprintf(arq, "\n\t\"Timestamp_resposta\":\"%ld\",", JA.Timestamp_resposta);
	fprintf(arq, "\n\t\"Ack\":\"%d\"", JA.Ack ? 1 : 0);
	fprintf(arq, "\n\t}");
	fclose(arq);
}

JsonAck RecebeJsonACK(){
	JsonAck JA;
	FILE *arq = fopen("Ack.json", "r");
	fscanf(arq, "{\n\t\"Ip_origem\":\"%s\",", &JA.Ip_origem);
	fscanf(arq, "\n\t\"Ip_destino\":\"%s\",", &JA.Ip_destino);
	fscanf(arq, "\n\t\"Porta_origem\":\"%d\",", &JA.Porta_origem);
	fscanf(arq, "\n\t\"Porta_destino\":\"%d\",", &JA.Porta_destino);
	fscanf(arq, "\n\t\"Timestamp_original\":\"%ld\",", &JA.Timestamp_original);
	fscanf(arq, "\n\t\"Timestamp_resposta\":\"%ld\",", &JA.Timestamp_resposta);
	fscanf(arq, "\n\t\"Ack\":\"%d\"", &JA.Ack ? true : false);
	fscanf(arq, "\n\t}");
	if(arq)
		fclose(arq);
	return JA;
}


void MountJsonResponse(JsonResposta JR){
	FILE *arq = fopen("Response.json", "w");
	if(!arq){
		printf("\n Erro ao criar o arquivo Json de resposta");
		exit(1);
	}
	fprintf(arq, "{\n\t\"Ip_origem\":\"%s\",", JR.Ip_origem);
	fprintf(arq, "\n\t\"Ip_destino\":\"%s\",", JR.Ip_destino);
	fprintf(arq, "\n\t\"Porta_origem\":\"%d\",", JR.Porta_origem);
	fprintf(arq, "\n\t\"Porta_destino\":\"%d\",", JR.Porta_destino);
	fprintf(arq, "\n\t\"Timestamp_original\":\"%ld\",", JR.Timestamp_original);
	fprintf(arq, "\n\t\"Timestamp_resposta\":\"%ld\",", JR.Timestamp_resposta);
	fprintf(arq, "\n\t\"Mensagem_original\":\"%s\",", JR.Mensagem_original);
	fprintf(arq, "\n\t\"Mensagem_resposta\":\"%s\"", JR.Mensagem_resposta);
	fprintf(arq, "\n\t}");
	fclose(arq);
}

JsonResposta RecebeJsonResponse(){
	JsonResposta JR;
	FILE *arq = fopen("Ack.json", "r");
	fscanf(arq, "{\n\t\"Ip_origem\":\"%s\",", &JR.Ip_origem);
	fscanf(arq, "\n\t\"Ip_destino\":\"%s\",", &JR.Ip_destino);
	fscanf(arq, "\n\t\"Porta_origem\":\"%d\",", &JR.Porta_origem);
	fscanf(arq, "\n\t\"Porta_destino\":\"%d\",", &JR.Porta_destino);
	fscanf(arq, "\n\t\"Timestamp_original\":\"%ld\",", &JR.Timestamp_original);
	fscanf(arq, "\n\t\"Timestamp_resposta\":\"%ld\",", &JR.Timestamp_resposta);
	fscanf(arq, "\n\t\"Mensagem_original\":\"%s\",", &JR.Mensagem_original);
	fscanf(arq, "\n\t\"Mensagem_resposta\":\"%s\"", &JR.Mensagem_resposta);
	fscanf(arq, "\n\t}");
	if(arq)
		fclose(arq);
	return JR;
}
