#ifndef Cabecalho_Missao
#define Cabecalho_Missao

#include "CenarioItem.h"
#include "Mistura.h"

typedef enum EnumPassoAcao;
typedef enum EnumPassoQuandoExecutar;
typedef struct MissaoDef Missao;
typedef struct PassoMissaoDef PassoMissao;

/// <summary>
/// Eventos que devem ser acionados na conclusão de cada passo.
/// </summary>
enum EnumPassoAcao {
	mostrarMensagem = 1,
	verificarHaTodosOsItemMistura
};
/// <summary>
/// Enum com os possivel eventos para a conclusão de um passo
/// </summary>
enum EnumPassoQuandoExecutar {
	/// <summary>
	/// Evento de click
	/// </summary>
	Click = 1
};
/// <summary>
/// Struct com as definições de cada missão do jogo
/// </summary>
struct Missao {
	/// <summary>
	/// Código da missão
	/// </summary>
	int codigo;
	/// <summary>
	/// Nome da missão
	/// </summary>
	char* nome;
	/// <summary>
	/// Texto que deve ser exibido para o usuario ao inicio da missão
	/// </summary>
	char* mensagemInicial;
	/// <summary>
	/// Texto que deve ser exibido para o usuario ao final da missão
	/// </summary>
	char* mensagemFinal;
	/// <summary>
	/// O objetivo da missão será gerar esse mistura
	/// </summary>
	Mistura misturaFinal;
	/// <summary>
	/// Passos que devem ser realizandos para a conclusão da missão
	/// </summary>
	PassoMissao * passosMissao;
	/// <summary>
	/// Indice da missão no vetor dinamico Missões
	/// </summary>
	int indice;
	/// <summary>
	/// Quantidade de missoões disponiveis no vetor dinamico
	/// </summary>
	int* count;
};
/// <summary>
/// Passos que devem ser executados para a finalização da missão
/// </summary>
struct PassoMissao {
	/// <summary>
	/// Qual função será executada ao final da tarefa
	/// </summary>
	int executar;
	/// <summary>
	/// Mensagem que será mostrada ao usuario quando iniciar a tarefa
	/// </summary>
	char* mensagemInicial;
	/// <summary>
	/// Mensagem que será mostrada ao usuario ao final da tarefa
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