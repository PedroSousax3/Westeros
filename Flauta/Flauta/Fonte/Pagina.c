#include "../Cabecalho/Pagina.h"
#include "allegro5/color.h"
#include <allegro5/allegro_color.h>

Pagina iniciarPagina(void) {
	Pagina pagina = {
		.aberta = false,
		.nome = ""
	};

	return pagina;
}

void exibirPagina(Pagina* pagina) {
	al_set_new_display_flags(ALLEGRO_NOFRAME);
	pagina->display = al_create_display(
		pagina->posicao.tamanhoX,
		pagina->posicao.tamanhoY
	); //Cria a tela do programa
	al_set_target_backbuffer(pagina->display);
	al_set_window_title(pagina->display, "Misturas");
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();

	pagina->aberta = true;
}
void ocultarPagina(Pagina* pagina, Pagina * paginaExibir) {
	pagina->aberta = false;
	al_destroy_display(pagina->display);

	al_set_target_backbuffer(paginaExibir->display);
	paginaExibir->aberta = true;
}