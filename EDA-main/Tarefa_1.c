// arvore.c
#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
    int chave;
    int altura;               
    struct nodo* esq;         
    struct nodo* dir;         
} Nodo;

// Função para criar um novo nodo
static Nodo* novo_nodo(int chave) {
    Nodo* n = (Nodo*)malloc(sizeof(Nodo));
    if (!n) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    n->chave = chave;
    n->altura = 0;     
    n->esq = n->dir = NULL;
    return n;
}

// Função para inserir um novo nodo na árvore
static void inserir(Nodo** raiz, int chave) {
    if (*raiz == NULL) {
        *raiz = novo_nodo(chave);
        return;
    }
    Nodo* at = *raiz;
    while (1) {
        if (chave < at->chave) {
            if (at->esq) at = at->esq;
            else { at->esq = novo_nodo(chave); break; }
        }
        else if (chave > at->chave) {
            if (at->dir) at = at->dir;
            else { at->dir = novo_nodo(chave); break; }
        }
        else {
           
            break;
        }
    }
}


static int computar_alturas(Nodo* n) {
    if (!n) return -1;
    int he = computar_alturas(n->esq);
    int hd = computar_alturas(n->dir);
    int h = (he > hd ? he : hd) + 1;
    n->altura = h;
    return h;
}

static void print_preordem(Nodo* n) {
    if (!n) return;
    printf("%d(%d) ", n->chave, n->altura);
    print_preordem(n->esq);
    print_preordem(n->dir);
}

static void print_simetrica(Nodo* n) {
    if (!n) return;
    print_simetrica(n->esq);
    printf("%d(%d) ", n->chave, n->altura);
    print_simetrica(n->dir);
}

static void liberar(Nodo* n) {
    if (!n) return;
    liberar(n->esq);
    liberar(n->dir);
    free(n);
}


static void criar_arquivo_entrada(const char* path) {
    
    int chaves[20] = {
        20, 30, 70, 50, 100, 60, 80, 90, 10, 40,
        5, 95, 25, 85, 35, 75, 65, 55, 45, 41
    };
    FILE* f = fopen(path, "w");
    if (!f) {
        perror("fopen escrita");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < 20; i++) {
        fprintf(f, "%d", chaves[i]);
        if (i + 1 < 20) fputc(' ', f);
    }
    fputc('\n', f);
    fclose(f);
}

static void ler_e_inserir(const char* path, Nodo** raiz) {
    FILE* f = fopen(path, "r");
    if (!f) {
        perror("fopen leitura");
        exit(EXIT_FAILURE);
    }
    int x;
    while (fscanf(f, "%d", &x) == 1) {
        inserir_bst(raiz, x);
    }
    fclose(f);
}

// ---------- main ----------
int main(void) {
    const char* arquivo = "entrada.txt";

//  cria o arquivo com as 20 chaves
    criar_arquivo_entrada(arquivo);

//  lê e insere 
    Nodo* raiz = NULL;
    ler_e_inserir(arquivo, &raiz);

// 3) computa e grava altura em cada nó 
    computar_alturas(raiz);

// 4) imprime 
    printf("Pre-ordem: ");
    print_preordem(raiz);
    printf("\n");

    printf("Simetrica: ");
    print_simetrica(raiz);
    printf("\n");

// 5) libera 
    liberar(raiz);
    return 0;
}
