#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>
#include "client.h"
#include "server.h"

int main(){
    char Mensagem[1000];
    char IpDestino[15];
    clock_t timestamp;
    JsonEnvio JsonE;
    mainServer();
    while(true){
        printf("\nIP Destino:");
        scanf("%s", IpDestino);
        printf("\nMensagem:");
        scanf("%s", Mensagem);
        strcpy(JsonE.IpDestino, IpDestino);
        strcpy(JsonE.IpOrigem, ColetarIP());
        strcpy(JsonE.Mensagem, Mensagem);
        JsonE.Timestamp = clock() / CLOCKS_PER_SEC;
        envio(JsonE);
        //Json
    }
    return 0;
}