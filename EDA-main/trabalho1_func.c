#include "trabalho1.h"
#include <ctype.h>

static void anexar_paciente(Paciente* nodo, Paciente** inicio, Paciente** fim){
    nodo->prox = NULL;
    if(*fim != NULL){
        (*fim)->prox = nodo;
    }else{
        *inicio = nodo;
    }
    *fim = nodo;
}

static const char* extrai_cor(const char* registro){
    const char* ultima_barra = strrchr(registro, '-');
    if(ultima_barra != NULL && *(ultima_barra + 1) != '\0'){
        return ultima_barra + 1;
    }
    return registro;
}

Fila*fila_cria(void){
    /*cria lista */
    Fila * f = (Fila*)malloc(sizeof(Fila));  
    f->inicio = NULL;     
    f->fim = NULL;   
    return f;
}
void fila_insere(Fila* f, char* v ){
    /*insere a item na lista*/
    Paciente* n=(Paciente*)malloc(sizeof(Paciente));
    // Aloca e copia a string
    n->cor = (char*)malloc(strlen(v) + 1);
    strcpy(n->cor, v);
    n->prox=NULL;
    if(f->fim!=NULL)
        f->fim->prox=n;
    else
        f->inicio=n;
    f->fim=n;
}
char* retira_fila(Fila* f){
    /*retira um item da fila*/ 
    Paciente* t;
    char* v; 
    if(fila_vazia(f)){
        printf("vazio\n");
        exit(1);
    }
    t=f->inicio;
    v=t->cor;
    f->inicio=t->prox;
    if(f->inicio==NULL)
        f->fim=NULL;
    free(t);
    return v; 
}

int fila_vazia(Fila* f){
    return (f->inicio == NULL);
}

void fila_libera(Fila* f ){
    /*vai liberar a fila */
    Paciente* q= f-> inicio;
    while(q!=NULL){
        Paciente* t=q->prox;
        free(q->cor);  // Libera a string também
        free(q);
        q=t;
    }
    free(f); 
}

Fila* arq_lista( FILE*arq){
    /*le o arquivo e me retorna uma lista */
    Fila* f = fila_cria();
    char buffer[100];
    while(fgets(buffer, sizeof(buffer), arq)){
        buffer[strcspn(buffer, "\r\n")] = '\0';
        size_t len = strlen(buffer);
        while(len > 0 && isspace((unsigned char)buffer[len-1])){
            buffer[--len] = '\0';
        }
        fila_insere(f, buffer);
    }
    return f;
}

void fila_imprime(Fila* f){
    /*imprime todos os elementos da fila*/
    if(f == NULL || fila_vazia(f)){
        printf("Fila vazia\n");
        return;
    }

    Paciente* atual = f->inicio;
    while(atual != NULL){
        printf("%s\n", atual->cor);
        atual = atual->prox;
    }
}

void ordena_fila(Fila* f){
    /*ordena a fila na ordem correta*/
    if(f == NULL || fila_vazia(f)){
        return;
    }

    Paciente *inicio_vermelho = NULL, *fim_vermelho = NULL;
    Paciente *inicio_amarelo = NULL, *fim_amarelo = NULL;
    Paciente *inicio_verde = NULL, *fim_verde = NULL;

    Paciente* atual = f->inicio;
    while(atual != NULL){
        Paciente* proximo = atual->prox;
        const char* cor = extrai_cor(atual->cor);

        if(strcmp(cor, "vermelha") == 0){
            anexar_paciente(atual, &inicio_vermelho, &fim_vermelho);
        }else if(strcmp(cor, "amarela") == 0){
            anexar_paciente(atual, &inicio_amarelo, &fim_amarelo);
        }else{
            anexar_paciente(atual, &inicio_verde, &fim_verde);
        }

        atual = proximo;
    }

    Paciente* novo_inicio = NULL;
    Paciente* novo_fim = NULL;

    if(inicio_vermelho != NULL){
        novo_inicio = inicio_vermelho;
        novo_fim = fim_vermelho;
    }

    if(inicio_amarelo != NULL){
        if(novo_inicio == NULL){
            novo_inicio = inicio_amarelo;
        }else{
            novo_fim->prox = inicio_amarelo;
        }
        novo_fim = fim_amarelo;
    }

    if(inicio_verde != NULL){
        if(novo_inicio == NULL){
            novo_inicio = inicio_verde;
        }else{
            novo_fim->prox = inicio_verde;
        }
        novo_fim = fim_verde;
    }

    if(novo_fim != NULL){
        novo_fim->prox = NULL;
    }

    f->inicio = novo_inicio;
    f->fim = novo_fim;
}