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
/// Eventos que devem ser acionados na conclusão de cada passo.
/// </summary>
enum EnumPassoAcao {
	MostrarMensagem = 1,
	VerificarItensInventario
};
/// <summary>
/// Enum com os possivel eventos para a conclusão de um passo
/// </summary>
enum EnumPassoQuandoExecutar {
	/// <summary>
	/// Evento ocorre com click no botão esquerdo do mouses
	/// </summary>
	Click = 1,
	ColetarItem
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
	struct Mistura * misturaFinal;
	/// <summary>
	/// Passos que devem ser realizandos para a conclusão da missão
	/// </summary>
	struct PassoMissao * passosMissao;
	/// <summary>
	/// Indice da missão no vetor dinamico Missões
	/// </summary>
	int indice;
	/// <summary>
	/// Quantidade de missoões disponiveis no vetor dinamico
	/// </summary>
	int* count;
	/// <summary>
	/// Proxima missão
	/// </summary>
	struct Missao* proxima;
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
	/// Informa se o passo é nescessario para a conclusao da missão
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
	/// Quantidade de missoões disponiveis no vetor dinamico
	/// </summary>
	int* count;
	struct PassoMissao * proxima;
};
/// <summary>
/// Obtem o objeto cJSON com as informções das missões do jogo
/// </summary>
/// <returns>Struct cJSON com as informações do jogo</returns>
cJSON * obterMissoesJson();
/// <summary>
/// Gera uma struct de Missão populado com os dados obtido no parametro jsonMissao
/// </summary>
/// <param name="missaoAnterior">A missão que foi gerada antes da atual. Caso não tenha informa NULL</param>
/// <param name="jsonMissao">Struct cJSON com as informações da missão que deseja</param>
/// <param name="cenarioInicial">Objeto de cenarioInicial para consultar cenarioItem do passo.</param>
/// <returns>Objeto de missão mapedo apartir do parametro cJSON</returns>
Missao* montarMissaoDeJson(Missao* missaoAnterior, cJSON* jsonMissao, CenarioItem* cenarioInicial);
/// <summary>
/// Função recursiva que utiliza o metodo montarMissaoDeJson para popular todas as missoes de um cJSON
/// </summary>
/// <param name="missaoAnterior">A missão que foi gerada antes da atual. Caso não tenha informa NULL</param>
/// <param name="missoaJson">cJSON de onde começará a buscar as missoes</param>
/// <param name="cenarioInicial">Objeto de cenarioInicial para consultar cenarioItem do passo.</param>
/// <returns>Retorna o primerio struct mapeada de Missao</returns>
Missao* mapearMissoesDeJson(Missao* missaoAnterior, cJSON* missoaJson, CenarioItem* cenarioInicial);
/// <summary>
/// Destri a missão e seus nós filhos
/// </summary>
/// <param name="missao">Inicio da destruição</param>
void destruirMissoes(Missao* missao);
/// <summary>
/// Gera uma struct de PassoMissao populado com os dados obtido no parametro jsonPassoMissao
/// </summary>
/// <param name="passoaMissoaAnterior">O passoMissao que foi gerada antes da atual. Caso não tenha informa NULL</param>
/// <param name="jsonPassoMissao">Struct cJSON com as informações passo que deseja.</param>
/// <param name="cenarioInicial">Objeto de cenarioInicial para consultar cenarioItem do passo.</param>
/// <returns>Objeto de passo mapedo apartir do parametro cJSON</returns>
PassoMissao* montarPassoMissaoDeCJson(PassoMissao* passoaMissoaAnterior, cJSON* jsonPassoMissao, CenarioItem* cenarioInicial);
/// <summary>
/// Função recursiva que utiliza o metodo montarPassoMissaoDeCJson para popular todos os passos de uma missão de um cJSON
/// </summary>
/// <param name="noAnterior">O passo que foi gerado antes da atual. Caso não tenha informo NULL</param>
/// <param name="passoJson">cJSON de onde começará a buscar os passos</param>
/// <param name="cenarioInicial">Objeto de cenarioInicial para consultar cenarioItem do passo.</param>
/// <returns>Retorna o primerio struct mapeada de PassoMissao</returns>
PassoMissao* mapearPassosMissaoDeJson(PassoMissao* noAnterior, cJSON* passoJson, CenarioItem* cenarioInicial);
/// <summary>
/// Destroi um passo e seus nós filhos
/// </summary>
/// <param name="passoMissao">Inicio da destruição</param>
void destruirPassosMissao(PassoMissao * passoMissao);
/// <summary>
/// Coleta a posição em que as misturas poderá ser realizada
/// </summary>
/// <param name="posicaoMisturaCJson">cJSON base para a coleta das indormações da posição</param>
/// <returns>Posição em que as misturas serão realizadas</returns>
Posicao* mapearPosicaoMistura(cJSON* posicaoMisturaCJson);
#endif // !Cabecalho_Missao