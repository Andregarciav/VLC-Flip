##### TP 3 ######

all: cliente servidor

cliente: client.c
	gcc -o cliente client.c -Wall -Wextra

servidor: server_fork.o main.o funcoes.o
	gcc -o servidor server_fork.o main.o funcoes.o

server_fork.o:  server_fork.c
	gcc -c server_fork.c -Wall -Wextra

main: main.o
	gcc -c main.c -Wall -Wextra

funcoes: funcoes.o
	gcc -c funcoes.c -Wall -Wextra

clean:
	rm cliente *.o
	rm servidor
