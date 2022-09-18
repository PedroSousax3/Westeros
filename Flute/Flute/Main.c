#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>

bool rodando;
int larguraTela = 600;
int alturaTela = 600;

int tamahoPassoPersonagem = 5;
int tamanhoPersonagemX = 20;
int tamanhoPersonagemY = 20;
float cameraPosition[2] = { 0 , 0 };

ALLEGRO_DISPLAY* display = NULL;;
ALLEGRO_EVENT_QUEUE* eventos = NULL;
ALLEGRO_BITMAP* personagem = NULL;
ALLEGRO_BITMAP* background = NULL;
ALLEGRO_TRANSFORM camera;

void configurarTela(void);
void registrarEventos(void);
void gerenciarPosicaoPersonagem(ALLEGRO_EVENT* evento, int* posicao_x, int* posicao_y);
void moverPersonagem(int posicaoX, int posicaoY);
void cameraUpdate(float* cameraPosition, int posicaoX, int posicaoY, int tamanhoPersonagemX, int tamanhoPersonagemY);

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

	al_init();
	al_install_keyboard();
	al_install_mouse();
	al_init_primitives_addon();
	al_init_image_addon();

	background = al_load_bitmap("BG-0001.png");
	personagem = al_load_bitmap("Sprite-0001.png");

	configurarTela();

	if (!display)
		return -1;

	moverPersonagem(posicao_x, posicao_y);
	al_flip_display();
	

	while (rodando)
	{
		ALLEGRO_EVENT evento;
		al_wait_for_event(eventos, &evento);

		gerenciarPosicaoPersonagem(&evento, &posicao_x, &posicao_y);

		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_draw_bitmap(background, 0, 0, 0);
		
	}

	al_destroy_display(display);
	al_destroy_event_queue(eventos);
	al_destroy_bitmap(personagem);
	al_destroy_bitmap(background);

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
		case ALLEGRO_KEY_W:
			chaves[CIMA] = true;
			break;
		case ALLEGRO_KEY_S:
			chaves[BAIXO] = true;
			break;
		case ALLEGRO_KEY_D:
			chaves[DIREITA] = true;
			break;
		case ALLEGRO_KEY_A:
			chaves[ESQUERDA] = true;
			break;
		}
	}
	else if (event.type == ALLEGRO_EVENT_KEY_UP) //Sai da tecla
	{
		switch (event.keyboard.keycode)
		{
		case ALLEGRO_KEY_W:
			chaves[CIMA] = false;
			break;
		case ALLEGRO_KEY_S:
			chaves[BAIXO] = false;
			break;
		case ALLEGRO_KEY_D:
			chaves[DIREITA] = false;
			break;
		case ALLEGRO_KEY_A:
			chaves[ESQUERDA] = false;
			break;
		}
	}
	else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		rodando = false;

	*posicao_y -= chaves[CIMA] ? tamahoPassoPersonagem : 0;
	*posicao_y += chaves[BAIXO] ? tamahoPassoPersonagem : 0;
	*posicao_x -= chaves[ESQUERDA] ? tamahoPassoPersonagem : 0;
	*posicao_x += chaves[DIREITA] ? tamahoPassoPersonagem : 0;

	moverPersonagem(*posicao_x, *posicao_y);
	cameraUpdate(cameraPosition, *posicao_x, *posicao_y, tamanhoPersonagemX, tamanhoPersonagemY);

	al_identity_transform(&camera);
	al_translate_transform(&camera, -cameraPosition[0], -cameraPosition[1]);
	al_use_transform(&camera);
}

void moverPersonagem(int posicaoX, int posicaoY) {
	al_draw_bitmap(personagem, posicaoX + tamanhoPersonagemX, posicaoY + tamanhoPersonagemY, NULL);
}

void cameraUpdate(float* cameraPosition, int posicaoX, int posicaoY, int tamanhoPersonagemX, int tamanhoPersonagemY)
{
	cameraPosition[0] = -(larguraTela / 2) + (posicaoX + tamanhoPersonagemX / 2);
	cameraPosition[1] = -(alturaTela / 2) + (posicaoY + tamanhoPersonagemY / 2);

	if (cameraPosition[0] < 0)
		cameraPosition[0] = 0;
	if (cameraPosition[1] < 0)
		cameraPosition[1] = 0;

}
