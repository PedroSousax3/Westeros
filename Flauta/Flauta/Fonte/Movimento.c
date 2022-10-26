#include "../Cabecalho/Movimento.h"

Movimento iniciarMovimento() {
	Movimento novoMovimento = {
		.direcaoX = DIRECAOXNENHUM,
		.direcaoY = DIRECAOYNENHUM,
		.direcao = 0
	};

	return novoMovimento;
}

void setMovimento(Movimento * novoMovimento, DirecaoY direcaoY, DirecaoX direcaoX, Posicao posicao) {
	novoMovimento->direcao = 0;
	novoMovimento->direcaoY = direcaoY;
	novoMovimento->direcaoX = direcaoX;
	novoMovimento->posicao = posicao;
}

bool emMovimento(Movimento novoMovimento) {
	return novoMovimento.direcaoX != DIRECAOXNENHUM || novoMovimento.direcaoY != DIRECAOYNENHUM;
}