#ifndef TRABALHO1_H
#define TRABALHO1_H

/*bibliotecas*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*definições */
#define N 17 

/*structs*/
struct paciente{
    char* cor;
    struct paciente* prox;  
}; 
typedef struct paciente Paciente;

struct fila{
    Paciente* inicio;
    Paciente* fim;
};
typedef struct fila Fila;

/*funções*/
Fila* fila_cria(void);
void fila_insere(Fila* f, char* v);
char* retira_fila(Fila* f);
int fila_vazia(Fila* f);
void fila_libera(Fila* f);
Fila* arq_lista(FILE* arq);
void ordena_fila(Fila* f);
void fila_imprime(Fila* f);

#endif