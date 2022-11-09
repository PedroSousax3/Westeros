#include <string.h>
#include <stdio.h>
#include <allegro5/allegro_image.h>
#include <allegro5/bitmap_io.h>

#include "../libs/cJSON/cJSON.h"
#include "CenarioItem.h"
#include "Utils/ManipularJson.h"
#include "../Cabecalho/Utils/Imagem.h"

cJSON* obterCJsonCenario(void);
CenarioItem* montarCenarioItemCJson(CenarioItem* noAnterior, cJSON* cenarioItemJson);
CenarioItem* mapearCenariosItemCJson(CenarioItem* noAnterior, cJSON* cenarioItemJson);
void destruirCenarioItens(CenarioItem* cenarioItem);
CenarioItem* buscarCenarioItem(CenarioItem* baseBusca, int codigoCenarioItem);
ElementoCenario* mapearElemetosCenarioJson(ElementoCenario* noAnterior, CenarioItem* cenarioItem, cJSON* elementoCenarioJson);
ElementoCenario* mapaearElementosCenarios(ElementoCenario* noAnterior, CenarioItem* cenarioItem, cJSON* elemtoCenarioJson);
void destruirElementosCenario(ElementoCenario* elementoCenario);
void desenharElementosCenario(ElementoCenario elementoCenario);
void desenharCenarioItens(CenarioItem* cenarioItenInicial);
bool colediuComElementoCenario(ElementoCenario* elementoCenario, Posicao posicaoComparacao, bool useRelative);
bool colediuComCenario(CenarioItem* cenarioItenInicial, Posicao posicaoComparacao, bool useRelative);
ElementoCenario* buscarElementoCenarioPorPosicao(ElementoCenario* elementoCenario, Posicao posicao, bool useRelative);
ElementoCenario* obterElementoCenarioEmPosicao(CenarioItem* cenarioItemInicial, Posicao posicao, bool useRelative);