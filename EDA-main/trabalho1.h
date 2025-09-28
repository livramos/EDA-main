/*bibliotecas*/
#include<stdio.h>
#include<stdlib.h>
/*definições */
#define N 17 
/*structs*/
typedef struct paciente Paciente;
typedef struct fila Fila;
/*funções*/
Fila*fila_cria(void);
void fila_insere(Fila* f, char* v );
char* retira_fila(Fila* f);
int fila_vazia(Fila* f);
void fila_libera(Fila* f );
