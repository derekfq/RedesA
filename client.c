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

int envio(JsonEnvio data){
    char *ip = "127.0.0.1";
    int port = 8080;
    int e;

    int sockfd;
    struct sockaddr_in server_addr;
    //FILE *fp;
    //char *filename = "send.txt";

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
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

    //fp = fopen(filename, "r");
    //if (fp == NULL){
    //    perror("Erro ao ler o arquivo.");
   //     exit(1);
    //}

    send_file(&data, sockfd);

    printf("Dados do arquivo enviados com sucesso.\n");

    printf("Terminando a conexão.\n");
    close(sockfd);

    return 0;
}