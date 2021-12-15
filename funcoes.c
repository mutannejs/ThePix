#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "thepix.h"

void menu(char bd[], float saldo) {
	boolean sair = nao;
	int opcao;
	
	do {
		printf("--- * Menu - ThePix * ---\n\n");
		printf("O que você deseja fazer?\n"
				"[1] Ver saldo.\n"
				"[2] Pagar um processo.\n"
				"[3] Fazer transferência.\n"
				"[0] Sair.\n\n");
		scanf("%d", &opcao);
		switch (opcao) {
			case 0:	sair = sim;
					break;
			case 1:	printf("Seu saldo é: %.2f\n", saldo);
					printf("----------------------------------------------------------- *\n\n");
					break;
			case 2: saldo = pagarProcesso(bd, saldo);
					break;
			case 3: saldo = fazerTransferencia(bd, saldo);
					break;
			default:do {
						printf("Opcao desconhecida!\nInforme um número válido:\n");
						scanf("%d", &opcao);
					} while (opcao < 0 || opcao > 3) ;
					switch (opcao) {
						case 1:	printf("\nSeu saldo é: %.2f\n\n", saldo);
								printf("----------------------------------------------------------- *\n\n");
								break;
						case 2: printf("\n");
								saldo = pagarProcesso(bd, saldo);
								break;
						case 3: printf("\n");
								saldo = fazerTransferencia(bd, saldo);
								break;
						default:sair = sim;
								break;
					}
		}
	} while (sair == nao);
	
}

float pagarProcesso(char bd[], float saldo) {
	char pagar, link[100], valorString[20], key[50], linha[100];
	int tam, posicao = 0, fase = 0;
	float valor;
	
	printf("Cole o link do processo:\n");
	scanf("%s^[\n]", link);
	
	//https://blabla.com/valor
	tam = strlen(link);
	for (int i = 19; i < tam; i++) {
		valorString[posicao] = link[i];
		posicao++;
	}
	valorString[posicao] = '\0';
	valor = geraSaldo(valorString);
	
	printf("O valor do processo é: %.2f\n", valor);
	if ((saldo - valor) >= 0) {
		printf("Você deseja pagar o processo? [s/n]\n");
		scanf(" %c", &pagar);
		if (pagar == 's' || pagar == 'S') {
			
			saldo = saldo - valor;
			sprintf(valorString, "%.2f", saldo);
			
			geraKey(key);
			FILE *banc = fopen(bd, "r");
			fscanf(banc, "%s^[EOF]", linha);
			fclose(banc);
			
			tam = strlen(linha);
			for (int i = 0; i < tam; i++) {
				if (linha[i] != '#') {
					if (linha[i] == '$') {
						fase++;
						posicao = 0;
					}
					else if (fase == 1) {
						linha[i] = valorString[posicao] + key[i];
						posicao++;
					}
				}
			}
			
			FILE *banc2 = fopen(bd, "w");
			fprintf(banc2, "%s", linha);
			fclose(banc2);
			printf("----------------------------------------------------------- *\n\n");
		}
		else {
			printf("\nFechando processo.\n");
			printf("----------------------------------------------------------- *\n\n");
		}
	}
	else {
		printf("Você não possui dinheiro suficiente para pagar esse processo.\n");
		printf("----------------------------------------------------------- *\n\n");
	}
	
	return saldo;
}

float fazerTransferencia(char bd[], float saldo) {

	char usuario[20] = ".", banco[50] = ".", chave[20], valorString[20], arquivo[30], linha[30], key[50], comando[50];
	int encontrou, sair = 0, tam, fase = 0, posicao = 0;
	float valor;
	
	printf("Digite a chave da conta para qual você deseja fazer uma transação:\n");
	scanf("%s^[\n]", chave);
	encontrou = geraVariaveis(usuario, banco, chave, 1);
	if (encontrou == sim) {
		while (sair == 0 || valor < 0) {
			printf("Quanto você deseja transferir para essa conta?\n");
			scanf("%f", &valor);
			if (saldo < valor) {
				printf("Seu saldo não é suficiente para realizar esta transferência.\n"
						"[0] Mudar valor da transferência.\n"
						"[1] Sair.\n");
				scanf("%d", &sair);
				while (sair < 0 || sair > 1) {
					printf("Opção invalida.\n");
					scanf("%d", &sair);
				}
			}
			else if (valor < 0) {
				printf("Digite apenas números positivos.\n");
			}
			else {
				sair = 2;
			}
		}
		if (sair == 2) {
			sprintf(arquivo, "/thepix/%s.txt", chave);
			FILE *arquivoT = fopen(arquivo, "r");
			if (arquivoT != NULL) {
				fscanf(arquivoT, "%s^[EOF]", linha);
				valor = valor + geraSaldo(linha);
				fclose(arquivoT);
			}			
			FILE *arquivoTransferencia = fopen(arquivo, "w");
			sprintf(valorString, "%.2f", valor);
			fprintf(arquivoTransferencia, "%s", valorString);
			fclose(arquivoTransferencia);
			sprintf(comando, "chmod 777 %s", arquivo);
			system(comando);
			
			saldo = saldo - valor;
			sprintf(valorString, "%.2f", saldo);
			geraKey(key);
			FILE *data = fopen(bd, "r");
			fscanf(data, "%s^[EOF]", linha);
			fclose(data);
			tam = strlen(linha);
			for (int i = 0; i < tam; i++) {
				if (linha[i] != '#') {
					if (linha[i] == '$') {
						fase++;
						posicao = 0;
					}
					else if (fase == 1) {
						linha[i] = valorString[posicao] + key[i];
						posicao++;
					}
				}
			}
			FILE *data2 = fopen(bd, "w");
			fprintf(data2, "%s", linha);
			fclose(data2);
			
			printf("Transferência realizada.\n");
			printf("----------------------------------------------------------- *\n\n");
		}
		else {
			printf("Sainda sem realizar transferência.\n");
			printf("----------------------------------------------------------- *\n\n");
		}
	}
	else {
		printf("Não foi encontrado nenhum usuario com esta chave.\n");
		printf("----------------------------------------------------------- *\n\n");
	}
	
	return saldo;
}
