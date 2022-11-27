#ifndef Cabelhado_CenarioItem
#define Cabelhado_CenarioItem
#include "Posicao.h"
#include "Utils/Imagem.h"

#include <allegro5/bitmap.h>

typedef struct CenarioItem CenarioItem;
typedef struct ElementoCenario ElementoCenario;

typedef struct ElementoCenario {
	int indice;

	CenarioItem * cenarioItem;
	
	Posicao * posicaoAbsoluta;//Posicão em que o elemento será desenhado na tela.
	Posicao * posicaoRelativa;//Posição que será considerada ao trabalhar logicamente com o elemento.
	//Caso não tenha diferença entre posição absoluta e relativa usar o mesmo ponteiro para ambas.

	ElementoCenario* proximo;
	ElementoCenario* anterior;

	int * count;
};

typedef struct CenarioItem {
	int codigo;
	char * nome;
	char * descricao;
	
	bool coletavelPeloJogador;
	int codigoItemInventario;

	struct Imagem * imagem;
	struct Imagem * imagemInventario;
	struct CenarioItem * proximo;

	struct ElementoCenario * elementoInical;

	int * count;
};

#endif // !Cabelhado_CenarioItem