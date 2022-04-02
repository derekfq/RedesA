#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include "client.h"
#define TAM 1024

void envio(FILE *arq, int socket_client, struct sockaddr_in end){
    int len;
    char buffer[TAM];

    while(fgets(buffer, TAM, arq) != NULL){
        printf("Enviando dados: %s", buffer);
        len = sendto(socket_client, buffer, TAM, 0, (struct sockaddr *)&end, sizeof(end));
        if(len == -1){
            printf("Erro ao enviar dados para o servidor.\n");
            exit(1);
        }
        bzero(buffer, TAM);
    }

    // Sending the 'END'
    strcpy(buffer, "END");
    sendto(socket_client, buffer, TAM, 0, (struct sockaddr *)&end, sizeof(end));
    if(arq)
        fclose(arq);
}

//Usado para receber o JSON de ACK e de resposta
void preenche_json(int socket_client, struct sockaddr_in end){
    char buffer[TAM];
    socklen_t tam_end;
    FILE *arq = fopen("client.json", "a");

    // Recebendo os dados do servidor
    while(true){
        tam_end = sizeof(end);
        if(recvfrom(socket_client, buffer, TAM, 0, (struct sockaddr *)&end, &tam_end) == -1){
            printf("Erro ao receber dados.\n");
            exit(1);
        }

        if(strcmp(buffer, "END") == 0)
            break;
        printf("Recebendo dados: %s", buffer);
        fprintf(arq, "%s", buffer);
        bzero(buffer, TAM);
    }
    fclose(arq);
}

int main(){
    char ip[15] = "127.0.0.1\0"; // Usuário insere isso
    const int porta = 8080;
    FILE *arq = fopen("client.json", "r");
    int socket_client, len;
    struct sockaddr_in client, server;

    if(arq == NULL){
        printf("Erro ao ler o arquivo.\n");
        exit(1);
    }
    // Criando o socket (SOCK_DGRAM -> UDP)
    socket_client = socket(AF_INET, SOCK_DGRAM, 0);
    if(socket_client < 0){
        printf("Erro no socket.\n");
        exit(1);
    }
    server.sin_family = AF_INET;
    server.sin_port = porta;
    server.sin_addr.s_addr = inet_addr(ip);

    // Envia os dados do arquivo para o servidor
    envio(arq, socket_client, server);
    if(arq)
        fclose(arq);
    printf("Dados enviados com sucesso.\n");

    // Aguardando ACK
    if(bind(socket_client, (struct sockaddr*) &server, sizeof(server)) < 0){
        printf("Erro na bind.\n");
        exit(1);
    }

    preenche_json(socket_client, client);
    printf("O dado enviado foi entregue ao destinatário com sucesso.\n");

    //Esperando a mensagem de resposta.
    preenche_json(socket_client, client);

    //Envia ACK Rsposta
    arq = fopen("ack.json", "r");
    envio(arq, socket_client, server);
    if(arq)
        fclose(arq);
    //Imprimir mensagem de resposta (abrir o arquivo json e exibir na tela as informações)
    printf("Desconectando do servidor...\n");

    close(socket_client);

    return 0;
}