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
    int sock, fromlen, n;
    socklen_t lenght;
    struct sockaddr_in server, from; 
    char buffer[1024] = "Hello from client";

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock < 0)
        printf("Erro na criação do socket");

    lenght = sizeof(server);
    bzero(&server, lenght);
    server.sin_family = AF_INET;
    server.sin_port = 8080;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    n = sendto(sock, buffer, strlen(buffer), 0, (const struct sockaddr *)&server, lenght);
    if(n < 0)
        printf("Erro no envio");

    n = recvfrom(sock, buffer, 256, 0, (struct sockaddr *)&from, &lenght);
    if(n < 0)
        printf("Erro no recebimento");

    printf("Message recived: %s", buffer);

    close(sock);





	// char * hello = "hello from client";
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
	
	// int len = sendto(sockfd, (const char *)hello, strlen(hello),
	// 	0, (const struct sockaddr *)&servaddr, sizeof(servaddr));
	// if(len ==-1)
	// {
	// 	perror("failed to send");
	// }

    // //Recive ack 
    // char buffer[50] = {0};

    // socklen_t lenn = 0;
	
	// int n = recvfrom(sockfd, (char *)buffer, 50, 0, (struct sockaddr *)&serv addr, &lenn);

	// buffer[n] = '\n';
	// printf("%s", buffer);


	// close(sockfd);
	
    return 0;
}












// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>
// #include <arpa/inet.h>
// #define SIZE 1024

// // void write_file(int sockfd, struct sockaddr_in addr)
// // {
// // 
// //   char* filename = "ack.json";
// //   int n;
// //   char buffer[SIZE];
// //   socklen_t addr_size;
// // 
// //  Creating a file.
// //   FILE* fp = fp = fopen(filename, "w");
// // 
// //  Receiving the data and writing it into the file.
// //   while (1)
// //   {
//     // addr_size = sizeof(addr);
//     // n = recvfrom(sockfd, (char *)buffer, SIZE, MSG_WAITALL, 0, &addr_size);
// // 
//     // if (strcmp(buffer, "END") == 0)
//     // {
//     //   break;
//     // }
// // 
//     // printf("[RECEVING] Data: %s", buffer);
//     // fprintf(fp, "%s", buffer);
//     // bzero(buffer, SIZE);
// //   }
// // 
// //   fclose(fp);
// // }
// // 
// // void send_file_data(FILE* fp, int sockfd, struct sockaddr_in addr)
// // {
// //   int n;
// //   char buffer[SIZE];
// // 
// //  Sending the data
// //   while (fgets(buffer, SIZE, fp) != NULL)
// //   {
//     // printf("[SENDING] Data: %s", buffer);
// // 
//     // n = sendto(sockfd, buffer, SIZE, 0, (struct sockaddr*)&addr, sizeof(addr));
//     // if (n == -1)
//     // {
//     //   perror("[ERROR] sending data to the server.");
//     //   exit(1);
//     // }
//     // bzero(buffer, SIZE);
// //   }
// // 
// //  Sending the 'END'
// //   strcpy(buffer, "END");
// //   sendto(sockfd, buffer, SIZE, 0, (struct sockaddr*)&addr, sizeof(addr));
// // 
// //   fclose(fp);
// // }

// int main(void)
// {

//   // Defining the IP and Port
//   char *ip = "127.0.0.1";
//   const int port = 8080;
//   char BUFFER_IN[50];

//   // Defining variables
//   struct sockaddr_in server_addr;
// //   char *filename = "cliente.json";
// //   FILE *fp = fopen(filename, "r");

//   // Creating a UDP socket
//   int server_sockfd = socket(AF_INET, SOCK_DGRAM, 0);
//   if (server_sockfd < 0)
//   {
//     perror("[ERROR] socket error");
//     exit(1);
//   }

//   server_addr.sin_family = AF_INET;
//   server_addr.sin_port = port;
//   server_addr.sin_addr.s_addr = inet_addr(ip);

//   //send to server
//   char BUFFER[50] = "Hello from client";
//   int size = sendto(server_sockfd, (const void*) BUFFER, 50, 0, (const struct sockaddr *)&server_addr, (socklen_t)sizeof(server_addr));

//   //recive from server
//   size = recvfrom(server_sockfd, (void *)BUFFER, 50, 0, (struct sockaddr*)(&server_addr), (socklen_t*)sizeof(server_addr));

//   close(server_sockfd);
//   // Reading the text file
// //   if (fp == NULL)
// //   {
// //     perror("[ERROR] reading the file");
// //     exit(1);
// //   }

//   // Sending the file data to the server
// //   send_file_data(fp, server_sockfd, server_addr);

// //   printf("[SUCCESS] Data transfer complete.\n");

// //   //recive ACK 
// //   write_file(server_sockfd, server_addr);


// //   printf("[CLOSING] Disconnecting from the server.\n");

// //   close(server_sockfd);

//   return 0;
// }