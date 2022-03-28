#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include "json.h"

#define SIZE 1024

void send_file(JsonEnvio *data, int sockfd);

int envio(JsonEnvio data);
