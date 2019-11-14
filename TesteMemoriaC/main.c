#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

#include "f_estrutura.h"
#include "geracoes.h"

int main()
{
    int tamanho;
    int tamanho_inicial = 0;
    int tamanho_final = 99999;
    int saltos = 1000;
    int repeticoes = 100;
    int i, j;                                                           //variaveis dos laços: inserção, busca
    int faixa_init ;                                                    //inicio da busca
    int faixa_final;                                                    //fim da busca
    int var_aleatoria;                                                  //variavel para a busca aleatoria

    double inicio;
    double fim;
    double tempo = 0;

    struct timeval t0;
    struct timeval t1;

    FILE *p_arq;
    p_arq = fopen("saidas_de_tempo_C.m", "w");                          //abertura de arquivo para escrita
    srand( (unsigned)time(NULL) );
//=====================================================================================================================

    printf("\nTeste de struct em lista .C!\n");

    pessoa *LISTA = malloc(sizeof(pessoa));

    if(!LISTA) {
        printf("\nMemoria indisponivel\n");
    }
    else {
        printf("\nLista iniciada\n");
        iniciar_lista(LISTA);
        for(i = 0; i < 100000; i++) {
            inserir(LISTA, gera_string(), i, gera_idade(), gera_cep(), gera_num(), gera_string());
        }
        //Se necessário ...
        //exibir_lista(LISTA);

//=====================================================================================================================

        fprintf(p_arq, "valores = [\n");

        for(tamanho = tamanho_inicial; tamanho <= tamanho_final; tamanho += saltos) {

            faixa_init  = tamanho;
            faixa_final = tamanho + saltos;

            gettimeofday(&t0, NULL);

            for(j = 0; j < repeticoes; j++){
                var_aleatoria = faixa_init + (rand() % faixa_final);
                buscar(LISTA, var_aleatoria);
            }

            gettimeofday(&t1, NULL);

            inicio = t0.tv_sec + t0.tv_usec/1000000.0;
            fim    = t1.tv_sec + t1.tv_usec/1000000.0;

            tempo = tempo + (fim - inicio);

            printf("\nTamanho: %d,  tempo: %f ms", tamanho, tempo);
            fprintf(p_arq, "%d\t%f\n", tamanho, tempo);

        }

        fprintf(p_arq, "]");

        fclose(p_arq);

        printf("\n\nArquivo .m gerado. Checar pasta do projeto.\n");
//=====================================================================================================================
    }

    free(LISTA);

    return 0;
}
