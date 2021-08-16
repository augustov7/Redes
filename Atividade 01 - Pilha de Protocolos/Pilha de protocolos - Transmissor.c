#include <stdio.h>
#include <stdlib.h>

void  to_decimal(int *result_decimal,char mensage[80], int *size){
	int i;
	for (i = 0; i < 80 && mensage[i] != '\0'; i++)
	{
		result_decimal[i] = mensage[i];

	}
	*size = i;
}

void  to_binary(int *result_binary,int result_decimal[80], int *size){

	int aux = *size, result = 0, j = 1, i;

	while(aux != 0){
		result += j * (aux % 2);			
		j = j * 10;
		aux = aux/2;
	}
	result_binary[0] = result;

	for (i = 0; i < *size ; i++)
	{
		aux = result_decimal[i];
		result = 0;
		j = 1;

		while(aux != 0){
			result += j * (aux % 2);			
			j = j * 10;
			aux = aux/2;
		}
		result_binary[i+1] = result;
	}

	for (i = 0; i <= *size; i++)
	{
		printf("%d ", result_binary[i]);
	}

}

int main(void){
	
	char mensage[80];
	int result_decimal[80];
	int result_binary[80];
	int size;

	scanf("%[^\n]", mensage);

	to_decimal(result_decimal,mensage,&size);	

	to_binary(result_binary,result_decimal,&size);

}
