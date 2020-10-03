#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*
	gcc atividade04-parte1.c -o exec -pedantic -Wall
*/

typedef struct ppp{
	char bits[9];
	struct ppp *prox;
}ppp;

int hexadecimal(){

	char hex[4];
	int num, i = 0, aux = 0, result = 0;
	scanf("%s", hex);

	i = strlen(hex);
	
	i--;
	while (i >= 0)
	{
		if (hex[i] == 65)
		{
			result += 10 * pow(16, aux);
		}
		else
		{

			if (hex[i] == 66)
			{
				result += 11 * pow(16, aux);
			}
			else
			{
				if (hex[i] == 67)
				{
					result += 12 * pow(16, aux);

				}else{
					if (hex[i] == 68)
					{
						result += 13 * pow(16, aux);
					}else{
						if (hex[i] == 69)
						{
							result += 14 * pow(16, aux);
						}else{
							if (hex[i] == 70)
							{
								result += 14 * pow(16, aux);
							}else{
								if (hex[i] == 71)
								{
									result += 15 * pow(16, aux);
								}else{
									num = hex[i] - '0';
									result += num * pow(16, aux);
								}
							} 
						}
					}
				}
			}
		}
		aux++;
		i--;
	}

	return result;

}


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
}

void print_output(ppp *frames){

	while(frames != NULL){
		printf("%s ", frames->bits);
		frames = frames->prox;
	}

}

char* to_char(int inteiro){
	int i;
	char* result = (char*) malloc(9 * sizeof(char));

	result[8] = '\0';

	for (i = 7; i >= 0; i--){
		if((inteiro % 10) == 0){
			result[i] = '0';
		}else{
			result[i] = (inteiro % 10) + '0';
		}

		inteiro = inteiro/10;
	}	

	return result;
}

ppp* to_char2(int inteiro){/*ESPERA UM NUMERO INTEIRO DE ZEROS E UNS E TRANSFORMA NO MESMO NUMERO MAS COM ZEROS A ESQUERDA*/
int i;
char result[9];
ppp *protocol1 = (ppp *) malloc(sizeof(ppp));
ppp *protocol2 = (ppp *) malloc(sizeof(ppp));

result[8] = '\0';

for (i = 7; i >= 0; i--){	
	
	if (inteiro == 0){
		result[i] = 48;
	}else{

		if(inteiro % 2 == 1){
			result[i] = 49;
		}else{
			result[i] = 48;
		}
		
		inteiro = inteiro/2;
	}
}	

strcpy(protocol2->bits,result);


for (i = 7; i >= 0; i--){	
	
	if (inteiro == 0){
		result[i] = 48;
	}else{

		if(inteiro % 2 == 1){
			result[i] = 49;
		}else{
			result[i] = 48;
		}
		
		inteiro = inteiro/2;
	}
}	

strcpy(protocol1->bits,result);

protocol1->prox = protocol2;
protocol2->prox = NULL;

return protocol1;
}

void build_payload(ppp **lst, char *value){

	ppp *new = (ppp *) malloc(sizeof(ppp));

	new->prox = NULL;

	(*lst)->prox = new;

	strcpy(new->bits,value);

	(*lst)->prox = new;

	*lst = (*lst)->prox;

}

void checksum(ppp *payload){
	int i, carry;
	char result[8];
	ppp *aux = payload->prox;

	while(payload != NULL){

		if(payload->prox == NULL){

		}else{

			carry = 0;
			result[8] = '\0';

			for(i = 7; i >= 0 ; i--){

				if (payload->bits[i] == '1'){
					if (aux->bits[i] == '1'){
						if (carry == 1){
							result[i] = '1';
							carry = 1;
						}else{
							result[i] = '0';
							carry = 1;
						}					

					}else{
						if (carry == 1){
							result[i] = '0';
							carry = 1;
						}else{
							result[i] = '1';
							carry = 0;
						}
					}
				}else{
					if (aux->bits[i] == 1){
						if (carry == 1){
							result[i] = '0';
							carry = 1;
						}else{
							result[i] = '1';
							carry = 0;
						}
					}else{
						if (carry == 1){
							result[i] = '1';
							carry = 0;
						}else{
							result[i] = '0';
							carry = 0;
						}
					}
				}
			}
		}



		payload = payload->prox;
		aux = payload->prox;
	}
}


void build_frame(int *result_binary, ppp *frames, int size, int hexa){

	int i;
	ppp *flag1 = (ppp *) malloc(sizeof(ppp));
	ppp *flag2 = (ppp *) malloc(sizeof(ppp));
	ppp *address = (ppp *) malloc(sizeof(ppp));
	ppp *control = (ppp *) malloc(sizeof(ppp));
	ppp *lst;

	frames = flag1;

	strcpy(flag1->bits,"01111110");
	flag1->prox = address;
	strcpy(address->bits,"11111111");
	address->prox = control;

	strcpy(control->bits,"00000011");
	
	control->prox = to_char2(hexa);

	lst = (control->prox)->prox;


	for (i = 1; i <= size; i++){
		
		build_payload(&lst,to_char(result_binary[i]));
		
	}

	printf("%s ", lst->bits);

	lst->prox = flag2;
	
	strcpy(flag2->bits,"01111110");
	flag2->prox = NULL;
	print_output(frames);
}


int main(void){

	int result_decimal[1500];
	int result_binary[1500];
	int size;
	char m[1500];
	int hexa;


	hexa = hexadecimal();

	ppp *frames;

	scanf("%s", m);

	to_decimal(result_decimal,m,&size);	

	to_binary(result_binary,result_decimal,&size);

	build_frame(result_binary,frames,size,hexa);


}