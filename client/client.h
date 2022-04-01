#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include "json.h"

#define SIZE 1024

void send_file(FILE *data, int sockfd,struct sockaddr_in server_addr);

JsonEnvio preencher(JsonEnvio data, int port);