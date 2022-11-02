#ifndef Cabelhado_CenarioItem
#define Cabelhado_CenarioItem
#include "Posicao.h"
#include <allegro5/bitmap.h>
typedef  struct CenarioItem {
	int codigo;

	struct CenarioItem * proximo;
	
	char * nome;
	char * descricao;
	char * enderecoImagem;

	ALLEGRO_BITMAP * imagem;
	int imagemX;
	int imagemY;
	int imagemTamanhoX;
	int imagemTamanhoY;

	Posicao * posicao;

	bool coletavelPeloJogador;
	int codigoItemInventario;

	int * count;
} CenarioItem;

#endif // !Cabelhado_CenarioItem
