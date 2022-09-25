#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>

typedef struct {
	int posicaoX;
	int posicaoY;

	int tamanhoX;
	int tamanhoY;

	int imagemX;
	int imagemY;
	int dir;

	int velocidadeX;
	int velocidadeY;
} Posicao;

typedef struct {
	bool cima;
	bool baixo;
	bool direita;
	bool esquerda;
	bool ativo;

	Posicao posicao;
} Movimento;

typedef struct {
	char nome[30];
	char sobreNome[70];
	int idade;

	Movimento movimento;

	ALLEGRO_BITMAP * imagem;

} PersonagemPrincipal;

bool rodando;
int larguraTela;
int alturaTela;
enum { DOWN, LEFT, RIGHT, UP };

PersonagemPrincipal personagemPrincipal;
Posicao posicoes[1];

ALLEGRO_DISPLAY* display = NULL;
ALLEGRO_EVENT_QUEUE* eventos = NULL;
ALLEGRO_BITMAP* background = NULL;
ALLEGRO_TRANSFORM camera;
ALLEGRO_FONT * fonte = NULL;
ALLEGRO_KEYBOARD_STATE keyState;

float cameraPosition[2] = { 0 , 0 };

void configurarPersonagemPrincipal(void);
void configuracaoInicial(void);
void registrarEventos(void);
void moverPersonagem(Posicao posicao);
void desenhaQuadrado(Posicao posicao);
void gerenciarPosicaoPersonagem(ALLEGRO_EVENT* evento, Movimento* movimento);
void cameraUpdate(float* cameraPosition, Posicao posicaoBase);

int main(void) {
	if (!al_init())
		return -1;
	
	al_install_keyboard();
	al_install_mouse();
	al_init_primitives_addon();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();

	configuracaoInicial();
	if (!display)
		return -1;

	moverPersonagem(personagemPrincipal.movimento.posicao);
	background = al_load_bitmap("BG-0001.png");
	al_flip_display(); 

	while (rodando) {
		ALLEGRO_EVENT evento;
		al_wait_for_event(eventos, &evento);

		gerenciarPosicaoPersonagem(&evento, &personagemPrincipal.movimento);

		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_draw_bitmap(background, 0, 0, 0);
	}

	al_destroy_font(fonte);
	al_destroy_display(display);
	al_destroy_event_queue(eventos);
	al_destroy_bitmap(personagemPrincipal.imagem);
	al_destroy_bitmap(background);
	return 0;
}

void configurarPersonagemPrincipal(void) {
	personagemPrincipal.idade = 14;
	//Posicao Inicial do personagem
	personagemPrincipal.movimento.posicao.tamanhoX = personagemPrincipal.movimento.posicao.tamanhoY = 31;
	personagemPrincipal.movimento.posicao.velocidadeX = personagemPrincipal.movimento.posicao.velocidadeY = 10;
	personagemPrincipal.movimento.posicao.posicaoX = 20;
	personagemPrincipal.movimento.posicao.posicaoY = 20;

	personagemPrincipal.imagem = al_load_bitmap("Sprite-0002.png");
}

void configuracaoInicial(void) {
	rodando = true;
	larguraTela = 600;
	alturaTela = 600;

	configurarPersonagemPrincipal();
	display = al_create_display(larguraTela, alturaTela); //Cria a tela do programa
	fonte = al_load_font("arial_narrow_7.ttf", 12, 0);

	registrarEventos();
}

void registrarEventos(void) {
	eventos = al_create_event_queue();

	al_register_event_source(eventos, al_get_keyboard_event_source());
	al_register_event_source(eventos, al_get_display_event_source(display));
}

bool colisaoPersonagem() {
	int qtdItens = sizeof(posicoes) / sizeof(Posicao);

	Posicao posicaoPersonagem = personagemPrincipal.movimento.posicao;
	int x = posicaoPersonagem.posicaoX;
	int y = posicaoPersonagem.posicaoY;
	int xM = personagemPrincipal.movimento.posicao.posicaoX + posicaoPersonagem.tamanhoX;
	int yM = personagemPrincipal.movimento.posicao.posicaoY + posicaoPersonagem.tamanhoY;
	
	for (int i = 0; i < qtdItens; i++)
		if (
			xM >= posicoes[i].posicaoX && x <= (posicoes[i].posicaoX + posicoes[i].tamanhoX)
			&& yM >= posicoes[i].posicaoY && y <= (posicoes[i].posicaoY + posicoes[i].tamanhoY)
		)
			return true;

	return false;
}


//void moverPersonagem(int posicaoX, int posicaoY) {
//	al_draw_bitmap(personagem, posicaoX + tamanhoPersonagemX, posicaoY + tamanhoPersonagemY, NULL);
//}

void gerenciarPosicaoPersonagem(ALLEGRO_EVENT* evento, Movimento* movimento) {
	ALLEGRO_EVENT event = *evento;

	if (event.type == ALLEGRO_EVENT_KEY_DOWN) //Entra na tecla
	{
		switch (event.keyboard.keycode)
		{
		case ALLEGRO_KEY_UP:
			movimento->cima = true;
			movimento->ativo = true;
			movimento->posicao.dir = UP;
			break;
		case ALLEGRO_KEY_DOWN:
			movimento->baixo = true;
			movimento->ativo = true;
			movimento->posicao.dir = DOWN;
			break;
		case ALLEGRO_KEY_RIGHT:
			movimento->direita = true;
			movimento->ativo = true;
			movimento->posicao.dir = RIGHT;
			break;
		case ALLEGRO_KEY_LEFT:
			movimento->esquerda = true;
			movimento->ativo = true;
			movimento->posicao.dir = LEFT;
			break;
		case ALLEGRO_KEY_W:
			movimento->cima = true;
			movimento->ativo = true;
			movimento->posicao.dir = UP;
			break;
		case ALLEGRO_KEY_S:
			movimento->baixo = true;
			movimento->ativo = true;
			movimento->posicao.dir = DOWN;
			break;
		case ALLEGRO_KEY_D:
			movimento->direita = true;
			movimento->ativo = true;
			movimento->posicao.dir = RIGHT;
			break;
		case ALLEGRO_KEY_A:
			movimento->esquerda = true;
			movimento->ativo = true;
			movimento->posicao.dir = LEFT;
			break;
		}
	}
	else if (event.type == ALLEGRO_EVENT_KEY_UP) //Sai da tecla
	{
		switch (event.keyboard.keycode)
		{
		case ALLEGRO_KEY_UP:
			movimento->cima = false;
			movimento->ativo = false;
			/*movimento->posicao.dir = UP;*/
			break;
		case ALLEGRO_KEY_DOWN:
			movimento->baixo = false;
			movimento->ativo = false;
			/*movimento->posicao.dir = DOWN;*/
			break;
		case ALLEGRO_KEY_RIGHT:
			movimento->direita = false;
			movimento->ativo = false;
			/*movimento->posicao.dir = RIGHT;*/
			break;
		case ALLEGRO_KEY_LEFT:
			movimento->esquerda = false;
			movimento->ativo = false;
			/*movimento->posicao.dir = LEFT;*/
			break;
		case ALLEGRO_KEY_W:
			movimento->cima = false;
			movimento->ativo = false;
			/*movimento->posicao.dir = UP;*/
			break;
		case ALLEGRO_KEY_S:
			movimento->baixo = false;
			movimento->ativo = false;
			/*movimento->posicao.dir = DOWN;*/
			break;
		case ALLEGRO_KEY_D:
			movimento->direita = false;
			movimento->ativo = false;
			/*movimento->posicao.dir = RIGHT;*/
			break;
		case ALLEGRO_KEY_A:
			movimento->esquerda = false;
			movimento->ativo = false;
			/*movimento->posicao.dir = LEFT;*/
			break;
		}
	}
	if (movimento->ativo) {
		movimento->posicao.imagemX += al_get_bitmap_width(personagemPrincipal.imagem) / 4;
	}
	else {
		movimento->posicao.imagemX = 0;
	}
	if (movimento->posicao.imagemX >= al_get_bitmap_width(personagemPrincipal.imagem)) {
		movimento->posicao.imagemX = 0;
	}

	else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		rodando = false;

	movimento->posicao.posicaoX += movimento->direita * movimento->posicao.velocidadeX;
	movimento->posicao.posicaoX -= movimento->esquerda * movimento->posicao.velocidadeX;
	movimento->posicao.posicaoY += movimento->baixo * movimento->posicao.velocidadeY;
	movimento->posicao.posicaoY -= movimento->cima * movimento->posicao.velocidadeY;

	Posicao posicaoItem;
	posicaoItem.posicaoX = 100;
	posicaoItem.posicaoY = 100;
	posicaoItem.tamanhoX = posicaoItem.tamanhoY = 300;
	posicoes[0] = posicaoItem;

	cameraUpdate(cameraPosition, personagemPrincipal.movimento.posicao);
	al_identity_transform(&camera);
	al_translate_transform(&camera, -cameraPosition[0], -cameraPosition[1]);
	al_use_transform(&camera);
	moverPersonagem(movimento->posicao);

	if (!colisaoPersonagem())
		desenhaQuadrado(posicaoItem);
}

void moverPersonagem(Posicao posicao) {
	al_draw_bitmap_region(personagemPrincipal.imagem, posicao.imagemX, posicao.dir * al_get_bitmap_height(personagemPrincipal.imagem) / 4, al_get_bitmap_width(personagemPrincipal.imagem) / 4, al_get_bitmap_height(personagemPrincipal.imagem) / 4, posicao.posicaoX, posicao.posicaoY, NULL);
	//al_draw_text(fonte, al_map_rgb(255, 255, 255), posicao.posicaoX - (15 + (posicao.tamanhoX / 2)), posicao.posicaoY - 15, ALLEGRO_ALIGN_LEFT, "Nome personagem");
}

void desenhaQuadrado(Posicao posicao) {
	al_draw_filled_rectangle(
		posicao.posicaoX,
		posicao.posicaoY,
		posicao.posicaoX + posicao.tamanhoX,
		posicao.posicaoY + posicao.tamanhoY,
		al_map_rgb(255, 255, 255)
	);
}

void cameraUpdate(float * cameraPosition, Posicao posicaoBase)
{
	cameraPosition[0] = -(larguraTela / 2) + (posicaoBase.posicaoX + posicaoBase.tamanhoX / 2);
	cameraPosition[1] = -(alturaTela / 2) + (posicaoBase.posicaoY + posicaoBase.tamanhoY / 2);

	if (cameraPosition[0] < 0)
		cameraPosition[0] = 0;
	if (cameraPosition[1] < 0)
		cameraPosition[1] = 0;
}