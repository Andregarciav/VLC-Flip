#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include "server.h"

int main(int argc, char** argv) {
  int server_socket, client_socket, bytes, v6only, pid, status = 0;
  char buffer[128], client_ip[150], buffer_out[128];
  unsigned int  size;
  /* New struct ! */
  struct sockaddr_in6 server_addr, client_addr;
  //Verificando se foi digitado a porta de comunicação
  if(argc != 2)
  {
  printf("\n[Servidor] Voce nao digitou a porta.\n\n");
  exit(1);
  }
  //Cria o socket
  server_socket = socket(AF_INET6, SOCK_STREAM, 0);  // AF_INET6 --> IPv6, SOCK_STREAM --> TCP
  if (server_socket == -1) //verifica se socket foi criado com sucesso
  {
  printf("\n[Servidor] Erro ao criar o socket.\n\n");
  exit(1);
  }
  /* Socket rodando IPv4 and IPv6 */
  v6only = 0;
  if (setsockopt(server_socket, IPPROTO_IPV6, IPV6_V6ONLY, &v6only, sizeof(v6only)) != 0) //verifica o socket
  {
  printf("\n[Servidor] Socket IPv6/IPv4 error.\n\n");
  exit(1);
  }
  /* Configure settings in address struct */
  memset(&server_addr, 0, sizeof(server_addr));   // Cleaning the entire struct

  server_addr.sin6_family = AF_INET6;           // IPv6
  server_addr.sin6_addr = in6addr_any;          // Any IP address for the server
  server_addr.sin6_port = htons(atoi(argv[1])); // Gets the port number by the first argument
  /* Bind socket with address struct */
  if(bind(server_socket, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0)
  {
  printf("\n[Servidor] Erro de Bind\n\n");
  exit(1);
  }

  /* Initialize size variable to be used later on */
  size = sizeof(struct sockaddr_in6);
  listen(server_socket, 5); // Transform the socket in an TCP listener, waiting for TCP connections.
  while(1)
  {
    // If a new client try to connect, ANOTHER socket is created just for it (client_socket).
    printf("[Servidor] Aguardando clientes...\n\n");
    client_socket = accept(server_socket, NULL, NULL); // Blocks the execution waiting por clients
    if (client_socket < 0)
    { // Test the new socket.
      perror("[Servidor] Error na conexão.\n");
      exit(1);
    }
    pid = fork(); // Fork!

    if (pid > 0)
    {
      // Processo Pai

      // Getting the information about the new client and putting on client_ip.
      getpeername(client_socket, (struct sockaddr *) &client_addr, &size);
      inet_ntop(AF_INET6, &client_addr.sin6_addr, client_ip, sizeof(client_ip));
      printf("[Processo pai] Cliente [%s:%d] Connectado!\n\n", client_ip, ntohs(client_addr.sin6_port));

      close(client_socket); // client_socket is not useful anymore
    }
    else if(pid == 0)
      {
      // Inicio do processo filho
      close(server_socket); // server_socket is not useful anymore
      while(1)
        {
        memset(&buffer, 0, sizeof(buffer));
        bytes = read(client_socket, buffer, 128);

        if(strcmp(buffer, "q") == 0 || bytes < 0) break;

        printf("[Processo filho - %d] Menssagem Recebida:\"%s\"\n", getpid(), buffer);
        main_in(buffer , buffer_out);
        /*for(i = 0; i < strlen(buffer); i+=2) {
          buffer[i] = toupper(buffer[i]);
        }*/

        printf("[Processo filho %d] Responde: %s\n\n", getpid(),  buffer_out);
        bytes = send(client_socket, buffer_out, sizeof(buffer_out), 0);
      }
      printf("[Processo filho %d] Conexao Fechada.\n\n", getpid());
      close(client_socket); // ending child.
      exit(0);
    }
    else
    {
      perror("[TCP Master] fork() Error.\n");
      break;
    }
  }
  while(waitpid(-1, &status, 0) > 0); // Waiting for all children to end
  close(server_socket); // Releasing the socket of the server
  return 0;
}
