#ifndef Cabecalho_Movimento
#define Cabecalho_Movimento

#include <stdbool.h>
#include "Posicao.h"

typedef enum DirecaoX {
	DIRECAOXNENHUM,
	DIRECAOXESQUERDA,
	DIRECAOXDIREITA
} DirecaoX;

typedef enum DirecaoY {
	DIRECAOYNENHUM,
	DIRECAOYCIMA = 1,
	DIRECAOYBAIXO
} DirecaoY;

typedef struct Movimento {
	int direcaoY;
	int direcaoX;

	int direcao;

	Posicao * posicao;
} Movimento;

Movimento * iniciarMovimento();
void setMovimento(Movimento * novoMovimento, DirecaoY direcaoY, DirecaoX direcaoX, Posicao * posicao);
bool emMovimento(Movimento * novoMovimento);

#endif // !Cabecalho_Movimento