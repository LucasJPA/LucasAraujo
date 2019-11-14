/************************************************************************************************************************************************************************
*Resolução dos exercicios C for Linux v 2.0.5
*Lucas araujo
*Data: 02/03/2019

 Exercicio 5: leilão de animais
************************************************************************************************************************************************************************/

#include <stdio.h>

int main()
{
	int tipo, qtd;
	float precoU, total, comissao;
	char opcao;
	
	printf("\nLeilão de animais\n\n");
	
	do{
		printf("\n[1] Bovinos\n[2] Equinos\n[3] Ovinos");
		
		printf("\n\nEscolha: ");
		scanf("%d", &tipo);
		
		if(tipo == 1)
			printf("Tipo escolhido: Bovinos");
		
		if(tipo == 2)
			printf("Tipo escolhido: Equinos");
		
		if(tipo == 3)
			printf("Tipo escolhido: Ovinos");
		
		printf("\n\nPreço unitário do animal: ");
		scanf("%f", &precoU);
		
		printf("Quantidade de animais: ");
		scanf("%d", &qtd);
		
		total = precoU * qtd;
		
		printf("\n\nPreço total pago (R$): %.2f", total);
		
		if(tipo == 1) {
			comissao = total * 0.05;
			printf("\nComissão a pagar (R$): %.2f", comissao);
		}
		
		if(tipo == 2) {
			comissao = total * 0.07;
			printf("\nComissão a pagar (R$): %.2f", comissao);
		}
		
		if(tipo == 3) {
			comissao = total * 0.03;
			printf("\nComissão a pagar (R$): %.2f", comissao);
		}
		
		printf("\n\nContinuar: ");
		scanf(" %c", &opcao);
		
	}while(opcao == 's' || opcao == 'N');
	
	printf("\nSessão encerrada");
			
	printf("\n\n");
	
	return 0;
}
