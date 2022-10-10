#pragma once

class Posicao {
public:
	int posicaoX;
	int posicaoY;

	int tamanhoX;
	int tamanhoY;

	int velocidadeX;
	int velocidadeY;

	Posicao();
	Posicao(int posicaoX, int posicaoY, int tamanhoX, int tamanhoY, int velocidadeX, int velocidadeY);
	bool colidiu(Posicao intens[], int tamanho);
};