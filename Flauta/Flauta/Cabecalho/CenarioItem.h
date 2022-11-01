#ifndef Cabelhado_CenarioItem
#define Cabelhado_CenarioItem
#include "Posicao.h"

typedef  struct CenarioItem {
	int codigo;

	struct CenarioItem * proximo;
	
	char * nome;
	char * descricao;
	char * enderecoImagem;

	Posicao * posicao;

	bool coletavelPeloJogador;
	int codigoItemInventario;

	int * count;
} CenarioItem;

#endif // !Cabelhado_CenarioItem
