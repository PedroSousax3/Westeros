#include "../Cabecalho/Mistura.h"

bool misturaPossuiTodosIngredientes(Ingrediente * ingrediente, Inventario * inventario) {
	if (inventario != NULL && possuiIngrediente(ingrediente, inventario)) {
		if (ingrediente->proximo != NULL)
			return misturaPossuiTodosIngredientes(ingrediente->proximo, inventario);
		else
			return true;
	}
	else
		return false;
}

bool possuiIngrediente(Ingrediente * ingrediente, Inventario* inventario) {
	if (ingrediente->elementoCenario->codigo == inventario->cenarioItem->codigo)
		return true;
	else if (inventario->proximo != NULL)
		return possuiIngrediente(ingrediente, inventario->proximo);
	else
		return false;
}

CenarioItem * realizarMistura(Mistura * mistura, Inventario * inventario)
{
	if (misturaPossuiTodosIngredientes(mistura->ingrediente, inventario)) {
		return NULL;
	}
	else {
		return NULL;
	}
}