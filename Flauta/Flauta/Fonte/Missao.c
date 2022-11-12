#include "../Cabecalho/Missao.h"

cJSON * obterMissoesJson() {
	return obterCJson("Utils/Missoes.json");
}

Missao * montarMissaoDeJson(Missao* missaoAnterior, cJSON* jsonMissao, CenarioItem * cenarioItem) {
	Missao* missao = (Missao*)malloc(sizeof(Missao));

	if (missaoAnterior == NULL) {
		missao->count = (int*)malloc(sizeof(int));
		(*missao->count) = 0;
	}
	else {
		if (missaoAnterior != NULL)
			missaoAnterior->proxima = missao;
		missao->count = missaoAnterior->count;
	}

	missao->codigo = bucarItemCJson(jsonMissao, "codigo")->valueint;
	missao->nome = bucarItemCJson(jsonMissao, "nome")->valuestring;
	missao->mensagemInicial = bucarItemCJson(jsonMissao, "mensagemInicial")->valuestring;
	missao->mensagemFinal = bucarItemCJson(jsonMissao, "mensagemFinal")->valuestring;

	cJSON* jsonPassos = bucarItemCJson(jsonMissao, "passos")->child;
	missao->passosMissao = mapearPassosMissaoDeJson(NULL, jsonPassos, cenarioItem);

	missao->proxima = NULL;
	(*missao->count)++;

	return missao;
}

Missao * mapearMissoesDeJson(Missao* missaoAnterior, cJSON* missoaJson, CenarioItem * cenarioInicial) {
	if (missoaJson != NULL) {
		Missao * missao = montarMissaoDeJson(missaoAnterior, missoaJson->child, cenarioInicial);

		if (missoaJson->next != NULL)
			mapearMissoesDeJson(missao, missoaJson->next, cenarioInicial);

		return missao;
	}
		
	return NULL;
}

void destruirMissoes(Missao * missao) {
	if (missao != NULL) {
		if (missao->proxima != NULL)
			destruirMissoes(missao->proxima);

		(*missao->count)--;
		if (*missao->count == 0)
			free(missao->count);
		free(missao);
	}
}

PassoMissao* montarPassoMissaoDeCJson(PassoMissao* passoaMissoaAnterior, cJSON* jsonPassoMissao, CenarioItem * cenarioInicial) {
	PassoMissao* passoMissao = (PassoMissao*)malloc(sizeof(PassoMissao));

	if (passoaMissoaAnterior == NULL) {
		passoMissao->count = (int*)malloc(sizeof(int));
		(*passoMissao->count) = 0;
	}
	else {
		if (passoaMissoaAnterior != NULL)
			passoaMissoaAnterior->proxima = passoMissao;
		passoMissao->count = passoaMissoaAnterior->count;
	}

	passoMissao->executar = bucarItemCJson(jsonPassoMissao, "executar")->valueint;
	passoMissao->mensagemInicial = bucarItemCJson(jsonPassoMissao, "mensagemInicial")->valuestring;
	passoMissao->mensagemFinal = bucarItemCJson(jsonPassoMissao, "mensagemFinal")->valuestring;
	passoMissao->quando = bucarItemCJson(jsonPassoMissao, "quando")->valueint;
	passoMissao->cenarioItem = buscarCenarioItem(cenarioInicial, bucarItemCJson(jsonPassoMissao, "cenarioItem")->valueint);

	passoMissao->proxima = NULL;
	(*passoMissao->count)++;

	return passoMissao;
}

PassoMissao* mapearPassosMissaoDeJson(PassoMissao* noAnterior, cJSON* passoJson, CenarioItem* cenarioInicial) {
	if (passoJson != NULL) {
		PassoMissao* passoMissao = montarPassoMissaoDeCJson(noAnterior, passoJson->child, cenarioInicial);

		if (passoJson->next != NULL)
			mapearPassosMissaoDeJson(passoMissao, passoJson->next, cenarioInicial);

		return passoMissao;
	}

	return NULL;
}

void destruirPassosMissao(PassoMissao* passoMissao) {

}