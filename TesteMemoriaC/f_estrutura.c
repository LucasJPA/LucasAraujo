#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "f_estrutura.h"


// Inicializa a lista com a raíz da lista
void iniciar_lista(pessoa *LISTA)
{
    LISTA->prox = NULL;
}


// Insere elementos na lista
void inserir(pessoa *LISTA, char *p_nome, int id, int p_idade, int p_cep, int p_numero, char *p_comp)
{
    pessoa *p_nova;
    pessoa *p_atual;

    // Alocação dinamica de memoria
    p_nova = malloc(sizeof(pessoa));

    if(p_nova == NULL)
    {
            printf("Erro, possivel falta de memoria\n\n");
            //return -1;
    }

    strcpy(p_nova->nome, p_nome);
    p_nova->id = id;
    p_nova->idade = p_idade;
    p_nova->cep = p_cep;
    p_nova->numero = p_numero;
    strcpy(p_nova->complemento, p_comp);

    if(LISTA->prox == NULL)     // Lista vazia
    {
        LISTA->prox = p_nova;
    }
    else
    {
        p_atual = LISTA->prox;

        while(p_atual->prox != NULL)
        {
            p_atual = p_atual->prox;
        }
        p_atual->prox = p_nova;
    }
}

void exibir_lista(pessoa *LISTA)
{
    if(LISTA->prox == NULL) {
        printf("\nLista vazia\n");
    }

    pessoa *p_atual;
    p_atual = LISTA->prox;

    printf("\nLista:\n");
    while(p_atual != NULL) {
        printf("\nID: %d", p_atual->id);
        printf("\nNome: %s", p_atual->nome);
        printf("\nIdade: %d", p_atual->idade);
        printf("\nCEP: %d", p_atual->cep);
        printf("\nNumero: %d", p_atual->numero);
        printf("\nComplemento: %s", p_atual->complemento);
        printf("\n\n");
        p_atual = p_atual->prox;
    }
}

pessoa *buscar(pessoa *LISTA, int p_id)
{
    pessoa *p_atual;
    p_atual = LISTA->prox;

    while(p_atual != NULL && p_atual->id == p_id) {
        p_atual = p_atual->prox;
    }

    return p_atual;
}
