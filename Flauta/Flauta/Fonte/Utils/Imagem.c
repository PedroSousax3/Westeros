#include "../../Cabecalho/Utils/Imagem.h"

void desenharImagem(Imagem imagem, Posicao posicao) {
	al_draw_bitmap_region(
		imagem.imagem,
		0,
		0,
		posicao.tamanhoX,
		posicao.tamanhoY,
		posicao.posicaoX,
		posicao.posicaoY,
		imagem.orientacao == 2 ? 0x00002 : 0x00001
	);
}