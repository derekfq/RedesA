#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <netdb.h>

int main()
{
    int sock, lenght, n;
    socklen_t fromlen;
    struct sockaddr_in server, from; 
    char buffer[1024];

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock < 0)
        printf("Erro na criação do socket");

    lenght = sizeof(server);
    bzero(&server, lenght);
    server.sin_family = AF_INET;
    server.sin_port = 8080;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(bind(sock, (struct sockaddr *)&server, lenght) < 0)
        printf("Erro no bind");

    while(1){
        n = recvfrom(sock, buffer, 1024, 0, (struct sockaddr *)&from, &fromlen);
        if(n < 0)
            printf("Erro no recebimento");
        printf("Data Recived: %s", buffer);

        n = sendto(sock, "ACK\n", 17, 0, (struct sockaddr *)&from, fromlen);
        if(n < 0)
            printf("Erro no envio");
    }
    close(sock);
        
	// char buffer[50] = {0};
	// struct sockaddr_in servaddr = {0};
	
	// int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	// if(sockfd == -1)
	// {
	// 	perror("failed to create socket");
	// 	exit(EXIT_FAILURE);
	// }
	
	// servaddr.sin_family = AF_INET;
	// servaddr.sin_port = htons(12345);
	// servaddr.sin_addr.s_addr = INADDR_ANY;
	
	// int rc = bind(sockfd, (const struct sockaddr *)&servaddr, 
	// 	sizeof(servaddr));
		
	// if(rc == -1)
	// {
	// 	perror("failed to bind");
	// 	close(sockfd);
	// 	exit(EXIT_FAILURE);
	// }
	// socklen_t len = 0;
	
    // while (1)
    // {
    //     int n = recvfrom(sockfd, (char *)buffer, 50, 0,(struct sockaddr *) &servaddr, &len);

	//     buffer[n] = '\n';
	//     printf("%s", buffer);

    //     char * hello = "I recived your message";
    //     //send ack

    //     len = sendto(sockfd, (const char *)hello, strlen(hello),
	//     	0, (const struct sockaddr *)&servaddr, sizeof(servaddr));
	//     if(len ==-1)
	//     {
	//     	perror("failed to send");
	//     }

    // }

	// close(sockfd);
    return 0;
}



// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>
// #include <arpa/inet.h>

// #define SIZE 1024

// // void send_file_data(FILE* fp, int sockfd, struct sockaddr_in addr)
// // {
// //   printf("send_file_data");
// //   int n;
// //   char buffer[SIZE];
// //   strcpy(buffer, "Rafa test ACK");
// //   // Sending the data
// //  // while (fgets(buffer, SIZE, fp) != NULL)
// //  // {
// //     printf("%s", buffer);
// //     printf("[SENDING] Data: %s", buffer);

// //     n = sendto(sockfd, buffer, SIZE, 0, (struct sockaddr*)&addr, sizeof(addr));
// //     if (n == -1)
// //     {
// //       perror("[ERROR] sending data to the server.");
// //       exit(1);
// //     }
// //     bzero(buffer, SIZE);
// //   //}

// //   // Sending the 'END'
// //   strcpy(buffer, "END");
// //   sendto(sockfd, buffer, SIZE, 0, (struct sockaddr*)&addr, sizeof(addr));

// //   fclose(fp);
// // }

// // void write_file(int sockfd, struct sockaddr_in addr)
// // {

// //   char* filename = "server.txt";
// //   int n;
// //   char buffer[SIZE];
// //   socklen_t addr_size;

// //   // Creating a file.
// //   FILE* fp = fopen(filename, "w");

// //   // Receiving the data and writing it into the file.
// //   while (1)
// //   {
// //     addr_size = sizeof(addr);
// //     n = recvfrom(sockfd, buffer, SIZE, 0, (struct sockaddr*)&addr, &addr_size);

// //     if (strcmp(buffer, "END") == 0)
// //     {
// //       break;
// //     }

// //     printf("[RECEVING] Data: %s", buffer);
// //     fprintf(fp, "%s", buffer);
// //     bzero(buffer, SIZE);
// //   }

// //   fclose(fp);
// // }

// int main()
// {

//   // Defining the IP and Port
//   char* ip = "127.0.0.1";
//   const int port = 8080;

//   // Defining variables
 
//   struct sockaddr_in server_addr, client_addr;
//   char buffer[SIZE];
//   int e;

//   // Creating a UDP socket
//   int server_sockfd = socket(AF_INET, SOCK_DGRAM, 0);
//   if (server_sockfd < 0)
//   {
//     perror("[ERROR] socket error");
//     exit(1);
//   }


//   server_addr.sin_family = AF_INET;
//   server_addr.sin_port = htons(12345);
//   server_addr.sin_addr.s_addr = INADDR_ANY;

//   e = bind(server_sockfd, (const struct sockaddr*)&server_addr, sizeof(server_addr));
//   if (e < 0)
//   {
//     perror("[ERROR] bind error");
//     exit(1);
//   }
// char BUFFER[50];


// //Espera resposta
// int size = recvfrom(server_sockfd, (void*) &BUFFER, 50, MSG_WAITALL, (struct sockaddr*) &client_addr, (socklen_t*) sizeof(client_addr));

// BUFFER[size] = '\n';
// printf("%s", BUFFER);

// strcpy(BUFFER, "I recived your message");
// //Envia mensagem 
// size = sendto(server_sockfd, (const char*) &BUFFER, 50, 0, (const struct sockaddr*) &client_addr, sizeof(client_addr));

// close(server_sockfd);

//   printf("[STARTING] UDP File Server started. \n");
//   write_file(server_sockfd, client_addr); //recebe

//   //manda ack 
//   FILE *fp = fopen("ack.json", "r");
//   if(!fp)
//     printf("Erro");
// usleep(3000000);
//   send_file_data(fp, server_sockfd, server_addr);


//   printf("[SUCCESS] Data transfer complete.\n");
//   printf("[CLOSING] Closing the server.\n");

//   close(server_sockfd);

//  return 0;
//}