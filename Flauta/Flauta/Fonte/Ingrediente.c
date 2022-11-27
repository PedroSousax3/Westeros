#include "../Cabecalho/Ingrediente.h"

void destruirIngredientes(Ingrediente * ingredienteInical) {
	if (ingredienteInical != NULL) {
		(*ingredienteInical->count)--;

		if (ingredienteInical->proximo != NULL)
			destruirIngredientes(ingredienteInical->proximo);

		if (ingredienteInical->indice == 0)
			free(ingredienteInical->count);

		free(ingredienteInical);
	}
}