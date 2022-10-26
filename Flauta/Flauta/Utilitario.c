#include <time.h>

#include "Utilitario.h"

int gerarNumeroAleatorioInt(int inicio, int fim) {
	srand(time(NULL));
	int numero = rand() % fim + 1;
	if (numero < inicio)
		numero = gerarNumeroAleatorioInt(inicio, fim);
	return numero;
}

void desenhaQuadrado(Posicao posicao, ALLEGRO_COLOR color) {
	al_draw_filled_rectangle(
		posicao.posicaoX,
		posicao.posicaoY,
		posicao.posicaoX + posicao.tamanhoX,
		posicao.posicaoY + posicao.tamanhoY,
		color
	);
}