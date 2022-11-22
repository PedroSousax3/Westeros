#include "PaginaCombinacao.h"

void desenharItemInventarioTelaConbinacao(Inventario* inventario, Posicao posicaoDoItemAnterior, Pagina * pagina) {
	if (inventario != NULL) {
		Posicao posicao = {
			.posicaoY = posicaoDoItemAnterior.posicaoY,
			.tamanhoX = 100,
			.tamanhoY = 100
		};
		posicao.posicaoX = posicaoDoItemAnterior.posicaoX + posicao.tamanhoX;

		if (posicao.posicaoX + posicao.tamanhoX > pagina->posicao.tamanhoX) {
			posicao.posicaoX = 0;
			posicao.posicaoY += posicao.tamanhoY;
		}

		desenharImagem(*inventario->cenarioItem->imagem, posicao);
	
		if (inventario->proximo != NULL)
			desenharItemInventarioTelaConbinacao(inventario->proximo, posicao, pagina);
	}
}
void executarPaginaCombinacao(Pagina * pagina, Inventario * inventario) {
	if (pagina->aberta)
	{	
		desenhaQuadrado(pagina->posicao, al_map_rgb(255, 255, 255));
		int posicaoY = pagina->posicao.tamanhoY - 206;
		Posicao posicaoBase = {
			.posicaoY = 0,
			.posicaoX = -100,
			.posicaoY = posicaoY
		};
		desenharItemInventarioTelaConbinacao(inventario, posicaoBase, pagina);
		al_flip_display();
	}
}