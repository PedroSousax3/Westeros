#ifndef Cabecalho_Pagina
#define Cabecalho_Pagina

#include <stdbool.h>
#include <allegro5/display.h>

#include "Posicao.h"
#include "Personagem.h"

typedef struct Pagina {
	char nome[50];
	/*float largura;
	float altura;*/

	bool aberta;

	ALLEGRO_BITMAP * background;
	ALLEGRO_DISPLAY * display;
	ALLEGRO_EVENT_QUEUE * eventos;
	Posicao posicao;

	Personagem * personagemPrincipal;
} Pagina;

Pagina iniciarPagina(void);
void exibirPagina(Pagina* pagina);
void ocultarPagina(Pagina* pagina, Pagina* paginaExibir);

#endif // !Cabecalho_Pagina