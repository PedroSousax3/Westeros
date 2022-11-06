#include "../Cabecalho/Mistura.h"

bool misturaPossuiTodosIngredientes(Mistura* mistura, Equipamento estoqueEquipamentos[10]) {
	int qtd = sizeof(mistura->ingredientes) / sizeof(Equipamento);
	for (int i = 0; i < qtd; i++) {
		int qtdEstoque = sizeof(estoqueEquipamentos) / sizeof(Equipamento);
		bool contem = false;
		for (int indiceEstoque = 0; indiceEstoque < qtdEstoque; indiceEstoque++) {
			if (estoqueEquipamentos[indiceEstoque].codigo == mistura->ingredientes[i].codigo) {
				contem = true;
				break;
			}
		}
		if (!contem)
			return false;
	}
	return true;
}
void misturaSepararIngredientes(Mistura* mistura, Equipamento* estoqueEquipamentos[]);
Equipamento misturaCriarEquipamento(Mistura* mistura, Equipamento estoqueEquipamentos[]);