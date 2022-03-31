#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "json.h"

FILE MountJsonEnvio(JsonEnvio JE){
		FILE *arq = fopen("json_envio.json", "w");
	if(!arq){
		printf("\n Erro ao criar o arquivo Json de envio");
		exit(1);	
	}
	fprintf(arq, "{\n\t\"OriginalIP\":\"%s\",", JE.IpOrigem);
	fprintf(arq, "\n\t\"DestinationIP\":\"%s\",", JE.IpDestino);
	fprintf(arq, "\n\t\"OriginalPort\":\"%d\",", JE.PortaOrigem);
	fprintf(arq, "\n\t\"DestinationPort\":\"%d\",", JE.PortaDestino);
	fprintf(arq, "\n\t\"Timestamp\":\"%Lf\",", JE.Timestamp);
	fprintf(arq, "\n\t\"Message\":\"%s\"", JE.Mensagem);
	fprintf(arq, "\n\t}");
	fclose(arq);
}


FILE MountJsonACK(JsonAck JA){
	FILE *arq = fopen("json_ACK.json", "w");
	if(!arq){
		printf("\n Erro ao criar o arquivo Json ACK");
		exit(1);	
	}
	fprintf(arq, "{\n\t\"OriginalIP\":\"%s\",", JA.IpOrigem);
	fprintf(arq, "\n\t\"DestinationIP\":\"%s\",", JA.IpDestino);
	fprintf(arq, "\n\t\"OriginalPort\":\"%d\",", JA.PortaOrigem);
	fprintf(arq, "\n\t\"DestinationPort\":\"%d\",", JA.PortaDestino);
	fprintf(arq, "\n\t\"OriginalTimestamp\":\"%Lf\",", JA.TimestampResposta);
	fprintf(arq, "\n\t\"DestinationTimestamp\":\"%Lf\",", JA.TimestampDes);
	fprintf(arq, "\n\t\"Ack\":\"%d\"", JR.ACK ? 1 : 0);
	fprintf(arq, "\n\t}");
	fclose(arq);	
}


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
	fprintf(arq, "\n\t\"OriginalTimestamp\":\"%Lf\",", JR.TimestampResposta);
	fprintf(arq, "\n\t\"DestinationTimestamp\":\"%Lf\",", JR.TimestampDes);
	fprintf(arq, "\n\t\"OriginalMessage\":\"%s\",", JR.MensagemOriginal);
	fprintf(arq, "\n\t\"ResponseMessage\":\"%s\"", JR.MensagemResposta);
	fprintf(arq, "\n\t}");
	fclose(arq);
}
