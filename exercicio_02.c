/************************************************************************************************************************************************************************
*Resolução dos exercicios C for Linux v 2.0.5
*Lucas araujo
*Data: 02/03/2019

 Exercicio 2: media aritimetica de notas
************************************************************************************************************************************************************************/

#include <stdio.h>

int main()
{
	float n1, n2, n3, n4, media;
	
	printf("\n\nCalculo de nota atravéz da média\n\n");
	
	printf("Nota 1: ");
	scanf("%f", &n1);
	
	printf("\nNota 2: ");
	scanf("%f", &n2);
	
	printf("\nNota 3: ");
	scanf("%f", &n3);
	
	printf("\nNota 4: ");
	scanf("%f", &n4);

	media = ( (n1 + n2 + n3 + n4)/4 ) ;
	
	printf("\n\nMédia final: %.2f", media);
	
	if(media >= 9.0)
		printf(" \tA ");
		
	if(media >= 7.5 && media < 9.0 )
		printf(" \tB ");
		
	if(media >= 6.0 && media < 7.5)
		printf(" \tC ");
	
	if(media < 6.0)
		printf(" \tD ");
		
	printf("\n\n");

	return 0;
}
