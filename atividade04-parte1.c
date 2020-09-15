#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
	gcc atividade04-parte1.c -o exec -pedantic -Wall

*/

typedef struct ppp{
	char bits[9];
	struct ppp *prox;
}ppp;	

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
	/* IMPRIME BINARIOS*
	for (i = 0; i <= *size; i++)
	{
		printf("%d ", result_binary[i]);
	}*/

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

			printf("payload: %s\n", payload->bits);
			printf("    aux: %s\n", aux->bits);

			puts("---------------------------------");

			carry = 0;
			result[8] = '\0';

			for(i = 7; i >= 0 ; i--){

				printf("payload[%d]: %c\n", i, payload->bits[i]);
				printf("    aux[%d]: %c\n", i, aux->bits[i]);
				printf("    aux: %c%c%c%c\n", aux->bits[0],aux->bits[1],aux->bits[2],aux->bits[3]);


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

			getch();
		}

		printf(" result: %s\n\n", result);

		//printf("check: %s\n", payload->bits);

		payload = payload->prox;
		aux = payload->prox;
	}
	getch();
}


void build_frame(int *result_binary, ppp *frames, int size){

	int i;
	ppp *flag1 = (ppp *) malloc(sizeof(ppp));
	ppp *flag2 = (ppp *) malloc(sizeof(ppp));
	ppp *address = (ppp *) malloc(sizeof(ppp));
	ppp *control = (ppp *) malloc(sizeof(ppp));
	ppp *lst;//, *check;

	frames = flag1;

	strcpy(flag1->bits,"01111110");
	flag1->prox = address;
	strcpy(address->bits,"11111111");
	address->prox = control;

	strcpy(control->bits,"00000001");
	control->prox = NULL;

	lst = control;


	for (i = 1; i <= size; i++){
		
		build_payload(&lst,to_char(result_binary[i]));
		
	}

	checksum(control->prox);

	printf("saida: %s ", lst->bits);

	lst->prox = flag2;
	
	strcpy(flag2->bits,"01111110");
	flag2->prox = NULL;
	print_output(frames);
}


int main(void){

	int result_decimal[1500];
	int result_binary[1500];
	int size;
	char p[4];
	char m[1500];
	


	ppp *frames;

	scanf("%s %s", p, m);

	to_decimal(result_decimal,m,&size);	

	to_binary(result_binary,result_decimal,&size);

	build_frame(result_binary,frames,size);

	getch();

}
