/* nome: ThePix
 * 
 * versão: 1.0
 * 
 * Desenvolvedor: Murillo Justino
 * 
 * Sobre: Esse programa foi feito para o Hackathon do Hackoon Space de 2021.
 * 	Tem como objetico ser um aplicativo estilo pix.
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "thepix.h"

int main() {
	boolean loginCorreto;
	char user[20], chave[20], bd[50], temp[50], senha[11], dinheiro[10];
	int opcao = 0;
	float saldo;
	
	geraNome(user);
	opcao = geraVariaveis(user, temp, chave, opcao);
	strcpy(bd, temp);
	sprintf(bd, "/home/%s/.%s", user, temp);
	desencripta(bd, senha, dinheiro);
	saldo = geraSaldo(dinheiro);
	saldo = verficaTransacao(bd, chave, saldo);
	loginCorreto = login(chave, senha);

	if (loginCorreto == sim) {
		printf("\n\n");
		menu(bd, saldo);
	}
	
	return 0;
}
