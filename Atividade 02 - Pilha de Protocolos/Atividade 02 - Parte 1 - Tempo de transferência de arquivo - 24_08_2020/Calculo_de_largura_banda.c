#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void){
	
    int d; /* distância d (valor inteiro, em quilômetros)*/
	int v; /* uma velocidade de propagação do sinal v (inteiro, em metros por segundo) */
	int t; /*  tamanho de pacote t (inteiro, em bytes) */
	//double l; /* valor de largura de banda l (real, em Mbps)*/ 
    double retardo_propagacao;
	
	/*
    Escreva um programa em C que lê uma distância d (valor inteiro, em quilômetros), 
    velocidade de propagação do sinal v (inteiro, em metros por segundo)
    tamanho de pacote t (inteiro, em bytes) 
    calcula o valor de largura de banda l (real, em Mbps) 
    tal que o retardo de propagação calculado em função de d e de v, é igual ao tempo de transmissão para pacotes de tamanho t
    */
	//scanf(" %d %ld %d ", &d, &v, &t);
    d = 50;
    v = 200000;
    t = 100;
    retardo_propagacao = d * 1000 / v;

    printf("distancia %d\n", d * 1000);
    printf("v:  %d\n", v);
    printf("rrrr:  %f\n", (d * 1000 / v) * 100);
    //d *= 1000;
    //retardo_propagacao = d / v;
	printf("O tempo de transmissão será equivalente ao retardo de propagação na largura de banda %f\n", retardo_propagacao);
	system("pause");
}