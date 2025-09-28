#include "trabalho1.h"

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
        buffer[strcspn(buffer, "\n")] = 0;  
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
    printf("Conteudo da fila:\n");
    while(atual != NULL){
        printf("%s\n", atual->cor);
        atual = atual->prox;
    }
}

/*void ordena_fila(Fila*f){
    // ordena a fila na ordem correta
}*/ 