#ifndef Cabecalho_Inventario
#define Cabecalho_Inventario

#include "CenarioItem.h"

typedef struct Inventario Inventario;

struct Inventario {
	CenarioItem * cenarioItem;

	Posicao * posicaoRelativa;
	Posicao * posicaoAbsoluta;

	int indice;
	int * count;
	Inventario * proximo;
};

Inventario* inserirItemInventario(Inventario* inventarioAnterior, CenarioItem* cenarioItem);
void alterarPosicaoChildren(Inventario* inicio, int diferenca);
void removerItemInventario(Inventario* inventario);
Inventario* buscarItemInventario(Inventario* inventario, int codCenarioItem);
void desenharItensInventarios(Inventario inventarioInicial);
CenarioItem* ultimoItemInventario(Inventario* inventarioInicial);
void destruirInvetario(Inventario* inventarioInicial);
#endif // !Cabecalho_Inventario
