#ifndef THEPIX_H
#define THEPIX_H

typedef enum boolean {sim, nao} boolean;

//variaveis.c
void geraNome(char user[]);
boolean geraVariaveis(char user[], char bd[], char chave[], const int opcao);

//desencripta.c
void desencripta(const char bd[], char senha[], char dinheiro[]);
void fazHash(char senha[]);
void geraKey(char key[]);

//conta.c
boolean login(const char chave[], const char senha[]);
float geraSaldo(const char dinheiro[]);
float verficaTransacao(char bd[], char chave[], float saldo);

//funcoes.c
void menu(char bd[], float saldo);
float pagarProcesso(char bd[], float saldo);
float fazerTransferencia(char bd[], float saldo);

#endif
