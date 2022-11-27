#ifndef Cabecalho_Missao
#define Cabecalho_Missao

#include "CenarioItem.h"
#include "Cenario.h"
#include "Mistura.h"
#include "Utils/ManipularJson.h"
#include "../libs/cJSON/cJSON.h"

typedef enum EnumPassoAcao;
typedef enum EnumPassoQuandoExecutar;
typedef struct Missao Missao;
typedef struct PassoMissao PassoMissao;

/// <summary>
/// Eventos que devem ser acionados na conclus�o de cada passo.
/// </summary>
enum EnumPassoAcao {
	MostrarMensagem = 1,
	VerificarItensInventario
};
/// <summary>
/// Enum com os possivel eventos para a conclus�o de um passo
/// </summary>
enum EnumPassoQuandoExecutar {
	/// <summary>
	/// Evento ocorre com click no bot�o esquerdo do mouses
	/// </summary>
	Click = 1,
	ColetarItem
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
	struct Mistura * misturaFinal;
	/// <summary>
	/// Passos que devem ser realizandos para a conclus�o da miss�o
	/// </summary>
	struct PassoMissao * passosMissao;
	/// <summary>
	/// Indice da miss�o no vetor dinamico Miss�es
	/// </summary>
	int indice;
	/// <summary>
	/// Quantidade de misso�es disponiveis no vetor dinamico
	/// </summary>
	int* count;
	/// <summary>
	/// Proxima miss�o
	/// </summary>
	struct Missao* proxima;
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
	/// Informa se o passo � nescessario para a conclusao da miss�o
	/// </summary>
	bool obrigatorio;
	/// <summary>
	/// Quando uma tarefa deve ser fizalinada.
	/// </summary>
	int quando;
	/// <summary>
	/// Elemento em que o evento deve ocorrer para finalizar a tarefa
	/// </summary>
	struct CenarioItem * cenarioItem;
	/// <summary>
	/// Posicao do passo
	/// </summary>
	int indice;
	/// <summary>
	/// Quantidade de misso�es disponiveis no vetor dinamico
	/// </summary>
	int* count;
	struct PassoMissao * proxima;
};
/// <summary>
/// Obtem o objeto cJSON com as inform��es das miss�es do jogo
/// </summary>
/// <returns>Struct cJSON com as informa��es do jogo</returns>
cJSON * obterMissoesJson();
/// <summary>
/// Gera uma struct de Miss�o populado com os dados obtido no parametro jsonMissao
/// </summary>
/// <param name="missaoAnterior">A miss�o que foi gerada antes da atual. Caso n�o tenha informa NULL</param>
/// <param name="jsonMissao">Struct cJSON com as informa��es da miss�o que deseja</param>
/// <param name="cenarioInicial">Objeto de cenarioInicial para consultar cenarioItem do passo.</param>
/// <returns>Objeto de miss�o mapedo apartir do parametro cJSON</returns>
Missao* montarMissaoDeJson(Missao* missaoAnterior, cJSON* jsonMissao, CenarioItem* cenarioInicial);
/// <summary>
/// Fun��o recursiva que utiliza o metodo montarMissaoDeJson para popular todas as missoes de um cJSON
/// </summary>
/// <param name="missaoAnterior">A miss�o que foi gerada antes da atual. Caso n�o tenha informa NULL</param>
/// <param name="missoaJson">cJSON de onde come�ar� a buscar as missoes</param>
/// <param name="cenarioInicial">Objeto de cenarioInicial para consultar cenarioItem do passo.</param>
/// <returns>Retorna o primerio struct mapeada de Missao</returns>
Missao* mapearMissoesDeJson(Missao* missaoAnterior, cJSON* missoaJson, CenarioItem* cenarioInicial);
/// <summary>
/// Destri a miss�o e seus n�s filhos
/// </summary>
/// <param name="missao">Inicio da destrui��o</param>
void destruirMissoes(Missao* missao);
/// <summary>
/// Gera uma struct de PassoMissao populado com os dados obtido no parametro jsonPassoMissao
/// </summary>
/// <param name="passoaMissoaAnterior">O passoMissao que foi gerada antes da atual. Caso n�o tenha informa NULL</param>
/// <param name="jsonPassoMissao">Struct cJSON com as informa��es passo que deseja.</param>
/// <param name="cenarioInicial">Objeto de cenarioInicial para consultar cenarioItem do passo.</param>
/// <returns>Objeto de passo mapedo apartir do parametro cJSON</returns>
PassoMissao* montarPassoMissaoDeCJson(PassoMissao* passoaMissoaAnterior, cJSON* jsonPassoMissao, CenarioItem* cenarioInicial);
/// <summary>
/// Fun��o recursiva que utiliza o metodo montarPassoMissaoDeCJson para popular todos os passos de uma miss�o de um cJSON
/// </summary>
/// <param name="noAnterior">O passo que foi gerado antes da atual. Caso n�o tenha informo NULL</param>
/// <param name="passoJson">cJSON de onde come�ar� a buscar os passos</param>
/// <param name="cenarioInicial">Objeto de cenarioInicial para consultar cenarioItem do passo.</param>
/// <returns>Retorna o primerio struct mapeada de PassoMissao</returns>
PassoMissao* mapearPassosMissaoDeJson(PassoMissao* noAnterior, cJSON* passoJson, CenarioItem* cenarioInicial);
/// <summary>
/// Destroi um passo e seus n�s filhos
/// </summary>
/// <param name="passoMissao">Inicio da destrui��o</param>
void destruirPassosMissao(PassoMissao * passoMissao);
/// <summary>
/// Coleta a posi��o em que as misturas poder� ser realizada
/// </summary>
/// <param name="posicaoMisturaCJson">cJSON base para a coleta das indorma��es da posi��o</param>
/// <returns>Posi��o em que as misturas ser�o realizadas</returns>
Posicao* mapearPosicaoMistura(cJSON* posicaoMisturaCJson);
#endif // !Cabecalho_Missao