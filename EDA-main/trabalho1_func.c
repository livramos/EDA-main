
#include<stdio.h>
#include<stdlib.h>

#define N 17 

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

Fila*fila_cria(void){
    /*cria lista */
    Fila * f = (Fila*)malloc(sizeof(Fila));  
    f->inicio = NULL;     
    f->fim = NULL;   
    return f;
}
void fila_insere(Fila* f, float v ){
    /*insere a item na lista*/
    Paciente* n=(Paciente*)malloc(sizeof(Paciente));
    n->cor= v;
    n->prox=NULL;
    if(f->fim!=NULL)
        f->fim->prox=n;
    else
        f->inicio=n;
        f->fim=n;
}
float retira_fila(Fila* f){
    /*retira um item da fila*/ 
    Lista*
}