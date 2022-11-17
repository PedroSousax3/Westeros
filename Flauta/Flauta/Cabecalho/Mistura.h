#ifndef Cabecalho_Mistura
#define Cabecalho_Mistura

#include "Equipamento.h"
#include "CenarioItem.h"
#include "Cenario.h"
#include "Inventario.h"

typedef struct Mistura {
	CenarioItem * novoItem;

	CenarioItem itens[3];
} Mistura;

bool misturaPossuiTodosIngredientes(Mistura mistura, Inventario* inventario);
Mistura* iniciarMisturas(CenarioItem* cenarioItemIncial);
#endif // !Cabecalho_Mistura

