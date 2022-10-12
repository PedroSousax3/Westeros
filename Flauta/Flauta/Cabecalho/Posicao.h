#ifndef Cabecalho_Posicao
#define Cabecalho_Posicao

#include <stdbool.h>

typedef struct Posicao {
	int posicaoX;
	int posicaoY;

	int tamanhoX;
	int tamanhoY;

	int velocidadeX;
	int velocidadeY;
} Posicao;

Posicao * iniciarPosicao();
void setPosicao(Posicao * posicao, int posicaoX, int posicaoY, int tamanhoX, int tamanhoY, int velocidadeX, int velocidadeY);
bool colidiu(Posicao * posicao, Posicao intens[], int tamanhoVetor);

#endif // !Cabecalho_Posicao