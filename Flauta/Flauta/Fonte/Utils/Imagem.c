#include "../../Cabecalho/Utils/Imagem.h"

void desenharImagem(Imagem imagem) {
	al_draw_bitmap_region(
		imagem.imagem,
		0,
		0,
		imagem.posicao.tamanhoX,
		imagem.posicao.tamanhoY,
		imagem.posicao.posicaoX,
		imagem.posicao.posicaoY,
		imagem.orientacao
	);
}