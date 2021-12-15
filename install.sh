#!/bin/bash


# ------------ Cria o arquivo onde há o nomes, usuarios e chaves
if [ ! -d "/thepix" ]; then
	sudo mkdir /thepix/;
	sudo touch /thepix/thepix.txt;
	sudo chmod 777 /thepix -R;
fi


# ------------ Compila e roda o instalador em c
gcc -o install install.c;
./install;


# ------------ Exclui os arquivos que podem conter chaves
#rm desencripta.c
