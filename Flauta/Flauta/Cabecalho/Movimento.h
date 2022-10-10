#pragma once

#include "Posicao.h"

enum class DirecaoX {
	NENHUM,
	ESQUERDA, 
	DIREITA
};

enum class DirecaoY {
	NENHUM,
	CIMA = 1,
	BAIXO
};

class Movimento {

	public:
		DirecaoY direcaoY;
		DirecaoX direcaoX;

		int direcao;

		Posicao posicao;

		Movimento();
		Movimento(DirecaoY direcaoY, DirecaoX direcaoX, Posicao posicao);
		bool emMovimento();
};