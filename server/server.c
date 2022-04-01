#include "server.h"
#define SIZE 1024

void write_file(int sockfd){
    int n;
    FILE *fp;
    char *filename = "Response.json";
    char buffer[SIZE];
    fp = fopen(filename, "w");
    while (1){
        n = recv(sockfd, buffer, SIZE, 0);
        if (n <= 0){
            break;
            return;
        }
        fprintf(fp, "%s", buffer); // Arrumar para tipo jeisao###########
        bzero(buffer, SIZE);
    }
    return;
}

int main(){
    char *ip = ColetarIP();
    int port = 8080;
    int e,n;
    int sockfd, new_sock;
    struct sockaddr_in server_addr, new_addr;
    socklen_t addr_size;
    char buffer[SIZE];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0){
        perror("Erro no socket");
        exit(1);
    }
    printf("Socket do servidor criado com sucesso.\n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = port;
    server_addr.sin_addr.s_addr = inet_addr(ip);

    e = bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (e < 0){
        perror("Erro em criar a bind");
        exit(1);
    }
    printf("Binding feita com sucesso.\n");

    addr_size = sizeof(&new_addr);
    n = recvfrom(sockfd, (char *)buffer, SIZE,
                MSG_WAITALL, ( struct sockaddr *) &new_addr,
                &addr_size);
    buffer[n] = '\0';
    printf("Client : %s\n", buffer);
    /*
    if (listen(sockfd, 10) == 0)
        printf("Listening....\n");
    else{
        perror("Erro ao realizar listening");
        exit(1);
    }
*/
    // recive the file
    new_sock = accept(sockfd, (struct sockaddr *)&new_addr, &addr_size);
    if (new_sock != -1){
        write_file(new_sock);
        printf("Arquivo Recebido.\n");
    }
    else
        printf("Erro ao receber arquivo");

    JsonEnvio request = RecebeJsonEnvio();
    // Transferir do envio para o ack as infos importantes
    // send_ack
    JsonAck ACK;
    strcpy(ACK.Ip_origem, request.Ip_destino);
    strcpy(ACK.Ip_destino, request.Ip_origem);
    ACK.Porta_origem = request.Porta_destino;
    ACK.Porta_destino = request.Porta_origem;
    ACK.Timestamp_original = request.Timestamp;
    ACK.Timestamp_resposta = clock();
    ACK.Ack = true;
    MountJsonACK(ACK);
    FILE *fp = fopen("ACK.json", "r");
    //sendto ACK
    sendto(sockfd, (const char *)"Ack.json", fseek(fp, 0L, SEEK_END), MSG_CONFIRM, (const struct sockaddr *) &new_addr, sizeof(new_addr));

    //Resposta da mensagem e mandar a mensagem com o sendto....
    //sendto answer


    //Falta while_true do server

    // printf("Dados escritos no arquivo com sucesso.\n");
    //  Ta faltando Pegar a mensagem e possibilitar a resposta Direta somente escrevendo a mensagem
    return 0;
}