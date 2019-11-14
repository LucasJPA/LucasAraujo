#ifndef F_ESTRUTURA_H
#define F_ESTRUTURA_H

struct Pessoa
{
    char nome[20];
    int id;
    int idade;
    int cep;
    int numero;
    char complemento[15];
    struct Pessoa *prox;
};
typedef struct Pessoa pessoa;

void iniciar_lista(pessoa *LISTA);
void inserir(pessoa *LISTA, char *p_nome, int id, int p_idade, int p_cep, int p_numero, char *p_comp);
void exibir_lista(pessoa *LISTA);
pessoa *buscar(pessoa *LISTA, int p_id);


#endif // F_ESTRUTURA_H
