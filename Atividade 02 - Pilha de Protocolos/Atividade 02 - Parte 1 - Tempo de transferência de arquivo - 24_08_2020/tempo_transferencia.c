#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void){
	double t; /* TAMANHO DO ARQUIVO  em MB*/
	double l; /* LARGURA DE BANDA */
	int r; /* RTT  em ms */
	int p; /* TAMANHO DO PACOTE em KB*/ 
	int k; /* handshaking */
	int q; /* pacotes */
	char s; /* OPÇÃO */
	double latencia = 0;
	double latencia_aux = 0;
	double aux2;
	int total_pacotes = 0;
	int count_pacotes = 1;

	
	scanf(" %lf %d %d %d ", &t, &r, &p, &k);

	scanf(" %c", &s);

	switch(s){
		case 'A': 
		scanf(" %lf", &l);
		/* Situação A: largura de banda l, valor real em Mbps, e os pacotes podem ser enviados continuamente; 
		 tempo total = handshake + tempo transmissão + tempo de propagação do último bit
		 TEMPO DE TRANSMISSÃO Tamanho/Largura de Banda;	*/	

		latencia = (( k * r) + (r/2)) * 0.001 + (t * 8 /l);
		
		break;
		case 'B': 
		scanf(" %lf", &l);
		/* Situação B: largura de banda l, valor real em Mbps, e deve-se esperar um RTT após o envio de cada pacote até que se envie o próximo; 
			Na Situação B, não é necessário esperar um RTT após o envio do último pacote (a transmissão estará encerrada);
		*/
		
		//latencia = (((p * 1000 - 1) * r)* 0.001) + ( (( k * r) + (r/2)) * 0.001 + (t * 8 /l) );
		aux2 = (( k * r) + (r/2)) * 0.001 + (t * 8 /l);
		printf("valor: %f pacote: %f \n", aux2, (((t * 1000000) / (p * 1000) - 1) * r * 0.001));
		latencia = (aux2 + (((t * 1000000) / (p * 1000) - 1) * r * 0.001));

		break;
		case 'C': 
		scanf(" %d", &q);
		/* Situação C: largura de banda "infinita" (tempo de transmissão irrelevante). Entretanto, q pacotes (valor inteiro) podem ser enviados por RTT; */

		latencia = (k * r + 0.5 * r + ((((t * 1000000) / (p * 1000))/q) - 1) * r) * 0.001;
		
		break;
		case 'D': 
		/* ituação D: largura de banda "infinita" (tempo de transmissão irrelevante). No primeiro RTT, entretanto, um pacote pode ser enviado. No segundo, dois pacotes podem ser enviados. No terceiro, quatro pacotes podem ser enviados. E assim sucessivamente. */

		total_pacotes = (t * 1000000) / (p * 1000);
		// 1000000 / 1000
		// 1000
		count_pacotes = 1;

		while( total_pacotes > 0){
			latencia_aux += r;
			total_pacotes -= count_pacotes;
			count_pacotes *= 2;
			printf("latencia Aux: %f Total pacote: %d\n", latencia_aux , total_pacotes);
		}

		//latencia = latencia_aux * 0.001;
		latencia = (k * r + 0.5 * r + (latencia_aux - r)) * 0.001;

		break;
	}
	printf("Tempo de transmissão: %.7f\n", latencia);
	system("pause");
}
