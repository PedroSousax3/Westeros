#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

bool rodando;
int larguraTela;
int alturaTela;

int tamahoPassoPersonagem = 5;
int tamanhoPersonagemX = 20;
int tamanhoPersonagemY = 20;

ALLEGRO_DISPLAY* display = NULL;;
ALLEGRO_EVENT_QUEUE* eventos = NULL;

void configurarTela(void);
void registrarEventos(void);
void gerenciarPosicaoPersonagem(ALLEGRO_EVENT* evento, int* posicao_x, int* posicao_y);
void moverPersonagem(int posicaoX, int posicaoY);

typedef struct {
	bool cima;
	bool baixo;
	bool direita;
	bool esquerda;

	int posicaoX;
	int posicaoY;

} Movimento;


enum KEYS {
	CIMA,
	BAIXO,
	ESQUERDA,
	DIREITA
};
bool chaves[4] = { false, false, false, false };


int main(void) {
	if (!al_init())
		return -1;

	int posicao_x = larguraTela / 2;
	int posicao_y = alturaTela / 2;

	Movimento movimento;
	movimento.cima = movimento.baixo = movimento.esquerda = movimento.direita = false;
	movimento.posicaoX = movimento.posicaoY = 0;

	al_install_keyboard();
	al_install_mouse();
	al_init_primitives_addon();

	configurarTela();

	if (!display)
		return -1;

	moverPersonagem(posicao_x, posicao_y);
	al_flip_display();
	al_clear_to_color(al_map_rgb(0, 0, 0));

	while (rodando)
	{
		ALLEGRO_EVENT evento;
		al_wait_for_event(eventos, &evento);

		gerenciarPosicaoPersonagem(&evento, &posicao_x, &posicao_y);

		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
	}

	al_destroy_display(display);
	al_destroy_event_queue(eventos);

	return 0;
}

void configurarTela(void) {
	rodando = true;
	larguraTela = 600;
	alturaTela = 600;

	display = al_create_display(larguraTela, alturaTela); //Cria a tela do programa
	registrarEventos();
}

void registrarEventos(void) {
	eventos = al_create_event_queue();

	al_register_event_source(eventos, al_get_keyboard_event_source());
	al_register_event_source(eventos, al_get_display_event_source(display));
}

void gerenciarPosicaoPersonagem(ALLEGRO_EVENT* evento, int* posicao_x, int* posicao_y) {
	ALLEGRO_EVENT event = *evento;
	if (event.type == ALLEGRO_EVENT_KEY_DOWN) //Entra na tecla
	{
		switch (event.keyboard.keycode)
		{
		case ALLEGRO_KEY_UP:
			chaves[CIMA] = true;
			break;
		case ALLEGRO_KEY_DOWN:
			chaves[BAIXO] = true;
			break;
		case ALLEGRO_KEY_RIGHT:
			chaves[DIREITA] = true;
			break;
		case ALLEGRO_KEY_LEFT:
			chaves[ESQUERDA] = true;
			break;
		}
	}
	else if (event.type == ALLEGRO_EVENT_KEY_UP) //Sai da tecla
	{
		switch (event.keyboard.keycode)
		{
		case ALLEGRO_KEY_UP:
			chaves[CIMA] = false;
			break;
		case ALLEGRO_KEY_DOWN:
			chaves[BAIXO] = false;
			break;
		case ALLEGRO_KEY_RIGHT:
			chaves[DIREITA] = false;
			break;
		case ALLEGRO_KEY_LEFT:
			chaves[ESQUERDA] = false;
			break;
		}
		al_clear_to_color(al_map_rgb(0, 0, 0));
	}
	else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		rodando = false;

	*posicao_y -= chaves[CIMA] ? tamahoPassoPersonagem : 0;
	*posicao_y += chaves[BAIXO] ? tamahoPassoPersonagem : 0;
	*posicao_x -= chaves[ESQUERDA] ? tamahoPassoPersonagem : 0;
	*posicao_x += chaves[DIREITA] ? tamahoPassoPersonagem : 0;

	moverPersonagem(*posicao_x, *posicao_y);
}

void moverPersonagem(int posicaoX, int posicaoY) {
	al_draw_filled_rectangle(posicaoX, posicaoY, posicaoX + tamanhoPersonagemX, posicaoY + tamanhoPersonagemY, al_map_rgb(255, 0, 255));
}