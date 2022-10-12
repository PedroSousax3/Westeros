﻿//Libs externas
#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <stdbool.h>

//Importações
#include "Cabecalho/Posicao.h"
#include "Cabecalho/Movimento.h"
#include "Cabecalho/Personagem.h"

bool rodando;
int larguraTela;
int alturaTela;
const int fps = 60;

Personagem * personagemPrincipal;
Posicao posicoes[1];

ALLEGRO_DISPLAY* display = NULL;
ALLEGRO_EVENT_QUEUE* eventos = NULL;
ALLEGRO_BITMAP* background = NULL;
ALLEGRO_TRANSFORM camera;
ALLEGRO_FONT * fonte = NULL;
ALLEGRO_KEYBOARD_STATE keyState;
ALLEGRO_TIMER * tempoRenderizacao = NULL;
//
float cameraPosition[2] = { 0 , 0 };
//
void configurarPersonagemPrincipal(void);
void configuracaoInicial(void);
void registrarEventos(void);
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

	desenharPersonagem(personagemPrincipal);
	al_start_timer(tempoRenderizacao);
	background = al_load_bitmap("Assets/Imagens/BG-0001.png");
	al_flip_display(); 
	
	while (rodando) {
		ALLEGRO_EVENT evento;
		al_wait_for_event(eventos, &evento);

		al_flip_display();
		al_draw_bitmap(background, 0, 0, 0);
		gerenciarPosicaoPersonagem(&evento, personagemPrincipal->movimento);
	}

	al_destroy_font(fonte);
	al_destroy_display(display);
	al_destroy_event_queue(eventos);
	al_destroy_bitmap(personagemPrincipal->imagem);
	al_destroy_bitmap(background);
	return 0;
}

void configurarPersonagemPrincipal(void) {
	//Posicao Inicial do personagem

	Personagem * personagem = iniciarPersonagem();
	Movimento * movimentoPersonagem = iniciarMovimento();
	Posicao * posicaoPersonagem = iniciarPosicao();

	personagem->idade = 14;
	personagem->imagem = al_load_bitmap("Assets/Imagens/Sprite-0002.png");

	posicaoPersonagem->velocidadeX = 3;
	posicaoPersonagem->velocidadeY = 3;
	posicaoPersonagem->posicaoX = 20;
	posicaoPersonagem->posicaoY = 20;
	posicaoPersonagem->tamanhoX = al_get_bitmap_width(personagem->imagem) / 4;
	posicaoPersonagem->tamanhoY = al_get_bitmap_height(personagem->imagem) / 4;
	movimentoPersonagem->posicao = posicaoPersonagem;
	personagem->movimento = movimentoPersonagem;
	personagemPrincipal = personagem;
}

void configuracaoInicial(void) {
	rodando = true;
	larguraTela = 600;
	alturaTela = 600;
	

	display = al_create_display(larguraTela, alturaTela); //Cria a tela do programa
	fonte = al_load_font("arial_narrow_7.ttf", 12, 0);

	registrarEventos();
	configurarPersonagemPrincipal();
}

void registrarEventos(void) {
	tempoRenderizacao = al_create_timer(1.0 / fps);//60 quadros por segundo
	eventos = al_create_event_queue();//Cria uma lista de eventos

	al_register_event_source(eventos, al_get_keyboard_event_source());
	al_register_event_source(eventos, al_get_timer_event_source(tempoRenderizacao));
	al_register_event_source(eventos, al_get_display_event_source(display));
}

void gerenciarPosicaoPersonagem(ALLEGRO_EVENT* evento, Movimento * movimento) {
	ALLEGRO_EVENT event = *evento;

	if (event.type == ALLEGRO_EVENT_KEY_DOWN) //Entra na tecla
	{
		switch (event.keyboard.keycode)
		{
			case ALLEGRO_KEY_DOWN:
				movimento->direcaoY = DIRECAOYBAIXO;
				personagemPrincipal->imagemX = 0;
				personagemPrincipal->imagemY = 0 * al_get_bitmap_height(personagemPrincipal->imagem) / 4;
				break;
			case ALLEGRO_KEY_LEFT:
				movimento->direcaoX = DIRECAOXESQUERDA;
				personagemPrincipal->imagemX = 0;
				personagemPrincipal->imagemY = 1 * al_get_bitmap_height(personagemPrincipal->imagem) / 4;
				break;
			case ALLEGRO_KEY_RIGHT:
				movimento->direcaoX = DIRECAOXDIREITA;
				personagemPrincipal->imagemX = 0;
				personagemPrincipal->imagemY = 2 * al_get_bitmap_height(personagemPrincipal->imagem) / 4;
				break;
			case ALLEGRO_KEY_UP:
				movimento->direcaoY = DIRECAOYCIMA;
				personagemPrincipal->imagemX = 0;
				personagemPrincipal->imagemY = 3 * al_get_bitmap_height(personagemPrincipal->imagem) / 4;
				break;
		}
	}
	//else if (event.type == ALLEGRO_EVENT_KEY_UP) //Entra na tecla
	//{
	//	switch (event.keyboard.keycode)
	//	{
	//		case ALLEGRO_KEY_UP:
	//			movimento->direcaoY = DIRECAOYNENHUM;
	//			break;
	//		case ALLEGRO_KEY_DOWN:
	//			movimento->direcaoY = DIRECAOYNENHUM;
	//			break;
	//		case ALLEGRO_KEY_RIGHT:
	//			movimento->direcaoX = DIRECAOXNENHUM;
	//			break;
	//		case ALLEGRO_KEY_LEFT:
	//			movimento->direcaoX = DIRECAOXNENHUM;
	//			break;
	//	}
	//}
	//else if (event.type == ALLEGRO_EVENT_TIMER)
	//{
	//	switch (movimento->direcaoY)
	//	{
	//		case DIRECAOYCIMA:
	//			movimento->posicao.posicaoY -= movimento->posicao.velocidadeX;
	//			break;
	//		case DIRECAOYBAIXO:
	//			movimento->posicao.posicaoY += movimento->posicao.velocidadeX;
	//			break;
	//		default :
	//			movimento->direcaoY = DIRECAOYNENHUM;
	//			break;
	//	}
	//	switch (movimento->direcaoX)
	//	{
	//		case DIRECAOXESQUERDA:
	//			movimento->posicao.posicaoX -= movimento->posicao.velocidadeX;
	//			break;
	//		case DIRECAOXDIREITA:
	//			movimento->posicao.posicaoX += movimento->posicao.velocidadeX;
	//			break;
	//		default:
	//			movimento->direcaoX = DIRECAOXNENHUM;
	//			break;
	//	}
	//}
	//else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
	//	rodando = false;


	//if (emMovimento(&personagemPrincipal.movimento))
	//	if (personagemPrincipal.imagemX >= al_get_bitmap_width(personagemPrincipal.imagem))
	//		personagemPrincipal.imagemX = 0;
	//	else
	//		personagemPrincipal.imagemX += al_get_bitmap_width(personagemPrincipal.imagem) / 4;
	//else
	//	personagemPrincipal.imagemX = 0;

	//Posicao posicaoItem;
	//posicaoItem.posicaoX = 100;
	//posicaoItem.posicaoY = 100;
	//posicaoItem.tamanhoX = posicaoItem.tamanhoY = 300;
	//posicoes[0] = posicaoItem;

	//cameraUpdate(cameraPosition, personagemPrincipal.movimento.posicao);
	//al_identity_transform(&camera);
	//al_translate_transform(&camera, -cameraPosition[0], -cameraPosition[1]);
	//al_use_transform(&camera);
	//desenharPersonagem(personagemPrincipal);

	//if (!colidiu(personagemPrincipal.movimento.posicao, posicoes, sizeof(posicoes) / sizeof(Posicao)))
	//	desenhaQuadrado(posicaoItem);
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

void desenhaQuadrado(Posicao posicao) {
	al_draw_filled_rectangle(
		posicao.posicaoX,
		posicao.posicaoY,
		posicao.posicaoX + posicao.tamanhoX,
		posicao.posicaoY + posicao.tamanhoY,
		al_map_rgb(255, 255, 255)
	);
}