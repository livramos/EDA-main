#include "trabalho1.h"

#include <ctype.h>
#include <stdio.h>

static void imprime_procedimento(const char* titulo, const char* complemento){
    if(titulo != NULL){
        printf("%s\n", titulo);
    }
    if(complemento != NULL && complemento[0] != '\0'){
        printf("%s\n", complemento);
    }
}

static void imprime_paciente_inline(const Paciente* paciente){
    if(paciente == NULL){
        return;
    }

    if(paciente->cor == NULL || paciente->cor[0] == '\0'){
        printf("%d -", paciente->id);
        return;
    }

    char primeira = (char)toupper((unsigned char)paciente->cor[0]);
    printf("%d - %c%s", paciente->id, primeira, paciente->cor + 1);
}

static void imprime_lista_com_contagem(const char* titulo, Fila* fila){
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

static int fila_contem_id(Fila* fila, int id){
    if(fila == NULL){
        return 0;
    }

    Paciente* atual = fila->inicio;
    while(atual != NULL){
        if(atual->id == id){
            return 1;
        }
        atual = atual->prox;
    }
    return 0;
}

static void inserir_eventos(Fila* origem, Fila* destino, int quantidade){
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

static void remover_paciente_e_imprimir(Fila* fila, int id){
    Paciente* removido = fila_retira_por_id(fila, id);
    if(removido != NULL){
        imprime_paciente_inline(removido);
        printf("\n");
        paciente_libera(removido);
    }
}

int main(void){
    FILE* arq = fopen("informacoes_trabalho1.txt", "r");
    if(arq == NULL){
        printf("ERRO NA ABERTURA DO ARQUIVO\n");
        return 1;
    }

    Fila* fila_remocoes = fila_cria();
    Fila* fila_chegadas = fila_cria();
    if(fila_remocoes == NULL || fila_chegadas == NULL){
        fprintf(stderr, "Erro ao alocar filas.\n");
        if(fila_remocoes != NULL){
            fila_libera(fila_remocoes);
        }
        if(fila_chegadas != NULL){
            fila_libera(fila_chegadas);
        }
        fclose(arq);
        return 1;
    }

    carregar_listas(arq, fila_remocoes, fila_chegadas);
    fclose(arq);

    Fila* fila_pacientes = fila_cria();
    if(fila_pacientes == NULL){
        fprintf(stderr, "Erro ao alocar fila de pacientes.\n");
        fila_libera(fila_remocoes);
        fila_libera(fila_chegadas);
        return 1;
    }

    inserir_eventos(fila_chegadas, fila_pacientes, 8);

    imprime_lista_com_contagem("a) Pacientes chegando no hospital:", fila_pacientes);

    ordena_fila(fila_pacientes);
    imprime_lista_com_contagem("a) Lista gerada computacionalmente:", fila_pacientes);

    Paciente* instrucao = fila_pop(fila_remocoes);
    if(instrucao != NULL){
        imprime_procedimento("b) paciente atendido:", NULL);
        remover_paciente_e_imprimir(fila_pacientes, instrucao->id);
        printf("\n");
        paciente_libera(instrucao);
    }
    ordena_fila(fila_pacientes);
    imprime_lista_com_contagem("b) Lista atualizada:", fila_pacientes);

    instrucao = fila_pop(fila_remocoes);
    if(instrucao != NULL){
        imprime_procedimento("c) paciente atendido:", NULL);
        remover_paciente_e_imprimir(fila_pacientes, instrucao->id);
        printf("\n");
        paciente_libera(instrucao);
    }
    ordena_fila(fila_pacientes);
    imprime_lista_com_contagem("c) Lista atualizada:", fila_pacientes);

    imprime_procedimento("d) chegada de novos pacientes:", "9 - Verde\n10 - Amarela\n11 - Vermelha\n12 - Amarela");
    inserir_eventos(fila_chegadas, fila_pacientes, 4);
    ordena_fila(fila_pacientes);
    imprime_lista_com_contagem("d) Lista atualizada:", fila_pacientes);

    imprime_procedimento("e) pacientes atendidos:", NULL);
    for(int i = 0; i < 2; ++i){
        instrucao = fila_pop(fila_remocoes);
        if(instrucao != NULL){
            remover_paciente_e_imprimir(fila_pacientes, instrucao->id);
            paciente_libera(instrucao);
        }
    }
    printf("\n");
    ordena_fila(fila_pacientes);
    imprime_lista_com_contagem("e) Lista atualizada:", fila_pacientes);

    printf("f) paciente 3 - Verde desiste do atendimento e vai embora\n");
    instrucao = fila_pop(fila_remocoes);
    if(instrucao != NULL){
        remover_paciente_e_imprimir(fila_pacientes, instrucao->id);
        paciente_libera(instrucao);
    }
    printf("\n");
    ordena_fila(fila_pacientes);
    imprime_lista_com_contagem("f) Lista atualizada:", fila_pacientes);

    fila_libera(fila_pacientes);
    fila_libera(fila_chegadas);
    fila_libera(fila_remocoes);
    printf("memoria foi liberada\n");

    return 0;
}