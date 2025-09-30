#include "trabalho1.h"

#include <ctype.h>
#include <string.h>

static void anexar_paciente(Paciente* nodo, Paciente** inicio, Paciente** fim){
    nodo->prox = NULL;
    if(*fim != NULL){
        (*fim)->prox = nodo;
    }else{
        *inicio = nodo;
    }
    *fim = nodo;
}

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

static void imprime_paciente(const Paciente* paciente){
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
        imprime_paciente(atual);
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

    Paciente *inicio_vermelho = NULL, *fim_vermelho = NULL;
    Paciente *inicio_amarelo = NULL, *fim_amarelo = NULL;
    Paciente *inicio_verde = NULL, *fim_verde = NULL;

    Paciente* atual = f->inicio;
    while(atual != NULL){
        Paciente* proximo = atual->prox;
        if(atual->cor != NULL && strcmp(atual->cor, "vermelha") == 0){
            anexar_paciente(atual, &inicio_vermelho, &fim_vermelho);
        }else if(atual->cor != NULL && strcmp(atual->cor, "amarela") == 0){
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
