#include "PaginaCombinacao.h"
#include "PaginaCombinacao.h"

#include "Cabecalho/Pagina.h"
#include "Cabecalho/Equipamento.h"
#include "Utilitario.h"

void executarPaginaCombinacao(Pagina * pagina, Equipamento equipamentos [], int qtdEquipamentos) {
	if (pagina->aberta)
	{	
		desenhaQuadrado(pagina->posicao, al_map_rgb(255, 255, 255));
		
		int posicaoX = 1.5;
		int posicaoY = pagina->posicao.tamanhoY - 206;

		for (int i = 0; i < qtdEquipamentos; i++)
		{

			Posicao posicao = {
				.posicaoX = posicaoX,
				.posicaoY = posicaoY,
				.tamanhoX = pagina->posicao.tamanhoX / 5 - 3,
				.tamanhoY = pagina->posicao.tamanhoY / 5
			};

			desenhaQuadrado(posicao, al_map_rgb(posicaoX, 5, 4));

			posicaoX += pagina->posicao.tamanhoX / 5;
			if (posicaoX > pagina->posicao.tamanhoX) {
				posicaoX = 1.5;
				posicaoY += 103;
			}
		}
		al_flip_display();
	}
}