#include "../Cabecalho/Mistura.h"

bool misturaPossuiTodosIngredientes(Mistura mistura, Inventario * inventario) {
	for (int i = 0; i < 3; i++)
		if (buscarItemInventario(inventario, mistura.itens[i].codigo) == NULL)
			return false;

	return true;
}

Mistura* iniciarMisturas(CenarioItem* cenarioItemIncial) {
	Mistura misturas[3];

	misturas[0].novoItem = buscarCenarioItem(cenarioItemIncial, 17);
	misturas[0].itens[0] = *buscarCenarioItem(cenarioItemIncial, 14);
	misturas[0].itens[1] = *buscarCenarioItem(cenarioItemIncial, 9);
	misturas[0].itens[2] = *buscarCenarioItem(cenarioItemIncial, 8);

	misturas[1].novoItem = buscarCenarioItem(cenarioItemIncial, 18);
	misturas[1].itens[0] = *buscarCenarioItem(cenarioItemIncial, 14);
	misturas[1].itens[1] = *buscarCenarioItem(cenarioItemIncial, 13);
	misturas[1].itens[2] = *buscarCenarioItem(cenarioItemIncial, 12);
	 
	misturas[2].novoItem = buscarCenarioItem(cenarioItemIncial, 19);
	misturas[2].itens[0] = *buscarCenarioItem(cenarioItemIncial, 11);
	misturas[2].itens[1] = *buscarCenarioItem(cenarioItemIncial, 10);
	misturas[2].itens[2] = *buscarCenarioItem(cenarioItemIncial, 8);
	
	return misturas;
}

Mistura* realizarMistura(Mistura mistura, Inventario* inventario)
{
	iniciarMisturas(inventario);
	misturaPossuiTodosIngredientes(mistura, inventario);
	if (misturaPossuiTodosIngredientes) {
		removerItemInventario(inventario);
		inserirItemInventario(inventario, mistura.novoItem);
	}
	else {
		removerItemInventario(inventario);
	}
}

