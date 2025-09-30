#include "trabalho1.h"

#include <ctype.h>
#include <string.h>

static char* dup_minusculo(const char* texto){
    if(texto == NULL){
        return NULL;
    }

    size_t len = strlen(texto);
    char* copia = (char*)malloc(len + 1);
    if(copia == NULL){
        return NULL;
    }

    for(size_t i = 0; i < len; ++i){
        copia[i] = (char)tolower((unsigned char)texto[i]);
    }
    copia[len] = '\0';
    return copia;
}

static Paciente* paciente_cria(char tipo, int id, const char* cor){
    Paciente* novo = (Paciente*)malloc(sizeof(Paciente));
    if(novo == NULL){
        return NULL;
    }

    novo->tipo = (char)tolower((unsigned char)tipo);
    novo->id = id;
    novo->cor = dup_minusculo(cor);
    if(cor != NULL && novo->cor == NULL){
        free(novo);
        return NULL;
    }
    novo->prox = NULL;
    return novo;
}

Fila* fila_cria(void){
    Fila* f = (Fila*)malloc(sizeof(Fila));
    if(f == NULL){
        return NULL;
    }

    f->inicio = NULL;
    f->fim = NULL;
    return f;
}

void fila_anexa_paciente(Fila* f, Paciente* paciente){
    if(f == NULL || paciente == NULL){
        return;
    }

    paciente->prox = NULL;
    if(f->fim != NULL){
        f->fim->prox = paciente;
    }else{
        f->inicio = paciente;
    }
    f->fim = paciente;
}

void fila_insere(Fila* f, char tipo, int id, const char* cor){
    if(f == NULL){
        return;
    }

    Paciente* novo = paciente_cria(tipo, id, cor);
    if(novo == NULL){
        fprintf(stderr, "Falha ao inserir paciente %c-%d-%s\n",
                tipo, id, cor != NULL ? cor : "?");
        return;
    }

    fila_anexa_paciente(f, novo);
}

Paciente* fila_pop(Fila* f){
    if(f == NULL || f->inicio == NULL){
        return NULL;
    }

    Paciente* removido = f->inicio;
    f->inicio = removido->prox;
    if(f->inicio == NULL){
        f->fim = NULL;
    }
    removido->prox = NULL;
    return removido;
}

Paciente* fila_retira_por_id(Fila* f, int id){
    if(f == NULL || f->inicio == NULL){
        return NULL;
    }

    Paciente* anterior = NULL;
    Paciente* atual = f->inicio;
    while(atual != NULL){
        if(atual->id == id){
            if(anterior == NULL){
                f->inicio = atual->prox;
            }else{
                anterior->prox = atual->prox;
            }
            if(atual == f->fim){
                f->fim = anterior;
            }
            atual->prox = NULL;
            return atual;
        }
        anterior = atual;
        atual = atual->prox;
    }
    return NULL;
}

int fila_contem_id(const Fila* f, int id){
    if(f == NULL){
        return 0;
    }

    const Paciente* atual = f->inicio;
    while(atual != NULL){
        if(atual->id == id){
            return 1;
        }
        atual = atual->prox;
    }
    return 0;
}

void paciente_libera(Paciente* paciente){
    if(paciente == NULL){
        return;
    }
    free(paciente->cor);
    free(paciente);
}

int fila_vazia(Fila* f){
    return f == NULL || f->inicio == NULL;
}

void fila_libera(Fila* f){
    if(f == NULL){
        return;
    }

    Paciente* atual = f->inicio;
    while(atual != NULL){
        Paciente* proximo = atual->prox;
        paciente_libera(atual);
        atual = proximo;
    }
    free(f);
}

static void trim(char* texto){
    if(texto == NULL){
        return;
    }

    char* inicio = texto;
    while(*inicio != '\0' && isspace((unsigned char)*inicio)){
        ++inicio;
    }

    char* fim = inicio + strlen(inicio);
    while(fim > inicio && isspace((unsigned char)fim[-1])){
        --fim;
    }
    *fim = '\0';

    if(inicio != texto){
        memmove(texto, inicio, (size_t)(fim - inicio) + 1);
    }
}

void carregar_listas(FILE* arq, Fila* iniciais, Fila* eventos){
    if(arq == NULL || iniciais == NULL || eventos == NULL){
        return;
    }

    char buffer[128];
    while(fgets(buffer, sizeof(buffer), arq) != NULL){
        buffer[strcspn(buffer, "\r\n")] = '\0';
        trim(buffer);
        if(buffer[0] == '\0'){
            continue;
        }

        char tipo = '\0';
        int id = 0;
        char cor[32];
        if(sscanf(buffer, " %c-%d-%31s", &tipo, &id, cor) != 3){
            continue;
        }

        if(tolower((unsigned char)tipo) == 'a'){
            fila_insere(iniciais, tipo, id, cor);
        }else if(tolower((unsigned char)tipo) == 'c'){
            fila_insere(eventos, tipo, id, cor);
        }
    }
}

void paciente_imprime(const Paciente* paciente){
    if(paciente == NULL){
        return;
    }

    if(paciente->cor == NULL || paciente->cor[0] == '\0'){
        printf("%d - \n", paciente->id);
        return;
    }

    char primeira = (char)toupper((unsigned char)paciente->cor[0]);
    printf("%d - %c%s\n", paciente->id, primeira, paciente->cor + 1);
}

void fila_imprime(Fila* f){
    if(f == NULL || fila_vazia(f)){
        printf("Fila vazia\n");
        return;
    }

    Paciente* atual = f->inicio;
    while(atual != NULL){
        paciente_imprime(atual);
        atual = atual->prox;
    }
}

void fila_contagem_por_cor(Fila* f, int* vermelha, int* amarela, int* verde){
    if(vermelha != NULL){
        *vermelha = 0;
    }
    if(amarela != NULL){
        *amarela = 0;
    }
    if(verde != NULL){
        *verde = 0;
    }

    if(f == NULL || fila_vazia(f)){
        return;
    }

    Paciente* atual = f->inicio;
    while(atual != NULL){
        if(vermelha != NULL && atual->cor != NULL && strcmp(atual->cor, "vermelha") == 0){
            (*vermelha)++;
        }else if(amarela != NULL && atual->cor != NULL && strcmp(atual->cor, "amarela") == 0){
            (*amarela)++;
        }else if(verde != NULL && atual->cor != NULL && strcmp(atual->cor, "verde") == 0){
            (*verde)++;
        }

        atual = atual->prox;
    }
}

void ordena_fila(Fila* f){
    if(f == NULL || fila_vazia(f)){
        return;
    }

    Fila vermelha = {NULL, NULL};
    Fila amarela = {NULL, NULL};
    Fila verde = {NULL, NULL};

    Paciente* atual = f->inicio;
    while(atual != NULL){
        Paciente* proximo = atual->prox;
        if(atual->cor != NULL && strcmp(atual->cor, "vermelha") == 0){
            fila_anexa_paciente(&vermelha, atual);
        }else if(atual->cor != NULL && strcmp(atual->cor, "amarela") == 0){
            fila_anexa_paciente(&amarela, atual);
        }else{
            fila_anexa_paciente(&verde, atual);
        }
        atual = proximo;
    }

    Fila* grupos[] = {&vermelha, &amarela, &verde};
    f->inicio = NULL;
    f->fim = NULL;

    for(size_t i = 0; i < sizeof(grupos) / sizeof(grupos[0]); ++i){
        if(grupos[i]->inicio == NULL){
            continue;
        }
        if(f->inicio == NULL){
            f->inicio = grupos[i]->inicio;
        }else{
            f->fim->prox = grupos[i]->inicio;
        }
        f->fim = grupos[i]->fim;
    }

    if(f->fim != NULL){
        f->fim->prox = NULL;
    }
}

void procedimento_imprime(const char* titulo, const char* complemento){
    if(titulo != NULL){
        printf("%s\n", titulo);
    }
    if(complemento != NULL && complemento[0] != '\0'){
        printf("%s\n", complemento);
    }
}

void fila_imprime_com_contagem(const char* titulo, Fila* fila){
    int vermelha = 0;
    int amarela = 0;
    int verde = 0;

    if(titulo != NULL){
        printf("%s\n", titulo);
    }
    fila_imprime(fila);
    fila_contagem_por_cor(fila, &vermelha, &amarela, &verde);
    printf("vermelha -%d, amarela -%d, verde -%d\n\n", vermelha, amarela, verde);
}

void fila_inserir_eventos(Fila* origem, Fila* destino, int quantidade){
    if(origem == NULL || destino == NULL || quantidade <= 0){
        return;
    }

    for(int i = 0; i < quantidade; ++i){
        Paciente* paciente = fila_pop(origem);
        if(paciente == NULL){
            break;
        }
        if(fila_contem_id(destino, paciente->id)){
            paciente_libera(paciente);
            continue;
        }
        fila_anexa_paciente(destino, paciente);
    }
}
