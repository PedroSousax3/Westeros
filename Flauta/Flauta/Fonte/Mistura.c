#include "../Cabecalho/Mistura.h"

bool misturaPossuiTodosIngredientes(Mistura* misturaBase, Mistura novaMistura);
void misturaSepararIngredientes(Mistura* mistura, Equipamento* estoqueEquipamentos[]);
Equipamento misturaCriarEquipamento(Mistura* mistura, Equipamento estoqueEquipamentos[]);