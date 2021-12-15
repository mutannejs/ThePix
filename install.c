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
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

typedef enum boolean {sim, nao} boolean;

void fazHash(char senha[]);

int main(int argc, char argv[]) {
	
	// ----- Declara variaveis -----
	char c, nome[20], chave[20], senha[50], user[20], path[20], bd[500], nuvem[100], key[50], comando[70], texto[2000];
	int opcao, tam, posicao, randomletter;
	
	// ----- Inicia a semente de números pseudo-aleatórios -----
	srand(time(NULL));
	
	// ----- Pega os dados necessários -----
	printf("Como você deseja chamar esse programa?\nnome: ");
	scanf("%s^[\n]", nome);
	printf("Você deseja que sua chave de acesso seja:\n"
		"[1] Seu número de celular.\n"
		"[2] Seu CPF.\n"
		"[3] Chave aleatória.\nopcao: ");
	scanf("%d", &opcao);
	if (opcao == 1) {
		printf("Digite seu número de celular (apenas digitos):\n");
		scanf("%s^[\n]", chave);
	}
	else if (opcao == 2) {
		printf("Digite seu CPF (apenas digitos):\n");
		scanf("%s^[\n]", chave);
	}
	else {
		//criar chave aleatória
		for (int i = 0; i < 8; i++) {
			chave[i] = "0123456789"[random () % 10];
		}
		chave[8] = '\0';
		printf("Sua chave de acesso é: %s\n", chave);
	}
	printf("Qual será sua senha? [não utilizar $ e #]\n");
	scanf("%s^[\n]", senha);
	fazHash(senha);
	
	// ----- Guarda na variável user o usuario logado atualmente -----
	system("touch .temp; whoami > .temp");
	FILE *temp = fopen(".temp", "r");
	fscanf(temp, "%s^[EOF]", user);
	fclose(temp);
	system("rm .temp");
	
	// ----- Guarda na variável path o caminho do banco de dados -----
	sprintf(path, "/home/%s/.%s", user, nome);
	
	// ----- Escreve na variavel bd o que será guardado no banco de dados -----
	sprintf(bd, "%s$1000.00##", senha);
	tam = strlen(bd);

	// ----- encriptar o bd -----
	for (int i = 0; i < 49; i++) {
		randomletter = "0123456789"[random () % 10];
		key[i] = randomletter;
	}
	key[49] = '\0';
	for (int i = 0; i < tam; i++) {
		if (bd[i] != '$' && bd[i] != '#') {
			bd[i] = bd[i] + key[i];
		}
	}
	
	// ----- Escreve no final de desencripta.c a chave para desencriptar o bd -----
	FILE *des = fopen("des.c", "r");
	FILE *descriptar = fopen("desencripta", "w");
	for (int i = 0; fscanf(des, "%c", &c) != EOF; i++) {
		fprintf(descriptar, "%c", c);
	}
	fclose(des);
	fprintf(descriptar, "void geraKey(char key[]) {\n\tchar chave[] = \"%s\";\n\tstrcpy(key, chave);\n}", key);
	fclose(descriptar);
	system("mv desencripta desencripta.c");
	
	// ----- Escreve no banco de dados o bd encriptado -----
	FILE *bancoDeDados = fopen(path, "w");
	fprintf(bancoDeDados, "%s", bd);
	fclose(bancoDeDados);
	// ----- Dá permissão apenas do usuario mexer no banco de dados -----
	sprintf(comando, "chmod 700 %s", path);
	system(comando);
	
	// ----- Escreve no arquivo /thepix/thepix.txt o usuario:nome:chave -----
	FILE *arquivo3 = fopen("/thepix/thepix.txt", "r");
	FILE *thepix = fopen("/thepix/thepix2.txt", "w");
	for (int i = 0; fscanf(arquivo3, "%c", &c) != EOF; i++) {
		fprintf(thepix, "%c", c);
	}
	fprintf(thepix, "%s:%s:%s\n", user, nome, chave);
	system("mv /thepix/thepix2.txt /thepix/thepix.txt; chmod 777 /thepix/thepix.txt");
	fclose(arquivo3);
	fclose(thepix);
	
	// ----- Printa tudo para ver se está correto ----- RETIRAR NO FIM
	//printf("\n --- * %s - %s - %s * ---\n"
	//		" --- * %s * ---", nome, chave, senha, bd);


	// ----- Compila o programa completo e finaliza a instalação ----- ACRESCENTAR O MOVER PARA /BIN
	sprintf(comando, "gcc -o geralink geralink.c; gcc -o %s main.c conta.c variaveis.c desencripta.c funcoes.c -lm; sudo mv %s /bin; echo \"sudo rm /bin/%s /home/%s/.%s;\" >> desinstala.sh", nome, nome, nome, user, nome);
	system(comando);
	system("rm desencripta.c");
	
	printf("\nFim da instalação!\n");

	return 0;
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
