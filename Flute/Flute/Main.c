#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

typedef struct {
	int posicaoX;
	int posicaoY;

	int tamanho;
} Posicao;

typedef struct {
	bool cima;
	bool baixo;
	bool direita;
	bool esquerda;

	Posicao posicao;
} Movimento;

typedef struct {
	char nome[30];
	char sobreNome[70];
	int idade;

	Movimento movimento;

} PersonagemPrincipal;

void configurarPersonagemPrincipal(void);
void configuracaoInicial(void);
void registrarEventos(void);
void desenhaQuadrado(Posicao posicao);
void gerenciarPosicaoPersonagem(ALLEGRO_EVENT* evento, Movimento* movimento);
void moverPersonagem(Posicao posicao);

bool rodando;
int larguraTela;
int alturaTela;

PersonagemPrincipal personagemPrincipal;
Posicao posicoes[2];

ALLEGRO_DISPLAY* display = NULL;
ALLEGRO_EVENT_QUEUE* eventos = NULL;

int main(void) {
	if (!al_init())
		return -1;

	al_install_keyboard();
	al_install_mouse();
	al_init_primitives_addon();

	configuracaoInicial();

	if (!display)
		return -1;

	moverPersonagem(personagemPrincipal.movimento.posicao);
	al_flip_display();

	while (rodando)
	{
		ALLEGRO_EVENT evento;
		al_wait_for_event(eventos, &evento);

		al_clear_to_color(al_map_rgb(0, 0, 0));
		gerenciarPosicaoPersonagem(&evento, &personagemPrincipal.movimento);
		al_flip_display();
	}

	al_destroy_display(display);
	al_destroy_event_queue(eventos);

	return 0;
}

void configurarPersonagemPrincipal(void) {
	personagemPrincipal.idade = 14;

	//Posicao Inicial do personagem
	personagemPrincipal.movimento.posicao.tamanho = 5;
	personagemPrincipal.movimento.posicao.posicaoX = 10;
	personagemPrincipal.movimento.posicao.posicaoY = 10;
}

void configuracaoInicial(void) {
	rodando = true;
	larguraTela = 600;
	alturaTela = 600;

	configurarPersonagemPrincipal();

	display = al_create_display(larguraTela, alturaTela); //Cria a tela do programa
	registrarEventos();
}

void registrarEventos(void) {
	eventos = al_create_event_queue();

	al_register_event_source(eventos, al_get_keyboard_event_source());
	al_register_event_source(eventos, al_get_display_event_source(display));
}

bool colisaoPersonagem() {
	int qtdItens = sizeof(posicoes) / sizeof(Posicao);
	for (int i = 0; i < qtdItens; i++) {
		int x = personagemPrincipal.movimento.posicao.posicaoX;
		int y = personagemPrincipal.movimento.posicao.posicaoY;
		int tamanho = personagemPrincipal.movimento.posicao.tamanho;

		if (
			(posicoes[i].posicaoX <= x && (posicoes[i].posicaoX + posicoes[i].tamanho) >= (x + tamanho))
			&& (posicoes[i].posicaoY <= y && (posicoes[i].posicaoY + posicoes[i].tamanho) >= (y + tamanho))
		)
			return true;
	}

	return false;
}

void gerenciarPosicaoPersonagem(ALLEGRO_EVENT* evento, Movimento * movimento) {
	ALLEGRO_EVENT event = *evento;

	if (event.type == ALLEGRO_EVENT_KEY_DOWN) //Entra na tecla
	{
		switch (event.keyboard.keycode)
		{
			case ALLEGRO_KEY_UP:
				movimento->cima = true;
				break;
			case ALLEGRO_KEY_DOWN:
				movimento->baixo = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				movimento->direita = true;
				break;
			case ALLEGRO_KEY_LEFT:
				movimento->esquerda = true;
				break;
		}
	}
	else if (event.type == ALLEGRO_EVENT_KEY_UP) //Sai da tecla
	{
		switch (event.keyboard.keycode)
		{
			case ALLEGRO_KEY_UP:
				movimento->cima = false;
				break;
			case ALLEGRO_KEY_DOWN:
				movimento->baixo = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				movimento->direita = false;
				break;
			case ALLEGRO_KEY_LEFT:
				movimento->esquerda = false;
				break;
		}
	}
	else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		rodando = false;

	int posicaoAtualX = movimento->posicao.posicaoX;
	int posicaoAtualY = movimento->posicao.posicaoY;

	movimento->posicao.posicaoX += movimento->direita * movimento->posicao.tamanho;
	movimento->posicao.posicaoX -= movimento->esquerda * movimento->posicao.tamanho;
	movimento->posicao.posicaoY += movimento->baixo * movimento->posicao.tamanho;
	movimento->posicao.posicaoY -= movimento->cima * movimento->posicao.tamanho;

	moverPersonagem(movimento->posicao);
	Posicao posicaoItem;
	posicaoItem.posicaoX = 100;
	posicaoItem.posicaoY = 100;
	posicaoItem.tamanho = 50;
	posicoes[0] = posicaoItem;
	posicoes[1] = posicaoItem;
	if (!colisaoPersonagem())
		desenhaQuadrado(posicaoItem);
}

void moverPersonagem(Posicao posicao) {
	al_draw_filled_circle(
		posicao.posicaoX,
		posicao.posicaoY,
		posicao.tamanho,
		al_map_rgb(255, 0, 255)
	);
}

void desenhaQuadrado(Posicao posicao) {
	al_draw_filled_rectangle(
		posicao.posicaoX,
		posicao.posicaoY,
		posicao.posicaoX + posicao.tamanho,
		posicao.posicaoY + posicao.tamanho,
		al_map_rgb(255, 0, 255)
	);
}