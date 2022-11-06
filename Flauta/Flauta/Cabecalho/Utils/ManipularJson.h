#ifndef Cabecalho_Utils_ManipularJson
#define Cabecalho_Utils_ManipularJson

#include "../../libs/cJSON/cJSON.h"

cJSON * obterCJson(char * caminho);
cJSON * bucarItemCJson(cJSON * baseBusca, char * item);

#endif // !Cabecalho_Utils_ManipularJson
