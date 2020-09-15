#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

	//ppp *lst = frames;

	while(frames != NULL){
		printf("%s ", frames->bits);
		frames = frames->prox;
	}

}

char* to_char(int inteiro){
	int i;
	//char result[9];
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
	//ppp *p;

	new->prox = NULL;
	
	//printf("P: %s\n", p->bits);

	(*lst)->prox = new;

	strcpy(new->bits,value);

	(*lst)->prox = new;

	//printf("%s ", (*lst)->bits);

	*lst = (*lst)->prox;

}


void build_frame(int *result_binary, ppp *frames, int size){

	int i;
	ppp *flag1 = (ppp *) malloc(sizeof(ppp));
	ppp *flag2 = (ppp *) malloc(sizeof(ppp));
	ppp *address = (ppp *) malloc(sizeof(ppp));
	ppp *control = (ppp *) malloc(sizeof(ppp));
	ppp *lst;
	//ppp *protocol = (ppp *) malloc(sizeof(ppp));

	frames = flag1;
	//char teste[15] = ;

	strcpy(flag1->bits,"01111110");
	flag1->prox = address;
	//printf("flag1 %s\n", flag1->bits);
	//address->bits = {'1','1','1','1''1','1','1','1'};
	strcpy(address->bits,"11111111");
	//printf("address %s\n", address->bits);
	address->prox = control;

	//control->bits = {'0','0','0','0''0','0','0','1'};
	strcpy(control->bits,"00000001");
	control->prox = NULL;
	//printf("control %s\n", control->bits);

	lst = control;
//	puts("--");

	for (i = 1; i <= size; i++){
		//printf("Dentro do vetor: %d \n", result_binary[i]);
		//printf("%s ",to_char(result_binary[i]));
		
		build_payload(&lst,to_char(result_binary[i]));
		
	}

	printf("saida: %s ", lst->bits);	

	lst->prox = flag2;

	//flag2->bits = {'0','1','1','1''1','1','1','0'};	
	strcpy(flag2->bits,"01111110");
	flag2->prox = NULL;
	//puts("--");
	print_output(frames);
}


int main(void){

	int result_decimal[1500];
	int result_binary[1500];
	int size;
	char m[1500];

	ppp *frames;

	scanf(" %s", m);

	to_decimal(result_decimal,m,&size);	

	to_binary(result_binary,result_decimal,&size);

	build_frame(result_binary,frames,size);

	getch();

}
