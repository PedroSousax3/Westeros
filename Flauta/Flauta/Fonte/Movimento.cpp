#include "../Cabecalho/Movimento.h"

Movimento::Movimento() {
	this->direcaoX = DirecaoX::NENHUM;
	this->direcaoY = DirecaoY::NENHUM;
	this->posicao = Posicao();
}

Movimento::Movimento(DirecaoY direcaoY, DirecaoX direcaoX, Posicao posicao) {
	this->direcao = 0;
	this->direcaoY = direcaoY;
	this->direcaoX = direcaoX;
	this->posicao = posicao;
}

bool Movimento::emMovimento() {
	return this->direcaoX != DirecaoX::NENHUM || this->direcaoY != DirecaoY::NENHUM;
}