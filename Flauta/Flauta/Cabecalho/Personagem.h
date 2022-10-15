#ifndef Cabecalho_Personagem
#define Cabecalho_Personagem

#include <allegro5/bitmap.h>
#include "../Cabecalho/Movimento.h"

typedef struct Personagem {
	char * nome[30];
	char * sobreNome[70];
	int idade;

	int imagemX;
	int imagemY;

	ALLEGRO_BITMAP * imagem;
	Movimento movimento;
} Personagem;

Personagem iniciarPersonagem();
void desenharPersonagem(Personagem personagem);

#endif // !Cabecalho_Personagem