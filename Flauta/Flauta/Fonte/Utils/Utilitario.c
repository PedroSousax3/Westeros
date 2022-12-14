#include "../../Cabecalho/Utils/Utilitario.h"
#include <stdlib.h>  /* rand(), srand() */
#include <time.h>    /* time() */

int gerarNumeroAleatorioInt(int inicio, int fim) {
	//time_t curtime;
	//time(&curtime);
	//srand(curtime);
	////srand(time(&curtime));
	int numeroAle = rand();
	int numero = (numeroAle % fim) + 1;
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