#include <stdio.h>
#include <stdlib.h>

void to_decimal(int *result_decimal, char mensage_binary[800], int *size){

	int result = 0,i,j = 0, k, aux = 0, binary = 0, op = 1;
	char binary_char[100];

	i = 0;
	while(op){
		binary_char[j] = mensage_binary[i];
		j++;
		if (mensage_binary[i] == 32 || mensage_binary[i] == '\0'){

			binary = atoi(binary_char);

			for (k = 1; binary > 0; k *= 2){
				result +=  (binary % 10) * k;
				binary = binary/10;
			}
			result_decimal[aux] = result;
			aux++;
			result = 0;			
			j = 0;

			if (mensage_binary[i] == '\0')
			{
				op = 0;
			}
		}
		i++;
	}
}

void to_string(int *result_decimal){
	int b;
	for (b = 1; b <= result_decimal[0]; ++b)
	{
		printf("%c", result_decimal[b]); 
	}
}

int main(void){
	
	char mensage_binary[800];
	int result_decimal[80];
	int size;

	scanf("%[^\n]", mensage_binary);

	to_decimal(result_decimal,mensage_binary,&size);	

	to_string(result_decimal);

}