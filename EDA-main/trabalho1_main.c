#include "trabalho1.h"
int main (void){
FILE*arq;
arq=fopen("informacoes_trabalho1.txt","r");
if(arq==NULL){
    printf("ERRO NA ABERTURA DO ARQUIVO\n");
    exit(1); 
}else{ 
  Fila* Lista_desorganizada=arq_lista(arq);
  print(Lista_desorganizada);
    fclose(arq);
  /*ordena_fila(Lista_desorganizada);
  fila_libera(Lista_desorganizada);*/

} 
  return 0; 
}