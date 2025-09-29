#include "trabalho1.h"
int main (void){
FILE*arq;
arq=fopen("informacoes_trabalho1.txt","r");
if(arq==NULL){
    printf("ERRO NA ABERTURA DO ARQUIVO\n");
    exit(1); 
}else{ 
  Fila* Lista_desorganizada=arq_lista(arq);
  printf("Lista original:\n");
  fila_imprime(Lista_desorganizada);
  fclose(arq);
  ordena_fila(Lista_desorganizada);
  printf("\nLista ordenada:\n");
  fila_imprime(Lista_desorganizada);
  fila_libera(Lista_desorganizada);
  printf("memoria foi liberada\n");
  /*fazendo o os casos de retorno*/
   printf("Pacientes chegando no hospital:\n");
} 
  return 0; 
}