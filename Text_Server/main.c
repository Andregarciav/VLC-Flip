#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <ctype.h>
#include "server.h"


int main_in(char *buffer_in, char *buffer_out)
{
  FILE *arq = fopen("string_in.txt" ,"w");
  fprintf(arq, "%s\n", buffer_in);
  fclose(arq);
  arq = fopen("string_in.txt", "r");
  int aux;
  FILE *arq_out = fopen("string_out.txt", "w");
  novo *msg=calloc( 1 , sizeof(novo));
  fscanf(arq, "%c", &msg->tipo);
  msg->tipo = toupper(msg->tipo);
  if (msg->tipo == 'N')
  {
    fscanf(arq,"%s %d", msg->login , &msg->senha);
    aux = verificaUsuario(msg->login);
    if (aux == -1)
      fprintf(arq_out,"N %d\n", aux);
    else
    {
      escreveUsuario(msg->login , msg->senha);
      fprintf(arq_out,"N 0");
    }
  }
  if (msg->tipo == 'S')
  {
    fscanf(arq, "%s %d" ,  msg->login , &msg->senha);
    aux = verificaUsuario(msg->login);
    if (aux == -1)
    {
      aux = verificaSenha(msg->login , msg->senha);
        if (aux == 0)
        {
          fscanf(arq,"%s %[^\n]s" , msg->arquivo , msg->conteudo);
          aux = verificaArquivo(msg->login , msg->arquivo, msg->conteudo);
            if(aux == 1)
            {
              fprintf (arq_out,"S 1");
              abreAux(msg->login , msg->arquivo , msg->conteudo);
            }
            if (aux == 0)
            {
              escreveArquivo(msg->login , msg->arquivo, msg->conteudo);
              fprintf(arq_out, "S 0" );
            }
        }
        if (aux == 2)
        {
              fprintf(arq_out,"S -2");
        }
    }
    else
    {
      fprintf(arq_out,"S -1");
    }
  }
  if (msg->tipo == 'R')
  {
    fscanf(arq,"%s %d" ,  msg->login , &msg->senha);
    aux = verificaUsuario(msg->login);
    if (aux == -1)
    {
      aux = verificaSenha(msg->login , msg->senha);
        if (aux == 0)
        {
          fscanf(arq ,"%s" , msg->arquivo);
          aux = buscaArquivo(msg->login , msg->arquivo , arq_out);
            if(aux == -3 )
            {
              fprintf (arq_out,"R -3");
            }
        }
        if (aux == 2)
        {
              fprintf(arq_out,"R -2");
        }
    }
    else
    {
      fprintf(arq_out,"R -1");
    }
  }
  if (msg->tipo == 'L')
  {
    fscanf(arq,"%s %d" ,  msg->login , &msg->senha);
    aux = verificaUsuario(msg->login);
    if (aux == -1)
    {
      aux = verificaSenha(msg->login , msg->senha);
        if (aux == 0)
        {
          fprintf( arq_out, "L 0" );
          imprimeArquivo(msg->login, arq_out);
        }
        if (aux == 2)
        {
              fprintf(arq_out,"L -2");
        }
    }
    else
    {
      fprintf(arq_out,"L -1");
    }
  }
  fclose(arq);
  fclose(arq_out);
  arq_out = fopen("string_out.txt" , "r");
  fscanf(arq_out, "%[^\n]s", buffer_out);
  free(msg);
  return 0;
}
