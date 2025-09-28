#include<stdio.h>
#include<stdlib.h>

struct paciente{
    int index;
    string cor;
    p* prox;
}; 
typedef struct  paciente Paciente;

struct fila{
    int inicial;
    int final;
    float vet[n];
};
typedef struct fila Fila;

Fila*fila_cria(void){
    Fila * f=(Fila)malloc(sizeof(Fila));
    f->n=0;
    f->ini=0;
    return f;
}



