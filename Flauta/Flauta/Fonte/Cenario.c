#include "../Cabecalho/Cenario.h"


cJSON * lerJson(char * json) {
	cJSON * cJson = NULL;
	cJson = cJSON_Parse(json);

	if (!json) {
		printf("Error ao converter dados Cenario: [%s]\n", cJSON_GetErrorPtr());
		cJSON_Delete(json);
		exit(1);
	}

	return cJson;
}
cJSON * buscarItemObject(cJSON * baseBusca, char * item) {
	if (baseBusca != NULL) {
		if (baseBusca->string != NULL && strcmp(baseBusca->string, item) == 0)
			return baseBusca;
		return buscarItemObject(baseBusca->next, item);
	}

	return NULL;
}

CenarioItem* primeiroNo = NULL;
CenarioItem* ultimoNo = NULL;

void obteItemCenarioJson(cJSON * cJson) {
	CenarioItem * cenarioItem = (CenarioItem*)malloc(sizeof(CenarioItem));

	if (primeiroNo == NULL) {
		cenarioItem->count = (int*)malloc(sizeof(int));
		(* cenarioItem->count) = 0;
		primeiroNo = cenarioItem;
	}
	else {
		ultimoNo->proximo = cenarioItem;
		cenarioItem->count = primeiroNo->count;
	}

	cenarioItem->nome = buscarItemObject(cJson, "nome")->valuestring;
	cenarioItem->descricao = buscarItemObject(cJson, "descricao")->valuestring;
	cenarioItem->enderecoImagem = buscarItemObject(cJson, "imagem")->valuestring;

	cenarioItem->posicao = (Posicao*)malloc(sizeof(Posicao));
	cJSON * cJsonPosicao = buscarItemObject(cJson, "posicao");

	cenarioItem->posicao->posicaoX = buscarItemObject(cJsonPosicao->child, "posicaoX")->valueint;
	cenarioItem->posicao->posicaoY = buscarItemObject(cJsonPosicao->child, "posicaoY")->valueint;
	cenarioItem->posicao->tamanhoX = buscarItemObject(cJsonPosicao->child, "tamanhoX")->valueint;
	cenarioItem->posicao->tamanhoY = buscarItemObject(cJsonPosicao->child, "tamanhoY")->valueint;

	cenarioItem->proximo = NULL;
	(*cenarioItem->count)++;
	cenarioItem->codigo = (*primeiroNo->count) - 1;
	ultimoNo = cenarioItem;
}

CenarioItem * mapearCenario(cJSON* itensV) {
	obteItemCenarioJson(itensV->child);
	if (itensV->next != NULL)
		mapearCenario(itensV->next);

	return primeiroNo;
}

void destruirCenarioItem(CenarioItem * inicioDestruicao) {
	if (inicioDestruicao != NULL) {
		if (inicioDestruicao->proximo != NULL)
			destruirCenarioItem(inicioDestruicao->proximo);

		if (inicioDestruicao->posicao != NULL)
			free(inicioDestruicao->posicao);
		(*inicioDestruicao->count)--;
		free(inicioDestruicao);
		inicioDestruicao = NULL;
	}
}

cJSON * obterDados(void) {
	FILE* arquivo = fopen("Utils/ItensCenario.json", "r");//Abri um arquivo

	//Verifica se o arquivo existe
	if (arquivo == NULL) {
		printf("Não foi possivel obter os dados do cenario.\n");
		exit(1);
	}

	long tamanho;
	char * dados;

	fseek(arquivo, 0, SEEK_END);//Move o ponteiro dentro de um arquivo (SEEK_END = Final do arquivo.)
	tamanho = ftell(arquivo); //Obtém a posição atual de um ponteiro de arquivo.
	fseek(arquivo, 0, SEEK_SET);// SEEK_SET = Início do arquivo.

	dados = (char*)malloc(tamanho + 1); //Aloca em memoria o tamanho do arquivo
	
	fread(dados, 1, tamanho, arquivo); //size_t fread(void* destino Leitura, size_t size, size_t quantidade de itens a ser lidos, FILE * arquivo);
	fclose(arquivo);//Fecha o arquivo

	cJSON * cJson = lerJson(dados);
	free(dados);

	return cJson;
}