#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "thepix.h"

void desencripta(const char bd[], char senha[], char dinheiro[]) {
	char linha[100], conteudo[100], key[50];
	int tam, fase = 0, posicao = 0;
	
	geraKey(key);
	
	FILE *banco = fopen(bd, "r");
	fscanf(banco, "%s^[EOF]", linha);
	//conteudo[0] = linha[0] - key[0];
	//for (int i = 1; linha[i-1] != '\0'; i++) {
	tam = strlen(linha);
	for (int i = 0; i < tam; i++) {
		if (linha[i] != '$' && linha[i] != '#') {
			conteudo[i] = linha[i] - key[i];
		}
		else {
			conteudo[i] = linha[i];
		}
	}
	fclose(banco);
	conteudo[tam] = '\0';
	
	// ----- Separa senha de dinheiro -----
	for (int i = 0; conteudo[i] != '#'; i++) {
		if (conteudo[i] == '$') {
			senha[i] = '\0';
			fase++;
			posicao = 0;
		}
		else if (fase == 0) {
			senha[posicao] = conteudo[i];
			posicao++;
		}
		else if (fase == 1) {
			dinheiro[posicao] = conteudo[i];
			posicao++;
		}
	}
	dinheiro[posicao] = '\0';
}

void fazHash(char senha[]) {
	boolean sair = nao;
	int baldes[10], turno = 0;
	char c;

	for (int i = 0; i < 10; i++)
		baldes[i] = i;

	while (sair == nao) {
		for (int i = 0; i < 10; i++) {
			c = senha[(turno*10) + i];
			if (c != '\0') {
				baldes[i] = baldes[i] + c;
				baldes[i] = baldes[i] % 26;
			}
			else {
				c = senha[(turno*10) + i - 1];
				for (; i < 10; i++) {
					baldes[i] = baldes[i] + c;
					baldes[i] = baldes[i] % 26;
				}
				sair = sim;
			}
		}
		turno++;
	}

	for (int i = 0; i < 10; i++) {
		senha[i] = baldes[i] + 65;
	}
	senha[10] = '\0';
}
