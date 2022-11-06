#include "../../Cabecalho/Utils/ManipularJson.h"
#include <stdio.h>

cJSON * obterCJson(char * caminho) {
	FILE* arquivo = fopen(caminho, "r");//Abri um arquivo

	//Verifica se o arquivo existe
	if (arquivo == NULL) {
		printf("Não foi possivel obter os dados do cenario.\n");
		exit(1);
	}

	long tamanho;
	char* dados;

	fseek(arquivo, 0, SEEK_END);//Move o ponteiro dentro de um arquivo (SEEK_END = Final do arquivo.)
	tamanho = ftell(arquivo); //Obtém a posição atual de um ponteiro de arquivo.
	fseek(arquivo, 0, SEEK_SET);// SEEK_SET = Início do arquivo.

	dados = (char*)malloc(tamanho + 1); //Aloca em memoria o tamanho do arquivo

	fread(dados, 1, tamanho, arquivo); //size_t fread(void* destino Leitura, size_t size, size_t quantidade de itens a ser lidos, FILE * arquivo);
	fclose(arquivo);//Fecha o arquivo

	cJSON* cJson = cJSON_Parse(dados);
	free(dados);

	if (!cJson) {
		printf("Error ao converter dados Cenario: [%s]\n", cJSON_GetErrorPtr());
		cJSON_Delete(cJson);
		exit(1);
	}

	return cJson;
}

cJSON * bucarItemCJson(cJSON * baseBusca, char * item) {
	if (baseBusca != NULL) {
		if (baseBusca->string != NULL && strcmp(baseBusca->string, item) == 0)
			return baseBusca;
		return bucarItemCJson(baseBusca->next, item);
	}

	return NULL;
}