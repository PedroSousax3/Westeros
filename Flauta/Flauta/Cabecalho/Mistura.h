#ifndef Cabecalho_Mistura
#define Cabecalho_Mistura

#include "Equipamento.h"

typedef struct Mistura {
	Equipamento novoEquipamento;
	Equipamento ingredientes[5];
} Mistura;

bool misturaPossuiTodosIngredientes(Mistura* mistura, Equipamento estoqueEquipamentos[]);
void misturaSepararIngredientes(Mistura * mistura, Equipamento estoqueEquipamentos[]);
Equipamento misturaCriarEquipamento(Mistura * mistura, Equipamento estoqueEquipamentos []);

#endif // !Cabecalho_Mistura

