#include "trabalho1.h"

#include <stdio.h>

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

    fila_inserir_eventos(fila_chegadas, fila_pacientes, 8);

    fila_imprime_com_contagem("a) Pacientes chegando no hospital:", fila_pacientes);

    ordena_fila(fila_pacientes);
    fila_imprime_com_contagem("a) Lista gerada computacionalmente:", fila_pacientes);

    Paciente* instrucao = fila_pop(fila_remocoes);
    if(instrucao != NULL){
        procedimento_imprime("b) paciente atendido:", NULL);
        Paciente* removido = fila_retira_por_id(fila_pacientes, instrucao->id);
        if(removido != NULL){
            paciente_imprime(removido);
            paciente_libera(removido);
        }
        printf("\n");
        paciente_libera(instrucao);
    }
    ordena_fila(fila_pacientes);
    fila_imprime_com_contagem("b) Lista atualizada:", fila_pacientes);

    instrucao = fila_pop(fila_remocoes);
    if(instrucao != NULL){
        procedimento_imprime("c) paciente atendido:", NULL);
        Paciente* removido = fila_retira_por_id(fila_pacientes, instrucao->id);
        if(removido != NULL){
            paciente_imprime(removido);
            paciente_libera(removido);
        }
        printf("\n");
        paciente_libera(instrucao);
    }
    ordena_fila(fila_pacientes);
    fila_imprime_com_contagem("c) Lista atualizada:", fila_pacientes);

    procedimento_imprime("d) chegada de novos pacientes:", "9 - Verde\n10 - Amarela\n11 - Vermelha\n12 - Amarela");
    fila_inserir_eventos(fila_chegadas, fila_pacientes, 4);
    ordena_fila(fila_pacientes);
    fila_imprime_com_contagem("d) Lista atualizada:", fila_pacientes);

    procedimento_imprime("e) pacientes atendidos:", NULL);
    for(int i = 0; i < 2; ++i){
        instrucao = fila_pop(fila_remocoes);
        if(instrucao != NULL){
            Paciente* removido = fila_retira_por_id(fila_pacientes, instrucao->id);
            if(removido != NULL){
                paciente_imprime(removido);
                paciente_libera(removido);
            }
            paciente_libera(instrucao);
        }
    }
    printf("\n");
    ordena_fila(fila_pacientes);
    fila_imprime_com_contagem("e) Lista atualizada:", fila_pacientes);

    printf("f) paciente 3 - Verde desiste do atendimento e vai embora\n");
    instrucao = fila_pop(fila_remocoes);
    if(instrucao != NULL){
        Paciente* removido = fila_retira_por_id(fila_pacientes, instrucao->id);
        if(removido != NULL){
            paciente_imprime(removido);
            paciente_libera(removido);
        }
        paciente_libera(instrucao);
    }
    printf("\n");
    ordena_fila(fila_pacientes);
    fila_imprime_com_contagem("f) Lista atualizada:", fila_pacientes);

    fila_libera(fila_pacientes);
    fila_libera(fila_chegadas);
    fila_libera(fila_remocoes);
    printf("memoria foi liberada\n");

    return 0;
}