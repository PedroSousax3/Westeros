#ifndef Cabecalho_Utils_Imagem
#define Cabecalho_Utils_Imagem

#include <allegro5/bitmap.h>
#include <allegro5/bitmap_draw.h>

#include "../Posicao.h"

typedef struct Imagem {
	char * endereco;
	ALLEGRO_BITMAP * imagem;
	int orientacao;
} Imagem;

void desenharImagem(Imagem imagem, Posicao posicao);

#endif //!Cabecalho_Utils_Imagem