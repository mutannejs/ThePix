#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int main() {
	float valor;
	char aleatorio[7], link[30];
	
	srand(time(NULL));
	for (int i = 0; i < 6; i++)
		aleatorio[i] = "abcdefghijklmnopqrstuvwxyz"[random () % 26];
	aleatorio[6] = '\0';
	
	printf("Você deseja gerar um processo com qual valor?\n");
	scanf("%f", &valor);
	while (valor < 0) {
		printf("Digite apenas números positivos.\n");
		scanf("%f", &valor);
	}
	sprintf(link, "https://%s.com/%.2f", aleatorio, valor);
	printf("Link: %s\n", link);
	
	return 0;
}
