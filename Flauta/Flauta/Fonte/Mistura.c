#include "../Cabecalho/Mistura.h"

bool misturaPossuiTodosIngredientes(Mistura mistura, Inventario * inventario) {
	for (int i = 0; i < 3; i++)
		if (buscarItemInventario(inventario, mistura.itens[i].codigo) == NULL)
			return false;

	return true;
}

Mistura * iniciarMisturas(CenarioItem * cenarioItemIncial) {
	Mistura misturas[3];

	misturas[0].novoItem = buscarCenarioItem(cenarioItemIncial, 1);
	misturas[0].itens[0] = *buscarCenarioItem(cenarioItemIncial, 1);
	misturas[0].itens[1] = *buscarCenarioItem(cenarioItemIncial, 2);
	misturas[0].itens[2] = *buscarCenarioItem(cenarioItemIncial, 3);

	misturas[1].novoItem = buscarCenarioItem(cenarioItemIncial, 2);
	misturas[1].itens[0] = *buscarCenarioItem(cenarioItemIncial, 1);
	misturas[1].itens[1] = *buscarCenarioItem(cenarioItemIncial, 2);
	misturas[1].itens[2] = *buscarCenarioItem(cenarioItemIncial, 3);
	//misturas[2].novoItem = buscarCenarioItem(cenarioItemIncial, 3);
	
	return misturas;
}

Mistura* realizarMistura(Mistura mistura, Inventario* inventario)
{

	if (misturaPossuiTodosIngredientes) {
		removerItemInventario(inventario);
		inserirItemInventario(inventario, mistura.novoItem);
	}
	else {
		removerItemInventario(inventario);
	}
}

