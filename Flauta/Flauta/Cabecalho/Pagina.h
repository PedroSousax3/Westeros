#ifndef Cabecalho_Pagina
#define Cabecalho_Pagina

#include <stdbool.h>

typedef struct Pagina {
	char nome[50];
	float largura;
	float altura;
	bool aberta;
} Pagina;

void iniciarPagina(Pagina* pagina);
void exibirPagina(Pagina* pagina);
void ocultarPagina(Pagina* pagina);

#endif // !Cabecalho_Pagina

