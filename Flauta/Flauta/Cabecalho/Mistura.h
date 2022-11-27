#ifndef Cabecalho_Mistura
#define Cabecalho_Mistura

#include "CenarioItem.h"
#include "Inventario.h"
#include "Ingrediente.h"

typedef struct Mistura {
	struct CenarioItem* produto;
	struct Ingrediente* ingrediente;
} Mistura;

bool misturaPossuiTodosIngredientes(struct Ingrediente* ingrediente, struct Inventario* inventario);
bool possuiIngrediente(struct Ingrediente* ingrediente, struct Inventario* inventario);
CenarioItem* realizarMistura(struct Mistura* mistura, struct Inventario* inventario);
#endif // !Cabecalho_Mistura

