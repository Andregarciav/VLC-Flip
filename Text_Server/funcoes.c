#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <ctype.h>
#include "server.h"

int verificaUsuario(char *usuario)
{
  FILE *arq;
  char buffer[MAX];
  char *nome = NULL ;
  arq = fopen("controle.txt" , "r");
  fgets ( buffer , MAX , arq);
  while (!feof(arq))
  {
    nome = strtok(buffer, ",");
    if( strcmp(nome, usuario) == 0)
    {
      fclose(arq);
      return -1;
    }
    fgets ( buffer , MAX , arq);
  }
  fclose(arq);
  return 1;
}

int escreveUsuario(char *usuario, int pass)
{
  FILE *arq;
  arq = fopen("controle.txt", "a");
  fprintf(arq, "%s,%d\n", usuario, pass);
  fclose(arq);
  return 0;
}

int verificaArquivo (char *usuario, char *file, char *conteudo)
{
  char *nomeArq , buffer[MAX];
  nomeArq = usuario;
  char *nome = NULL ;
  FILE *arq;
  arq = fopen(nomeArq , "r");
  //verica se cliente ja tinha arquivo  se não, cria
  if (arq == NULL)
  {
    arq = fopen(nomeArq , "w");
    //fprintf(arq , "%s,%s\n" , file , conteudo);
    fclose(arq);
    return 0;
  }
  //se cliente tem arquivo, procura string com nome do caminho
  else
  {
    fgets ( buffer , MAX , arq);
    while (!feof(arq))
    {
      nome = strtok(buffer, ",");
      //se nome do caminho existe retorna 1
      if( strcmp(nome, file) == 0)
      {
        fclose(arq);
        return 1;
      }
    }
      // se não, escreve caminho,conteudo fecha o arquivo e retorna 0
    fprintf(arq , "%s,%s\n" , file , conteudo);
    fclose(arq);
    return 0;
  }
}

int verificaSenha(char *usuario, int pass)
 {
   FILE *arq;
   char buffer[MAX];
   char *nome = NULL ;
   int senha;
   arq = fopen("controle.txt" , "r");
   fgets ( buffer , MAX , arq);
   while (!feof(arq))
   {
     nome = strtok(buffer, ",");
     senha = atoi(strtok(NULL, ","));
     if( strcmp(nome, usuario) == 0)
     {
       if (senha == pass)
       {
         fclose(arq);
         return 0;
       }
       return 2;
     }
     fgets ( buffer , MAX , arq);
   }
   fclose(arq);
   return 1;
 }

int escreveArquivo (char *usuario, char *file, char *conteudo)
{
  char *nomeArq , buffer[MAX];
  nomeArq = usuario;
  char *nome = NULL ;
  FILE *arq;
  arq = fopen(nomeArq , "a");
  fprintf(arq, "%s,%s\n", file , conteudo );
  fclose(arq);
}
int abreAux(char *usuario, char *file , char * conteudo)
{
  FILE *arq_r, *arq_w;
  char *nomeArq , buffer[MAX];
  nomeArq = usuario;
  char *nome = NULL;
  arq_w = fopen("aux.txt" , "w");
  arq_r = fopen(nomeArq , "r");
  fgets ( buffer , MAX , arq_r);
  while (!feof(arq_r))
  {
    nome = strtok(buffer, ",");
    if(strcmp(nome , file) == 0)
    {
      fgets ( buffer , MAX , arq_r);
    }
    fprintf(arq_w, "%s\n", buffer );
    fgets ( buffer , MAX , arq_r);
  }
  fprintf(arq_w, "%s,%s\n", file , conteudo);
  fclose(arq_w);
  fclose(arq_r);
  arq_w = fopen("aux.txt" , "r");
  arq_r = fopen(nomeArq , "w");
  fgets ( buffer , MAX , arq_w);
  while (!feof(arq_w))
  {
    fprintf(arq_r, "%s\n", buffer );
    fgets ( buffer , MAX , arq_w);
  }
  fclose(arq_w);
  fclose(arq_r);
  }
int buscaArquivo( char *usuario, char *file , FILE *saida)
{
  char *nomeArq , buffer[MAX];
  nomeArq = usuario;
  char *nome = NULL;
  char *conteudo = NULL;
  FILE *arq =  fopen(nomeArq , "r");
  fgets (buffer, MAX, arq);
  while (!feof(arq))
  {
    nome = strtok(buffer, ",");
    conteudo = strtok(NULL,"," );
    if (strcmp(nome, file) == 0)
    {
      fprintf(saida ,"R 0 %s\n", conteudo);
      return 0;
    }
    return -3;
  }
}
int imprimeArquivo(char *usuario , FILE *saida)
{
  char *nomeArq , buffer[MAX];
  nomeArq = usuario;
  char *nome = NULL;
  FILE *arq = fopen(nomeArq , "r");
  if (arq == NULL);
  return 3;
  fgets(buffer, MAX , arq);
  while (!feof(arq))
  {
    nome = strtok(buffer, ",");
    fprintf(saida , "%s ", nome);
  }
  return 4;
}
