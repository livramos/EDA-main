#include <trabalho1.h>
struct paciente{
    char* cor;
    struct paciente* prox;  
}; 
struct fila{
    Paciente* inicio;
    Paciente* fim;
};

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
    n->cor= v;
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
        buffer[strcspn(buffer, "\n")] = 0;  // Remove newline
        fila_insere(f, strdup(buffer));
    }
    return f;
}

void ordena_fila(Fila*f){
    /*ordena a fila na ordem correta*/
}