#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int to_decimal(char campo[4]){
	int r;
	if (campo[1] == 't'){
		r = campo[2] - '0';
		r+= 8;
		return r;
	}else{
		r = campo[2] - '0';
		r+= 16;
		return r;
	}
}

void to_binary(int n, int valor){
	char bits[30];
	int aux = valor, i;

	bits[n] = '\0';

	for (i = n; i > 0; i--){

		if ((aux % 2) == 1){
			bits[i-1] = 49;
		}else{
			bits[i-1] = 48;
		}
		
		aux = aux/2;
	}

	printf("%s", bits);
}

int main(void){
	
	int n;
	int endereco;
	char op[4], rd[4], rs[4], rt[4], enderecostr[20];
	char *teste;


	scanf("%d", &n);
	

	while(n > 0){

		scanf("%s", op);

		if (strcmp(op,"lw") == 0){
			
			scanf(" %s %s", rs, enderecostr);

			to_binary(6,35);

			teste = strtok(enderecostr,"(");
			endereco = atoi(teste);
			

			teste = strtok(NULL,")");
			

			to_binary(5,to_decimal(teste));
			
			to_binary(5,to_decimal(rs));
			to_binary(16,endereco);

		}else{
			if(strcmp(op,"add") == 0){

				scanf("%s %s %s", rd, rs, rt);

				to_binary(6,0);

				to_binary(5,to_decimal(rs));
				to_binary(5,to_decimal(rd));
				to_binary(5,to_decimal(rt));

				to_binary(5,0);
				to_binary(6,32);
				printf("\n");

			}else{
				if(strcmp(op,"sw") == 0){
					
					scanf(" %s %s", rs, enderecostr);

					to_binary(6,43);


					teste = strtok(enderecostr,"(");
					endereco = atoi(teste);


					teste = strtok(NULL,")");


					to_binary(5,to_decimal(teste));

					to_binary(5,to_decimal(rs));
					to_binary(16,endereco);


				}else{
					if (strcmp(op,"addi") == 0){
						scanf("%s %s %s", rd, rs, rt);

						to_binary(6,8);

						to_binary(5,to_decimal(rs));
						to_binary(5,to_decimal(rd));
						to_binary(5,to_decimal(rt));

						to_binary(5,0);
						to_binary(6,32);
						printf("\n");
					}else{
						if (strcmp(op,"sub") == 0){
							scanf("%s %s %s", rd, rs, rt);

							to_binary(6,34);

							to_binary(5,to_decimal(rs));
							to_binary(5,to_decimal(rd));
							to_binary(5,to_decimal(rt));

							to_binary(5,0);
							to_binary(6,32);
							printf("\n");
						}else{
							if (strcmp(op,"slt") == 0){
								scanf("%s %s %s", rd, rs, rt);

								to_binary(6,8);

								to_binary(5,to_decimal(rs));
								to_binary(5,to_decimal(rd));
								to_binary(5,to_decimal(rt));

								to_binary(5,0);
								to_binary(6,32);
								printf("\n");
							}else{
								if (strcmp(op,"slti") == 0){
									scanf("%s %s %s", rd, rs, rt);

									to_binary(6,10);

									to_binary(5,to_decimal(rs));
									to_binary(5,to_decimal(rd));
									to_binary(5,to_decimal(rt));

									
									to_binary(5,0);
									to_binary(6,32);
									printf("\n");
								}else{
									if (strcmp(op,"jal") == 0){
										to_binary(6,3);
										to_binary(26,16777212);
										
									}else{
										if (strcmp(op,"j") == 0){
											to_binary(6,2);
											to_binary(26,50331645);
										}else{
											if (strcmp(op,"beq") == 0){
												to_binary(6,4);
												to_binary(26,49149);
											}else{
												if (strcmp(op,"bne") == 0){
													to_binary(6,5);
													to_binary(26,16380);
												}
											}
										}
									}
								}
							}
						}
					}

				}
			}
		}



		n--;
	}


}
