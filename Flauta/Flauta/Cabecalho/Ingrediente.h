#ifndef Cabecalho_Ingrediente
#define Cabecalho_Ingrediente
#include "CenarioItem.h"
#include "Missao.h"

typedef struct Ingrediente Ingrediente;
struct Ingrediente {
	int indice;

	//Missao* missao;
	CenarioItem* elementoCenario;

	Ingrediente* proximo;
	Ingrediente* anterior;

	int* count;
};

void destruirIngredientes(Ingrediente* ingredienteInical);
#endif // !Cabecalho_Ingrediente

