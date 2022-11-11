#include "../Cabecalho/Inventario.h"

Inventario * inserirItemInventario(Inventario * inventarioAnterior, CenarioItem* cenarioItem) {
	Inventario* novoInventario = (Inventario*)malloc(sizeof(Inventario));

	if (inventarioAnterior == NULL) {
		inventarioAnterior = novoInventario;

		novoInventario->proximo = NULL;
		novoInventario->count = (int*)malloc(sizeof(int));
		(*novoInventario->count) = 1;
	}
	else {
		inventarioAnterior->proximo = novoInventario;

		novoInventario->count = inventarioAnterior->count;
		(*novoInventario->count)++;
	}

	novoInventario->cenarioItem = cenarioItem;
	novoInventario->indice = (*novoInventario->count) - 1;
	novoInventario->proximo = NULL;

	return novoInventario;
}

void removerItemInventario(Inventario * inventario) {
	(*inventario->count)--;
	if (inventario->count == 0)
		free(inventario->count);

	Inventario* proximo = inventario->proximo;
	alterarPosicaoChildren(proximo, -1);
	free(inventario);

	inventario = proximo;
}

void alterarPosicaoChildren(Inventario* inicio, int diferenca) {
	if (inicio != NULL)
	{
		inicio->indice = inicio->indice + diferenca;
		if (inicio->proximo != NULL)
			alterarPosicaoChildren(inicio->proximo, diferenca);
	}
}

void desenharItensInventarios(Inventario inventarioInicial) {
	desenharImagem(*inventarioInicial.cenarioItem->imagem, *inventarioInicial.posicaoAbsoluta);
}