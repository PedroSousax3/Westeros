#include <allegro5/allegro5.h>
#include <stdbool.h>

#include "../Cabecalho/Personagem.h"


Personagem iniciarPersonagem() {
	Personagem personagem = {
		.nome = NULL,
		.sobreNome = NULL,
		.idade = 0,
		.imagemX = 0,
		.imagemY = 0
	};

	return personagem;
}

void desenharPersonagem(Personagem personagem) {
	al_draw_bitmap_region(
		personagem.imagem,
		personagem.imagemX,
		personagem.imagemY,
		personagem.movimento.posicao.tamanhoX,
		personagem.movimento.posicao.tamanhoY,
		personagem.movimento.posicao.posicaoX,
		personagem.movimento.posicao.posicaoY,
		0
	);
}

//void coletaItens(ItensRoot itens, Personagem pesonagem)
//{
//	int n = 0;
//	while (n < 8 && pesonagem.inventario[n] != 0)
//	{
//		n++;
//	}
//	if (pesonagem.inventario[n] == 0)
//	{
//		pesonagem.inventario[n] = 2;
//	}
//}
//
//void popularInv(Personagem personagem)
//{
//	int n = 0;
//	while (n < 8) {
//		personagem.inventario[n] = n;
//		n++;
//	}
//}
