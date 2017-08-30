#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <ctype.h>

#define MAX 128
typedef struct newUser
{
  char tipo;
  char login[15];
  int senha;
  char arquivo[MAX];
  char conteudo[MAX];
}novo;

int verificaUsuario(char *usuario);

int escreveUsuario(char *usuario, int pass);

int verificaSenha(char *usuario, int pass);

int verificaArquivo (char *usuario, char *file, char *conteudo);

int escreveArquivo (char *usuario, char *file, char *conteudo);

int abreAux(char *usuario, char *file , char * conteudo);

int buscaArquivo( char *usuario, char *file , FILE *saida);

int imprimeArquivo(char *usuario, FILE *saida);

int main_in(char *buffer_in, char *buffer_out);
