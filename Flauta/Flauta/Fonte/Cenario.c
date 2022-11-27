#include "../Cabecalho/Cenario.h"
#include "../Cabecalho/Posicao.h"

cJSON* obterCJsonCenario(void) {
	return obterCJson("Utils/ItensCenario.json");
}

ElementoCenario * gerarElementosCenario(CenarioItem* cenarioItem, int qtdGerar, Posicao posicaoInicialGeracao, Posicao poseicaoBase, CenarioItem * cenarioItemIncial) {
	ElementoCenario* primeiro = NULL;
	ElementoCenario* noAnterior = NULL;
	ElementoCenario* noProximo = NULL;

	for (int i = 0; i < qtdGerar; i++) {
		int x = gerarNumeroAleatorioInt(posicaoInicialGeracao.posicaoX, posicaoInicialGeracao.tamanhoX - poseicaoBase.tamanhoX);
		int y = gerarNumeroAleatorioInt(posicaoInicialGeracao.posicaoY, posicaoInicialGeracao.tamanhoY - poseicaoBase.tamanhoY);

		Posicao posicaoValidar = {
			.posicaoX = x,
			.posicaoY = y,
			.tamanhoX = poseicaoBase.tamanhoX,
			.tamanhoY = poseicaoBase.tamanhoY
		};

		if (colediuComCenario(cenarioItemIncial, posicaoValidar, false)) {
			i--;
		} 
		else {
			ElementoCenario* elementoCenario = (ElementoCenario*)malloc(sizeof(ElementoCenario));
			elementoCenario->proximo = NULL;
			elementoCenario->anterior = NULL;

			elementoCenario->cenarioItem = cenarioItem;

			elementoCenario->posicaoAbsoluta = (Posicao*)malloc(sizeof(Posicao));
			elementoCenario->posicaoRelativa = (Posicao*)malloc(sizeof(Posicao));

			elementoCenario->posicaoAbsoluta->posicaoX = x;
			elementoCenario->posicaoAbsoluta->posicaoY = y;
			elementoCenario->posicaoAbsoluta->tamanhoX = poseicaoBase.tamanhoX;
			elementoCenario->posicaoAbsoluta->tamanhoY = poseicaoBase.tamanhoY;

			elementoCenario->posicaoRelativa->posicaoX = x;
			elementoCenario->posicaoRelativa->posicaoY = y;
			elementoCenario->posicaoRelativa->tamanhoX = poseicaoBase.tamanhoX;
			elementoCenario->posicaoRelativa->tamanhoY = poseicaoBase.tamanhoY;
		
			if (primeiro == NULL) {
				primeiro = elementoCenario;
				primeiro->anterior = NULL;
				elementoCenario->count = (int*)malloc(sizeof(int));
				(*elementoCenario->count) = 0;
			}
			else if (noAnterior != NULL) {
				noAnterior->proximo = elementoCenario;
				elementoCenario->anterior = noAnterior;
				elementoCenario->count = noAnterior->count;
			}

			elementoCenario->proximo = NULL;
			elementoCenario->indice = (*elementoCenario->count);
			(*elementoCenario->count)++;
			noAnterior = elementoCenario;
		}		
	}

	return primeiro;
}
CenarioItem * montarCenarioItemCJson(CenarioItem * noAnterior, cJSON * cenarioItemJson, CenarioItem * cenarioItemIncial) {
	CenarioItem* cenarioItem = (CenarioItem*)malloc(sizeof(CenarioItem));
	cenarioItem->proximo = NULL;

	if (noAnterior == NULL) {
		cenarioItem->count = (int*)malloc(sizeof(int));
		cenarioItemIncial = cenarioItem;
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
	//cenarioItem->codigoItemInventario = bucarItemCJson(cenarioItemJson, "codigoItemInventario")->valueint;

	cJSON* imagemJson = bucarItemCJson(cenarioItemJson, "imagem");
	cenarioItem->imagem = (Imagem*)malloc(sizeof(Imagem));
	cenarioItem->imagem->endereco = bucarItemCJson(imagemJson->child, "endereco")->valuestring;
	cenarioItem->imagem->orientacao = bucarItemCJson(imagemJson->child, "orientacao")->valueint;
	cenarioItem->imagem->imagem = al_load_bitmap(cenarioItem->imagem->endereco);

	cJSON* imagemInventarioJson = bucarItemCJson(cenarioItemJson, "imagemInventario");
	if (imagemInventarioJson->child == NULL)
		cenarioItem->imagemInventario = NULL;
	else
	{
		cenarioItem->imagemInventario = (Imagem*)malloc(sizeof(Imagem));
		cenarioItem->imagemInventario->endereco = bucarItemCJson(imagemInventarioJson->child, "endereco")->valuestring;
		cenarioItem->imagemInventario->orientacao = bucarItemCJson(imagemInventarioJson->child, "orientacao")->valueint;
		cenarioItem->imagemInventario->imagem = al_load_bitmap(cenarioItem->imagemInventario->endereco);
	}

	//Todos os itens dentro do vetor randomElementos
	cJSON* randomElementesJson = bucarItemCJson(cenarioItemJson, "randomElementes")->child;

	if (randomElementesJson != NULL) {		
		cJSON* atualCJsonAleatorio = randomElementesJson;

		cenarioItem->elementoInical = NULL;


		while (atualCJsonAleatorio != NULL) {
			//Quantidade de itens que devem ser gerados
			int qtdGerar = bucarItemCJson(atualCJsonAleatorio->child, "qtdItens")->valueint;

			cJSON* posicaoGeracaoJson = bucarItemCJson(randomElementesJson->child, "posicaoGeracao")->child;

			//Container que define o inicio e fim da geração dos elementos
			Posicao posicaoGerar = {
				.posicaoX = bucarItemCJson(posicaoGeracaoJson, "posicaoX")->valueint,
				.posicaoY = bucarItemCJson(posicaoGeracaoJson, "posicaoY")->valueint,
				.tamanhoX = bucarItemCJson(posicaoGeracaoJson, "tamanhoX")->valueint,
				.tamanhoY = bucarItemCJson(posicaoGeracaoJson, "tamanhoY")->valueint,
			};

			//Dados da posicção base dos elementos
			Posicao posicaoBase = {
				.tamanhoX = bucarItemCJson(atualCJsonAleatorio->child, "tamanhoX")->valueint,
				.tamanhoY = bucarItemCJson(atualCJsonAleatorio->child, "tamanhoY")->valueint,
			};

			if (cenarioItem->elementoInical == NULL)
				cenarioItem->elementoInical = gerarElementosCenario(cenarioItem, qtdGerar, posicaoGerar, posicaoBase, cenarioItemIncial);
			else {
				ElementoCenario * ultimo = obterUltimoElementoCenario(cenarioItem->elementoInical);
				ultimo->proximo = gerarElementosCenario(cenarioItem, qtdGerar, posicaoGerar, posicaoBase, cenarioItemIncial);
			}

			atualCJsonAleatorio = atualCJsonAleatorio->next;
		}
	}
	else
		cenarioItem->elementoInical = mapaearElementosCenarios(NULL, cenarioItem, bucarItemCJson(cenarioItemJson, "elementos")->child);

	cenarioItem->proximo = NULL;
	(*cenarioItem->count)++;

	return cenarioItem;
}

CenarioItem * mapearCenariosItemCJson(CenarioItem* noAnterior, cJSON* cenarioItemJson, CenarioItem * cenarioItemIncial) {
	if (cenarioItemJson != NULL) {
		CenarioItem* cenarioItem = montarCenarioItemCJson(noAnterior, cenarioItemJson->child, cenarioItemIncial);
		if (noAnterior == NULL)
			cenarioItemIncial = cenarioItem;
		if (cenarioItemJson->next != NULL)
			mapearCenariosItemCJson(cenarioItem, cenarioItemJson->next, cenarioItemIncial);
	
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
	elementoCenario->proximo = NULL;
	elementoCenario->anterior = NULL;

	if (noAnterior == NULL) {
		elementoCenario->count = (int*)malloc(sizeof(int));
		(*elementoCenario->count) = 0;
		elementoCenario->anterior = NULL;
	}
	else {
		if (noAnterior != NULL) {
			noAnterior->proximo = elementoCenario;
			elementoCenario->anterior = noAnterior;
		}
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
	elementoCenario->indice = (*elementoCenario->count);
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

bool colediuComElementoCenario(ElementoCenario * elementoCenario, Posicao posicaoComparacao, bool useRelative) {
	if (elementoCenario != NULL) {
		if (posicaoColediu(useRelative  ? *elementoCenario->posicaoRelativa : *elementoCenario->posicaoAbsoluta, posicaoComparacao))
			return true;
		else if (elementoCenario->proximo != NULL)
			return colediuComElementoCenario(elementoCenario->proximo, posicaoComparacao, useRelative);
	}

	return false;
}

bool colediuComCenario(CenarioItem * cenarioItenInicial, Posicao posicaoComparacao, bool useRelative) {
	if (cenarioItenInicial != NULL) {
		if (colediuComElementoCenario(cenarioItenInicial->elementoInical, posicaoComparacao, useRelative))
			return true;
		else if (cenarioItenInicial->proximo != NULL)
			return colediuComCenario(cenarioItenInicial->proximo, posicaoComparacao, useRelative);
	}
		
	return false;
}

ElementoCenario * buscarElementoCenarioPorPosicao(ElementoCenario * elementoCenario, Posicao posicao, bool useRelative) {
	if (posicaoColediu(useRelative ? *elementoCenario->posicaoRelativa : *elementoCenario->posicaoAbsoluta, posicao))
		return elementoCenario;
	else if (elementoCenario->proximo != NULL)
		return buscarElementoCenarioPorPosicao(elementoCenario->proximo, posicao, useRelative);

	return NULL;
}

ElementoCenario * obterElementoCenarioEmPosicao(CenarioItem * cenarioItemInicial, Posicao posicao, bool useRelative) {
	if (cenarioItemInicial != NULL) {
		if (cenarioItemInicial->elementoInical != NULL)
		{
			ElementoCenario* elementoCenario = buscarElementoCenarioPorPosicao(cenarioItemInicial->elementoInical, posicao, useRelative);
			if (elementoCenario != NULL)
				return elementoCenario;
		}
		
		if (cenarioItemInicial->proximo != NULL)
			return obterElementoCenarioEmPosicao(cenarioItemInicial->proximo, posicao, useRelative);
	}

	return NULL;
}

ElementoCenario * removerElementoCenario (ElementoCenario * elementoCenario) {
	(*elementoCenario->count)--;
	if (elementoCenario->count == 0)
		free(elementoCenario->count);

	ElementoCenario* anterior = elementoCenario->anterior;
	ElementoCenario* proximo = elementoCenario->proximo;

	alterarPosicaoChildrenElementoCenario(proximo, -1);
	free(elementoCenario);

	if (anterior != NULL)
		anterior->proximo = proximo;
	if (proximo != NULL)
		proximo->anterior = anterior;

	if (anterior != NULL)
		return anterior;
	if (proximo != NULL)
		return proximo;

	return NULL;
}

void alterarPosicaoChildrenElementoCenario(ElementoCenario * inicio, int diferenca) {
	if (inicio != NULL)
	{
		inicio->indice = inicio->indice + diferenca;
		if (inicio->proximo != NULL)
			alterarPosicaoChildrenElementoCenario(inicio->proximo, diferenca);
	}
}

ElementoCenario* obterUltimoElementoCenario(ElementoCenario * elementoCenario) {
	if (elementoCenario->proximo == NULL)
		return elementoCenario;
	else
		return obterUltimoElementoCenario(elementoCenario->proximo);
}