#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include "client.h"

#define SIZE 1024

void send_file(JsonEnvio *data, int sockfd){
    int n;
    //char data[SIZE] = {0};

    //while (fgets(data, SIZE, fp) != NULL){
        if (send(sockfd, (const void *)data, sizeof(data), 0) == -1){
            perror("Erro ao enviar o arquivo.");
            exit(1);
        }
        bzero((void *)data, SIZE);
    //}
}

int envio(FILE* FileName){
    char *ip = ColetarIP();
    int port = 8080;
    int e;

    int sockfd;
    struct sockaddr_in server_addr;
    FILE *fp;
    char *filename = "Request.json";

    //AF_INET (IPv4)
    sockfd = socket(AF_INET, SOCK_DGRAM, 0); //SOCK_STREAM FOR TCP AND SOCK_DGRAM FOR UDP 
    if (sockfd < 0){
        perror("Erro no socket");
        exit(1);
    }
    printf("Socket do servidor criado com sucesso.\n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = port;
    server_addr.sin_addr.s_addr = inet_addr(ip);

    e = connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (e == -1){
        perror("Erro no socket");
        exit(1);
    }
    printf("Conectado com Servidor.\n");

    JsonEnvio MensagemEnvio;
    preencher(MensagemEnvio, port);
    MountJsonEnvio(MensagemEnvio);

    FILE *fp = fopen("Envio.json", "r");
    if (fp == NULL){
        perror("Erro ao ler o arquivo.");
        exit(1);
    }

    send_file(&fp, sockfd);

    //Receber o ACK and the response message 
    printf("Dados do arquivo enviados com sucesso.\n");

    printf("Terminando a conexão.\n");
    close(sockfd);
    //Ver como vai enviar o Jeiso 
    return 0;
}

void preencher(JsonEnvio data,int port){
    data.Porta_origem = port;
    data.Timestamp = clock();
    strcpy(data.Ip_origem, ColetarIP());
    printf("Ip de Destino: ");
    scanf("%d",&data.Ip_destino);
    printf("\nPorta de Destino: ");
    scanf("%d",&data.Porta_destino);
    printf("\nMensagem: ");
    scanf("%s",data.Mensagem);
    return data;
    // colocar nosso ip e essas coisa tudo

}

///CheckList
// Verficar a resposta do ack
// Definição de um tempo pro ack 