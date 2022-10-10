#pragma once
#include <allegro5/bitmap.h>

#include "../Cabecalho/Movimento.h"

class Personagem {
public:
	char nome[30];
	char sobreNome[70];
	int idade;

	int imagemX;
	int imagemY;

	Movimento movimento;
	ALLEGRO_BITMAP * imagem;

	Personagem();
	void desenharPersonagem();
}; 