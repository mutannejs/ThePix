#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "thepix.h"

void geraNome(char user[]) {
	//--------- Guarda na variável user o usuario logado atualmente -------
	
	system("touch .temp; whoami > .temp");
	FILE *temp = fopen(".temp", "r");
	fscanf(temp, "%s^[EOF]", user);
	fclose(temp);
	system("rm .temp");
	// --------------------------------------------------------------------
}

boolean geraVariaveis(char user[], char bd[], char chave[], const int opcao) {
	boolean sair = nao;
	int tam, tam2, fase = 0, posicao = 0;
	char c, linha[100], nome[20], comparar[20];
	
	FILE *thepix = fopen("/thepix/thepix.txt", "r");
	if (opcao == 0) {
		tam = strlen(user);
		while (sair == nao) {
			fscanf(thepix, "%s^[\n]", linha);
			strncpy(comparar, linha, tam);
			if (strcmp(comparar, user) == 0)
				sair = sim;
		}
	}
	//aprendiz:aprendiz:123456789
	//mestre:aqui:123456
	else {
		for (int i = 0, j = 0; fscanf(thepix, "%c", &c) != EOF && sair == nao; i++) {
			if (c == '\n') {
				comparar[j] = '\0';
				//printf("%s %d\n", comparar, opcao);
				if (strcmp(comparar, chave) == 0)
					sair = sim;
				fase = 0;
				j = 0;
			}
			else if (c == ':') {
				fase++;
			}
			else if (fase == 2) {
				comparar[j] = c;
				j++;
			}
		}
	}
	fclose(thepix);
	
	fase = posicao = 0;
	if (sair == nao) {
		return nao;
	}
	else {
		tam = strlen(linha);
		for (int i = 0; i < tam; i++) {
			if (linha[i] == ':') {
				if (fase == 0)
					user[posicao] = '\0';
				else
					bd[posicao] = '\0';
				fase++;
				posicao = 0;
			}
			else if (fase == 0) {
				user[posicao] = linha[i];
				posicao++;
			}
			else if (fase == 1) {
				bd[posicao] = linha[i];
				posicao++;
			}
			else if (fase == 2 && opcao == 0) {
				chave[posicao] = linha[i];
				posicao++;
			}
		}
		if (opcao == 0)
			chave[posicao] = '\0';
		return sim;
	}
}
