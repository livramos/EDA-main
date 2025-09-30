#ifndef TRABALHO1_H
#define TRABALHO1_H

/*bibliotecas*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*structs*/
struct paciente{
    char tipo;
    int id;
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
void fila_insere(Fila* f, char tipo, int id, const char* cor);
Paciente* fila_pop(Fila* f);
void fila_anexa_paciente(Fila* f, Paciente* paciente);
Paciente* fila_retira_por_id(Fila* f, int id);
void paciente_libera(Paciente* paciente);
int fila_vazia(Fila* f);
void fila_libera(Fila* f);
void carregar_listas(FILE* arq, Fila* iniciais, Fila* eventos);
void ordena_fila(Fila* f);
void fila_imprime(Fila* f);
void fila_contagem_por_cor(Fila* f, int* vermelha, int* amarela, int* verde);
void paciente_imprime(const Paciente* paciente);
int fila_contem_id(const Fila* f, int id);
void procedimento_imprime(const char* titulo, const char* complemento);
void fila_imprime_com_contagem(const char* titulo, Fila* fila);
void fila_inserir_eventos(Fila* origem, Fila* destino, int quantidade);

#endif