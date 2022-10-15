#include "../Cabecalho/Posicao.h"

Posicao iniciarPosicao() {
	Posicao posicao = {
		.posicaoX = 0,
		.posicaoY = 0,
		.tamanhoX = 0,
		.tamanhoY = 0,
		.velocidadeX = 0,
		.velocidadeY = 0
	};

	return posicao;
}

void setPosicao(Posicao * posicao, int posicaoX, int posicaoY, int tamanhoX, int tamanhoY, int velocidadeX, int velocidadeY) {
	posicao->posicaoX = posicaoX;
	posicao->posicaoY = posicaoY;
	posicao->tamanhoX = tamanhoX;
	posicao->tamanhoY = tamanhoY;
	posicao->velocidadeX = velocidadeX;
	posicao->velocidadeY = velocidadeY;
}

bool colidiu(Posicao posicao, Posicao intens[], int tamanhoVetor) {
	int x = posicao.posicaoX;
	int y = posicao.posicaoY;
	int xM = posicao.posicaoX + posicao.tamanhoX;
	int yM = posicao.posicaoY + posicao.tamanhoY;

	for (int i = 0; i < tamanhoVetor; i++)
		if (
			xM >= intens[i].posicaoX && x <= (intens[i].posicaoX + intens[i].tamanhoX)
			&& yM >= intens[i].posicaoY && y <= (intens[i].posicaoY + intens[i].tamanhoY)
		)
			return true;

	return false;
}