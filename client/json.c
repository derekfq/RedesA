#include "json.h"
#include <arpa/inet.h>

void MountJsonEnvio(JsonEnvio JE){
	FILE *arq = fopen("Data.json", "w");
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
	fprintf(arq, "\n}");
	fclose(arq);
}

JsonAck RecebeJsonACK(){
	JsonAck JA;
	int boo;
	FILE *arq = fopen("Data.json", "r");
	// TODO: coletar parte do envio antes do ack
	fscanf(arq, "{\n\t\"Ip_origem\":\"%s\",", JA.Ip_origem);
	fscanf(arq, "\n\t\"Ip_destino\":\"%s\",", JA.Ip_destino);
	fscanf(arq, "\n\t\"Porta_origem\":\"%d\",", &JA.Porta_origem);
	fscanf(arq, "\n\t\"Porta_destino\":\"%d\",", &JA.Porta_destino);
	fscanf(arq, "\n\t\"Timestamp_original\":\"%ld\",", &JA.Timestamp_original);
	fscanf(arq, "\n\t\"Timestamp_resposta\":\"%ld\",", &JA.Timestamp_resposta);
	fscanf(arq, "\n\t\"Ack\":\"%d\"", &boo);
	fscanf(arq, "\n\t}");
	if(boo == 1)
		JA.Ack = true;
	else
		JA.Ack = false;
	if(arq)
		fclose(arq);
	return JA;
}

JsonResposta RecebeJsonResponse(){
	JsonResposta JR;
	FILE *arq = fopen("Data.json", "r");
	// TODO: coletar parte do envio e ack antes do response
	fscanf(arq, "{\n\t\"Ip_origem\":\"%s\",", JR.Ip_origem);
	fscanf(arq, "\n\t\"Ip_destino\":\"%s\",", JR.Ip_destino);
	fscanf(arq, "\n\t\"Porta_origem\":\"%d\",", &JR.Porta_origem);
	fscanf(arq, "\n\t\"Porta_destino\":\"%d\",", &JR.Porta_destino);
	fscanf(arq, "\n\t\"Timestamp_original\":\"%ld\",", &JR.Timestamp_original);
	fscanf(arq, "\n\t\"Timestamp_resposta\":\"%ld\",", &JR.Timestamp_resposta);
	fscanf(arq, "\n\t\"Mensagem_original\":\"%s\",", JR.Mensagem_original);
	fscanf(arq, "\n\t\"Mensagem_resposta\":\"%s\"", JR.Mensagem_resposta);
	fscanf(arq, "\n\t}");
	if(arq)
		fclose(arq);
	return JR;
}

char *ColetarIP(){
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    struct ifreq ifr;

    // Endereço IPv4
    ifr.ifr_addr.sa_family = AF_INET;

    // Endereço IP dentro de "enp2s0"
    strncpy(ifr.ifr_name, "enp2s0", IFNAMSIZ - 1);
    ioctl(fd, SIOCGIFADDR, &ifr);
    close(fd);
    // printf("%s\n", inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));

    return inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr);
}