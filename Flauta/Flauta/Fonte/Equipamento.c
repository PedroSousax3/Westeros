#include "../Cabecalho/Equipamento.h"
#include "../Utilitario.h"

void gerarNomeEquipamento(Equipamento* equipamento) {
	switch (equipamento->codigo)
	{
		case EquipamentoEnumAgua:
			equipamento->qtdOndeEncontrar = gerarNumeroAleatorioInt(0, 5);
			/*equipamento->nome[0] = "Água";
			equipamento->nome[0] = "Uma substância abundante, pode ser facilmente encontrada em lagos e rios";*/
			break;
	}
}
void gerarPosicoesEquipamento(Equipamento* equipamento, Posicao posicoesOcupadas[], int qtdItensCriados) {
	for (int i = 0; i < qtdItensCriados; i++)
	{
		gerarNumeroAleatorioInt(0, 100);
	}
}
Equipamento gerarEquipamento(int codigo) {
	Equipamento equipamento = {
		.codigo = codigo
	};
	gerarNomeEquipamento(&equipamento);

	return equipamento;
}