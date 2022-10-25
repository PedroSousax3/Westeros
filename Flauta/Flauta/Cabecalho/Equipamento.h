#ifndef Cabecalho_Equipamento
#define Cabecalho_Equipamento

#include "Posicao.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Equipamento {
	int codigo;
	char nome[30];
	char descricao[300];

	int qtdOndeEncontrar;
	Posicao ondeEncontrar[10];
} Equipamento;

typedef enum EquipamentoEnum {
	EquipamentoEnumAgua = 1,
	EquipamentoEnumSal
} EquipamentoEnum;

void gerarNomeEquipamento(Equipamento * equipamento);
void gerarPosicoesEquipamento(Equipamento* equipamento, Posicao posicoesOcupadas [], int qtdItensCriados);
Equipamento gerarEquipamento(int codigo);
#endif // !Cabecalho_Equipamento
