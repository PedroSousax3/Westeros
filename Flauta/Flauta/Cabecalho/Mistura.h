#ifndef Cabecalho_Mistura
#define Cabecalho_Mistura

#include "Equipamento.h"
#include "CenarioItem.h"

typedef struct Mistura {
	CenarioItem novoItem;

	CenarioItem itens[3];
} Mistura;

bool misturaPossuiTodosIngredientes(Mistura* mistura, Equipamento estoqueEquipamentos[]);
void misturaSepararIngredientes(Mistura * mistura, Equipamento estoqueEquipamentos[]);
Equipamento misturaCriarEquipamento(Mistura * mistura, Equipamento estoqueEquipamentos []);

#endif // !Cabecalho_Mistura

