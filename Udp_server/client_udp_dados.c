#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>


int main(int argc, char** argv) {

	int client_socket, bytes, rv;
  struct sockaddr_in6;
  char buffer[128];
	fd_set fds;
	clock_t inicio, final , startTime , endTime;

  	// Esta é a nova estrutura que vamos utilizar!
	struct addrinfo hints, *list, *item;
	/* Checking the arguments */
  	if(argc != 3) {
    	printf("\n[CLIENTE] Erro de Argumento.\n\n");
    	exit(1);
  	}

  	memset(&hints, 0, sizeof hints); // Enche de zeros na nova estrutura
  	hints.ai_family = AF_UNSPEC;     // aceitar IPv4 ou IPv6
  	hints.ai_socktype = SOCK_DGRAM; // Apenas UDP

  	if((rv = getaddrinfo(argv[1], argv[2], &hints, &list)) != 0) { // Chama a função passando os dois argumentos
    	printf("[CLIENTE] Erro de getaddrinfo: %s\n", gai_strerror(rv));
    	exit(1);
  	}


 // ------------------------------------------------------------
 // Para cada item obtido da função....
 	for(item = list; item != NULL; item = item->ai_next) {
    // Tenta criar o socket
    	if((client_socket = socket(item->ai_family, item->ai_socktype, item->ai_protocol)) == -1) {
      		continue;
    	}
		// Se criar o socket, tenta realizar a conexão:
    	if(connect(client_socket, item->ai_addr, item->ai_addrlen) == -1) {
      		close(client_socket); // Não deu certo a conexão! Fecha o socket criado e tenta de novo.
      		printf("[CLIENTE]: Erro de conexao\n");
      		continue;
    	}
    	break;
    }

  if(item == NULL) exit(1); // Caso todos os itens falhem, será o fim da lista.
 // ------------------------------------------------------------
 // A partir deste ponto, estamos conectados!
 // ------------------------------------------------------------


 	char msg[20];
  printf("[CLIENTE] Conectado!\n");
  	while(1)
		{
			FD_ZERO(&fds);//Reseta todos os bits
      FD_SET (client_socket, &fds);

			memset(&msg, 0, sizeof(msg)); //Zera Memoria da variável
			memset(&buffer, 0, sizeof(buffer));
			int i, aux;
			inicio = clock();
			FILE *arq_send = fopen("envio.txt", "w");

			for (i=0; i < 10000; i++)
			{
				final = clock();
				aux = (final - inicio)/1000;
				sprintf(msg, "%d %d\n", i , aux );
				fprintf(arq_send, "%s", msg);
				bytes = strlen(msg);
				write(client_socket, msg , bytes);
				startTime = clock();
				endTime = clock();
				printf("[CLIENTE] mensagem %d enviada\n", i);
				while ((endTime - startTime )/1000 < 5) {
					endTime = clock();
				}

  		}
			fclose(arq_send);

			*msg = 'S';
			bytes = strlen(msg);
			write(client_socket, msg , bytes);
			break;
		}
  	close(client_socket); // Releasing the socket.
  	freeaddrinfo(list); // liberando a memória!!
	return 0;
}
