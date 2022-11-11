#ifndef Cabecalho_Missao
#define Cabecalho_Missao

#include "CenarioItem.h"
#include "Mistura.h"

typedef enum EnumPassoAcao;
typedef enum EnumPassoQuandoExecutar;
typedef struct MissaoDef Missao;
typedef struct PassoMissaoDef PassoMissao;

/// <summary>
/// Eventos que devem ser acionados na conclus�o de cada passo.
/// </summary>
enum EnumPassoAcao {
	mostrarMensagem = 1,
	verificarHaTodosOsItemMistura
};
/// <summary>
/// Enum com os possivel eventos para a conclus�o de um passo
/// </summary>
enum EnumPassoQuandoExecutar {
	/// <summary>
	/// Evento de click
	/// </summary>
	Click = 1
};
/// <summary>
/// Struct com as defini��es de cada miss�o do jogo
/// </summary>
struct Missao {
	/// <summary>
	/// C�digo da miss�o
	/// </summary>
	int codigo;
	/// <summary>
	/// Nome da miss�o
	/// </summary>
	char* nome;
	/// <summary>
	/// Texto que deve ser exibido para o usuario ao inicio da miss�o
	/// </summary>
	char* mensagemInicial;
	/// <summary>
	/// Texto que deve ser exibido para o usuario ao final da miss�o
	/// </summary>
	char* mensagemFinal;
	/// <summary>
	/// O objetivo da miss�o ser� gerar esse mistura
	/// </summary>
	Mistura misturaFinal;
	/// <summary>
	/// Passos que devem ser realizandos para a conclus�o da miss�o
	/// </summary>
	PassoMissao * passosMissao;
	/// <summary>
	/// Indice da miss�o no vetor dinamico Miss�es
	/// </summary>
	int indice;
	/// <summary>
	/// Quantidade de misso�es disponiveis no vetor dinamico
	/// </summary>
	int* count;
};
/// <summary>
/// Passos que devem ser executados para a finaliza��o da miss�o
/// </summary>
struct PassoMissao {
	/// <summary>
	/// Qual fun��o ser� executada ao final da tarefa
	/// </summary>
	int executar;
	/// <summary>
	/// Mensagem que ser� mostrada ao usuario quando iniciar a tarefa
	/// </summary>
	char* mensagemInicial;
	/// <summary>
	/// Mensagem que ser� mostrada ao usuario ao final da tarefa
	/// </summary>
	char* mensagemFinal;
	/// <summary>
	/// Quando uma tarefa deve ser fizalinada.
	/// </summary>
	int quando;
	/// <summary>
	/// Elemento em que o evento deve ocorrer para finalizar a tarefa
	/// </summary>
	CenarioItem* cenarioItem;
};

#endif // !Cabecalho_Missao