#include "../Cabecalho/Posicao.h"

Posicao::Posicao() {}

Posicao::Posicao(int posicaoX, int posicaoY, int tamanhoX, int tamanhoY, int velocidadeX, int velocidadeY) {
	this->posicaoX = posicaoX;
	this->posicaoY = posicaoY;
	this->tamanhoX = tamanhoX;
	this->tamanhoY = tamanhoY;
	this->velocidadeX = velocidadeX;
	this->velocidadeY = velocidadeY;
}

bool Posicao::colidiu(Posicao intens[], int tamanhoVetor) {
	int x = this->posicaoX;
	int y = this->posicaoY;
	int xM = this->posicaoX + this->tamanhoX;
	int yM = this->posicaoY + this->tamanhoY;

	for (int i = 0; i < tamanhoVetor; i++)
		if (
			xM >= intens[i].posicaoX && x <= (intens[i].posicaoX + intens[i].tamanhoX)
			&& yM >= intens[i].posicaoY && y <= (intens[i].posicaoY + intens[i].tamanhoY)
		)
			return true;

	return false;
}