#include "PaginaCombinacao.h"

void desenharItemInventarioTelaConbinacao(Inventario* inventario, Posicao posicaoDoItemAnterior, Pagina * pagina) {
	if (inventario != NULL) {
		Posicao posicao = {
			.posicaoY = posicaoDoItemAnterior.posicaoY,
			.tamanhoX = 64,
			.tamanhoY = 56
		};
		posicao.posicaoX = posicaoDoItemAnterior.posicaoX + posicao.tamanhoX;

		if (posicao.posicaoX + posicao.tamanhoX > pagina->posicao.tamanhoX) {
			posicao.posicaoX = 0;
			posicao.posicaoY += posicao.tamanhoY;
		}

		Imagem* imagem = NULL;
		if (inventario->cenarioItem->imagemInventario != NULL)
			imagem = inventario->cenarioItem->imagemInventario;
		else
			imagem = inventario->cenarioItem->imagem;

		desenharImagem(*imagem, posicao);
	
		if (inventario->proximo != NULL)
			desenharItemInventarioTelaConbinacao(inventario->proximo, posicao, pagina);
	}
}
void executarPaginaCombinacao(Pagina * pagina, Inventario * inventario) {
	if (pagina->aberta)
	{	
		desenharImagem(pagina->background, pagina->posicao);
		int posicaoY = pagina->posicao.tamanhoY - 80;
		Posicao posicaoBase = {
			.posicaoY = 24,
			.posicaoX = - 49,
			.posicaoY = posicaoY
		};
		desenharItemInventarioTelaConbinacao(inventario, posicaoBase, pagina);
		al_flip_display();
	}
}