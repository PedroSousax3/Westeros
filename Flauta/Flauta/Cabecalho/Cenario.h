#include "../libs/cJSON/cJSON.h"
#include "../Cabecalho/CenarioItem.h"
#include <string.h>
#include <stdio.h>
#include <allegro5/allegro_image.h>

cJSON* lerJson(char* json);
cJSON* buscarItemObject(cJSON* baseBusca, char* item);
void obteItemCenarioJson(cJSON* cJSON);
CenarioItem * mapearCenario(cJSON* itensV);
void destruirCenarioItem(CenarioItem * inicioDestruicao);
cJSON* obterDados(void);