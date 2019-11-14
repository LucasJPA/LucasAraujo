#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "geracoes.h"


//geração de cep aleatorio
int gera_cep()
{
    int cep_gerado;

    cep_gerado = 10000000 + (rand()%99999999);

    return cep_gerado;
}

//geração de idade aleatorio
int gera_idade()
{
    int idade;

    idade = 1 + (rand()%100);

    return idade;
}

//geração de numero de residencia
int gera_num()
{
    int num_casa;

    num_casa = 10 + (rand()%9999);

    return num_casa;
}

//geração de strings aleatórias para nomes e complementos
char *gera_string()
{
    char *validchars = " abcdefghijklmnopqrstuvwxyz";
    char *novastr;
	int i;
    int str_len;

    str_len = ( rand() % MAX_STR_SIZE );

    str_len += ( str_len < MIN_STR_SIZE) ? MIN_STR_SIZE : 0;

    novastr = malloc((str_len + 1) * sizeof(char));

    if( !novastr )
    {
        printf( "\n[*} Erro ao alocar memoria\n" );

        exit( EXIT_FAILURE );
    }

    for( i = 0; i < str_len; i++ )
    {
        novastr[i] = validchars[rand() % strlen(validchars)];
    }
	novastr[i] = '\0';

	return novastr;
}
