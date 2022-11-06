#include "../Cabecalho/Cenario.h"

cJSON* obterCJsonCenario(void) {
	return obterCJson("Utils/ItensCenario.json");
}

CenarioItem * montarCenarioItemCJson(CenarioItem * noAnterior, cJSON * cenarioItemJson) {
	CenarioItem* cenarioItem = (CenarioItem*)malloc(sizeof(CenarioItem));

	if (noAnterior == NULL) {
		cenarioItem->count = (int*)malloc(sizeof(int));
		(*cenarioItem->count) = 0;
	}
	else {
		if (noAnterior != NULL)
			noAnterior->proximo = cenarioItem;
		cenarioItem->count = noAnterior->count;
	}

	cenarioItem->codigo = bucarItemCJson(cenarioItemJson, "codigo")->valueint;
	cenarioItem->nome = bucarItemCJson(cenarioItemJson, "nome")->valuestring;
	cenarioItem->descricao = bucarItemCJson(cenarioItemJson, "descricao")->valuestring;
	cenarioItem->coletavelPeloJogador = bucarItemCJson(cenarioItemJson, "coletavelPeloJogador")->valueint;
	cenarioItem->codigoItemInventario = bucarItemCJson(cenarioItemJson, "codigoItemInventario")->valueint;

	cJSON* imagemJson = bucarItemCJson(cenarioItemJson, "imagem");
	cenarioItem->imagem = (Imagem*)malloc(sizeof(Imagem));
	cenarioItem->imagem->endereco = bucarItemCJson(imagemJson->child, "endereco")->valuestring;
	cenarioItem->imagem->orientacao = bucarItemCJson(imagemJson->child, "orientacao")->valueint;
	cenarioItem->imagem->imagem = al_load_bitmap(cenarioItem->imagem->endereco);

	cenarioItem->elementoInical = mapaearElementosCenarios(NULL, cenarioItem, bucarItemCJson(cenarioItemJson, "elementos")->child);

	cenarioItem->proximo = NULL;
	(*cenarioItem->count)++;

	return cenarioItem;
}
CenarioItem * mapearCenariosItemCJson(CenarioItem* noAnterior, cJSON* cenarioItemJson) {
	if (cenarioItemJson != NULL) {
		CenarioItem* cenarioItem = montarCenarioItemCJson(noAnterior, cenarioItemJson->child);
		if (cenarioItemJson->next != NULL)
			mapearCenariosItemCJson(cenarioItem, cenarioItemJson->next);
	
		return cenarioItem;
	}

	return NULL;
}
void destruirCenarioItens(CenarioItem * cenarioItem) {
	if (cenarioItem != NULL) {
		if (cenarioItem->proximo != NULL)
			destruirCenarioItens(cenarioItem->proximo);

		(*cenarioItem->count)--;
		if (*cenarioItem->count == 0)
			free(cenarioItem->count);
		if (cenarioItem->imagem != NULL)
			free(cenarioItem->imagem);
		destruirElementosCenario(cenarioItem->elementoInical);
		free(cenarioItem);
	}
}

CenarioItem * buscarCenarioItem(CenarioItem * baseBusca, int codigoCenarioItem) {
	if (baseBusca != NULL && baseBusca->codigo == codigoCenarioItem)
		return baseBusca;
	else if (baseBusca->proximo != NULL)
		return buscarCenarioItem(baseBusca->proximo, codigoCenarioItem);

	return NULL;
}

ElementoCenario * mapearElemetosCenarioJson(ElementoCenario* noAnterior, CenarioItem * cenarioItem, cJSON* elementoCenarioJson) {
	ElementoCenario* elementoCenario = (ElementoCenario*)malloc(sizeof(ElementoCenario));

	if (noAnterior == NULL) {
		elementoCenario->count = (int*)malloc(sizeof(int));
		(*elementoCenario->count) = 0;
	}
	else {
		if (noAnterior != NULL)
			noAnterior->proximo = elementoCenario;
		elementoCenario->count = noAnterior->count;
	}

	elementoCenario->cenarioItem = cenarioItem;

	cJSON * posicaoAbsolutaJson = bucarItemCJson(elementoCenarioJson, "posicaoAbsoluta");
	elementoCenario->posicaoAbsoluta = (Posicao*)malloc(sizeof(Posicao));

	elementoCenario->posicaoAbsoluta->posicaoX = bucarItemCJson(posicaoAbsolutaJson->child, "posicaoX")->valueint;
	elementoCenario->posicaoAbsoluta->posicaoY = bucarItemCJson(posicaoAbsolutaJson->child, "posicaoY")->valueint;
	elementoCenario->posicaoAbsoluta->tamanhoX = bucarItemCJson(posicaoAbsolutaJson->child, "tamanhoX")->valueint;
	elementoCenario->posicaoAbsoluta->tamanhoY = bucarItemCJson(posicaoAbsolutaJson->child, "tamanhoY")->valueint;

	cJSON* posicaoRelativaJson = bucarItemCJson(elementoCenarioJson, "posicaoRelativa");
	elementoCenario->posicaoRelativa = (Posicao*)malloc(sizeof(Posicao));

	elementoCenario->posicaoRelativa->posicaoX = bucarItemCJson(posicaoRelativaJson->child, "posicaoX")->valueint;
	elementoCenario->posicaoRelativa->posicaoY = bucarItemCJson(posicaoRelativaJson->child, "posicaoY")->valueint;
	elementoCenario->posicaoRelativa->tamanhoX = bucarItemCJson(posicaoRelativaJson->child, "tamanhoX")->valueint;
	elementoCenario->posicaoRelativa->tamanhoY = bucarItemCJson(posicaoRelativaJson->child, "tamanhoY")->valueint;

	elementoCenario->proximo = NULL;
	(*elementoCenario->count)++;

	return elementoCenario;
}

ElementoCenario * mapaearElementosCenarios(ElementoCenario * noAnterior, CenarioItem * cenarioItem, cJSON * elemtoCenarioJson) {
	if (elemtoCenarioJson != NULL) {
		ElementoCenario * elenmentoCenario = mapearElemetosCenarioJson(noAnterior, cenarioItem, elemtoCenarioJson->child);
		if (elemtoCenarioJson->next != NULL)
			mapaearElementosCenarios(elenmentoCenario, cenarioItem, elemtoCenarioJson->next);

		return elenmentoCenario;
	}

	return NULL;
}

void destruirElementosCenario(ElementoCenario * elementoCenario) {
	if (elementoCenario != NULL) {
		if (elementoCenario->proximo != NULL)
			destruirElementosCenario(elementoCenario->proximo);

		(*elementoCenario->count)--;
		if (*elementoCenario->count == 0)
			free(elementoCenario->count);
		if (elementoCenario->posicaoAbsoluta != NULL)
			free(elementoCenario->posicaoAbsoluta);
		if (elementoCenario->posicaoRelativa != NULL)
			free(elementoCenario->posicaoRelativa);
		free(elementoCenario);
	}
}

void desenharElementosCenario(ElementoCenario elementoCenario) {
	desenharImagem(*elementoCenario.cenarioItem->imagem, *elementoCenario.posicaoAbsoluta);
	if (elementoCenario.proximo != NULL)
		desenharElementosCenario(*elementoCenario.proximo);
}

void desenharCenarioItens(CenarioItem * cenarioItenInicial) {
	if (cenarioItenInicial != NULL) {
		if (cenarioItenInicial->imagem->imagem != NULL && cenarioItenInicial->elementoInical != NULL)
			desenharElementosCenario(*cenarioItenInicial->elementoInical);
		if (cenarioItenInicial->proximo != NULL)
			desenharCenarioItens(cenarioItenInicial->proximo);
	}
}

bool colediuComElementoCenario(ElementoCenario * elementoCenario, Posicao posicaoComparacao) {
	if (elementoCenario != NULL) {
		if (posicaoColediu(*elementoCenario->posicaoRelativa, posicaoComparacao))
			return true;
		else if (elementoCenario->proximo != NULL)
			return colediuComElementoCenario(elementoCenario->proximo, posicaoComparacao);
	}

	return false;
}

bool colediuComCenario(CenarioItem * cenarioItenInicial, Posicao posicaoComparacao) {
	if (cenarioItenInicial != NULL && cenarioItenInicial->elementoInical != NULL) {
		if (colediuComElementoCenario(cenarioItenInicial->elementoInical, posicaoComparacao))
			return true;
		else if (cenarioItenInicial->proximo != NULL)
			return colediuComCenario(cenarioItenInicial->proximo, posicaoComparacao);
	}
		
	return false;
}