#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "thepix.h"

boolean login(const char chave[], const char senha[]) {

	boolean ok;
	char chaveInformada[20], senhaInformada[50];

	printf("Login\n");
	printf("Digite sua chave de acesso:\n");
	scanf("%s", chaveInformada);
	if (strcmp(chave, chaveInformada) == 0) {
		printf("Digite sua senha:\n");
		scanf("%s", senhaInformada);
		fazHash(senhaInformada);
		if (strcmp(senha, senhaInformada) == 0) {
			ok = sim;
		}
		else {
			printf("Senha incorreta!\n");
			ok = nao;
		}
	}
	else {
		printf("Chave incorreta!\n");
		ok = nao;
	}
	return ok;
}

float geraSaldo(const char dinheiro[]) {
	float saldo = 0.0;
	int tam;
	
	tam = strlen(dinheiro);
	for (int i = tam - 4, j = 0; i > -4; i--, j++) {
		if (isdigit(dinheiro[j])) {
			if (i >= 0)
				saldo += (int) (dinheiro[j] - 48) * pow(10, i);
			else
				saldo += (int) (dinheiro[j] - 48) * pow(10, i+1);
		}
	}
	
	return saldo;
}

float verficaTransacao(char bd[], char chave[], float saldo) {

	char linha[20], transacao[30], key[50], valorString[20];
	int tam, posicao = 0, fase = 0;
	float valor;
	
	sprintf(transacao, "/thepix/%s.txt", chave);
	FILE *aTransacao = fopen(transacao, "r");
	
	if (aTransacao != NULL) {
		fscanf(aTransacao, "%s^[EOF]", linha);
		fclose(aTransacao);
		sprintf(transacao, "rm /thepix/%s.txt", chave);
		system(transacao);
		valor = geraSaldo(linha);
		saldo = saldo + valor;
		printf("\nFoi feito uma transação para sua conta de : %.2f\n", valor);
		printf("Seu saldo atual é: %.2f\n", saldo);
		printf("----------------------------------------------------------- *\n\n");
		
		geraKey(key);
		FILE *bancoDados = fopen(bd, "r");
		fscanf(bancoDados, "%s^[EOF]", linha);
		fclose(bancoDados);
		
		sprintf(valorString, "%.2f", saldo);
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
			
		FILE *bancoDados2 = fopen(bd, "w");
		fprintf(bancoDados2, "%s", linha);
		fclose(bancoDados2);
	}
	
	return saldo;

}
