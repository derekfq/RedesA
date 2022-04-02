#include "server.h"
#define TAM 1024

void envio(FILE *arq, int socket_server, struct sockaddr_in end){
    char buffer[TAM];
    int len;

    while(fgets(buffer, TAM, arq) != NULL){
        printf("Enviando dados: %s", buffer);
        len = sendto(socket_server, buffer, TAM, 0, (struct sockaddr *)&end, sizeof(end));
        if(len == -1){
            printf("Erro ao enviar dados para o servidor.\n");
            exit(1);
        }
        bzero(buffer, TAM);
    }

    strcpy(buffer, "END");
    sendto(socket_server, buffer, TAM, 0, (struct sockaddr *)&end, sizeof(end));

    fclose(arq);
}

void preencher_json(int socket_server, struct sockaddr_in end){
    int n;
    char buffer[TAM];
    socklen_t addr_TAM;

    // Creating a file.
    FILE *arq = fopen("server.json", "w");

    // Receiving the data and writing it into the file.
    while(true){
        addr_TAM = sizeof(end);
        int len = recvfrom(socket_server, buffer, TAM, 0, (struct sockaddr *)&end, &addr_TAM);
        if(len == -1){
            printf("Erro no recebimento do arquivo!");
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
    char *ip = "127.0.0.1"; // usuário coloca o ip
    const int port = 8080;
    int socket_server, len;
    struct sockaddr_in server, client;
    char buffer[TAM];

    // Creating a UDP socket
    socket_server = socket(AF_INET, SOCK_DGRAM, 0);
    if(socket_server < 0){
        printf("Erro no socket.\n");
        exit(1);
    }
    server.sin_family = AF_INET;
    server.sin_port = port;
    server.sin_addr.s_addr = inet_addr(ip);

    if(bind(socket_server, (struct sockaddr *)&server, sizeof(server)) < 0){
        printf("Erro na bind.\n");
        exit(1);
    }

    printf("Iniciando servidor.\n");
    preencher_json(socket_server, client);//Recebe o arquivo

    //Envia o ACK;
    FILE *arq = fopen("ack.json", "r");
    envio(arq, socket_server, server);
    printf("ACK enviado com sucesso.\n");
    if(arq)
        fclose(arq);
    //Digito a resposta
    arq = fopen("mensagemResposta.json", "r");
    //Envio a resposta
    envio(arq, socket_server, server);

    //Espera o ACK
    preencher_json(socket_server, client);//Recebe o arquivo

    printf("Encerrando o servidor.\n");

    close(socket_server);

    return 0;
}