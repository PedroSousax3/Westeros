//Libs externas
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
//#include "Cabecalho/Pagina.h"
#include "Utilitario.h"
#include "Cabecalho/Posicao.h"
#include "Cabecalho/Movimento.h"
#include "Cabecalho/Personagem.h"
#include "Cabecalho/Pagina.h"
#include "PaginaCombinacao.h"
#include "Cabecalho/Cenario.h"

const int fps = 60;
int fpsAnimacao = 0;

Pagina paginaPrincipal;
Pagina paginaCombinacao;
Personagem personagemPrincipal;
Posicao posicoes[1];

ALLEGRO_EVENT_QUEUE* eventos = NULL;
ALLEGRO_BITMAP* background = NULL;
ALLEGRO_TRANSFORM camera;
ALLEGRO_FONT *  fonte = NULL;
ALLEGRO_KEYBOARD_STATE keyState;
ALLEGRO_TIMER * tempoRenderizacao = NULL;

float cameraPosition[2] = { 0 , 0 };

Personagem configurarPersonagemPrincipal(void);
void abrirPaginaComposicao();
void configuracaoInicial(void);
void registrarEventos(void);
void gerenciarPosicaoPersonagem(ALLEGRO_EVENT* evento);
void cameraUpdate(float* cameraPosition, Posicao * posicaoBase);


void desenharItensCenario(CenarioItem* cenarioInicial) {
	if (cenarioInicial != NULL) {
		desenhaQuadrado((*cenarioInicial->posicao), al_map_rgb(255, 255, 255));
		desenharItensCenario(cenarioInicial->proximo);
	}
}
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
	personagemPrincipal = configurarPersonagemPrincipal();

	paginaPrincipal.personagemPrincipal = &personagemPrincipal;
	paginaCombinacao.personagemPrincipal = &personagemPrincipal;

	if (!paginaPrincipal.display)
		return -1;

	desenharPersonagem(personagemPrincipal);
	background = al_load_bitmap("BG-0001.png");
	cJSON * jsonCenarioItem = obterDados();
	cJSON* itens = buscarItemObject(jsonCenarioItem->child, "itens");
	CenarioItem * cenarioItemInicial = mapearCenario(itens->child);

	al_start_timer(tempoRenderizacao);
	while (paginaPrincipal.aberta) {
		ALLEGRO_EVENT evento;
		al_wait_for_event(eventos, &evento);

		//Gerenciador de display
		if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
			if (evento.keyboard.keycode == ALLEGRO_KEY_F1) {
				if (paginaCombinacao.aberta)
					ocultarPagina(&paginaCombinacao, &paginaPrincipal);
				else
					abrirPaginaComposicao();
			}
		}

		//Execucao de dislay
		if (paginaCombinacao.aberta)
			executarPaginaCombinacao(&paginaCombinacao, personagemPrincipal.equipamentos, sizeof(personagemPrincipal.equipamentos) / sizeof(Equipamento));
		else if (paginaPrincipal.aberta) {
			gerenciarPosicaoPersonagem(&evento);
			desenharItensCenario(cenarioItemInicial);
		}
	}

	free(itens);
	free(jsonCenarioItem);
	destruirCenarioItem(cenarioItemInicial);
	al_destroy_font(fonte);
	al_destroy_display(paginaPrincipal.display);
	al_destroy_event_queue(eventos);
	al_destroy_bitmap(personagemPrincipal.imagem);
	al_destroy_bitmap(background);
	al_destroy_timer(tempoRenderizacao);

	return 0;
}

Personagem configurarPersonagemPrincipal(void) {
	//Posicao Inicial do personagem
	Personagem personagem = {
		.nome = NULL,
		.sobreNome = NULL,
		.idade = 14,
		.imagemX = 0,
		.imagemY = 0,
		.imagem = al_load_bitmap("Sprite-0002.png")
	};

	Movimento movimento = {
		.direcaoX = DIRECAOXNENHUM,
		.direcaoY = DIRECAOYNENHUM,
		.direcao = 0
	};
	Posicao posicao = {
		.posicaoX = 0,
		.posicaoY = 0,
		.tamanhoX = 0,
		.tamanhoY = 0,
		.velocidadeX = 0,
		.velocidadeY = 0
	};
	posicao.velocidadeX = 3;
	posicao.velocidadeY = 3;
	posicao.posicaoX = 20;
	posicao.posicaoY = 20;
	posicao.tamanhoX = al_get_bitmap_width(personagem.imagem) / 4;
	posicao.tamanhoY = al_get_bitmap_height(personagem.imagem) / 4;

	movimento.posicao = posicao;
	personagem.movimento = movimento;

	//Careaga inventario teste
	for (int i = 0; i < 10; i++) {
		Equipamento equipamento = gerarEquipamento(1);
		personagemPrincipal.equipamentos[i] = equipamento;
	}

	return personagem;
}

void configuracaoInicial(void) {
	paginaPrincipal = iniciarPagina();
	paginaPrincipal.aberta = true;
	paginaPrincipal.posicao.tamanhoX = 1200;
	paginaPrincipal.posicao.tamanhoY = 650;
	paginaPrincipal.display = al_create_display(
		paginaPrincipal.posicao.tamanhoX ,
		paginaPrincipal.posicao.tamanhoY
	); //Cria a tela do programa
	

	paginaCombinacao = iniciarPagina();
	fonte = al_load_font("arial_narrow_7.ttf", 12, 0);
		
	registrarEventos();
}

void registrarEventos(void) {
	tempoRenderizacao = al_create_timer(1.0 / fps);//60 quadros por segundo
	eventos = al_create_event_queue();//Cria uma lista de eventos

	al_register_event_source(eventos, al_get_keyboard_event_source());
	al_register_event_source(eventos, al_get_display_event_source(paginaPrincipal.display));
	al_register_event_source(eventos, al_get_timer_event_source(tempoRenderizacao));
}

void abrirPaginaComposicao() {
	paginaCombinacao.posicao.posicaoX = 0;
	paginaCombinacao.posicao.posicaoY = 0;
	paginaCombinacao.posicao.tamanhoX = 500;
	paginaCombinacao.posicao.tamanhoY = 500;
	/*const char * nomePagina[50] = "Misturar elementos";
	strcpy(&paginaCombinacao.nome, nomePagina);*/
	exibirPagina(&paginaCombinacao);
}

void gerenciarPosicaoPersonagem(ALLEGRO_EVENT* evento) {
	ALLEGRO_EVENT event = *evento;

	if (event.type == ALLEGRO_EVENT_KEY_DOWN) //Entra na tecla
		switch (event.keyboard.keycode)
		{
			case ALLEGRO_KEY_DOWN:
				personagemPrincipal.movimento.direcaoY = DIRECAOYBAIXO;
				personagemPrincipal.imagemX = 0;
				personagemPrincipal.imagemY = 0 * al_get_bitmap_height(personagemPrincipal.imagem) / 4;
				break;
			case ALLEGRO_KEY_LEFT:
				personagemPrincipal.movimento.direcaoX = DIRECAOXESQUERDA;
				personagemPrincipal.imagemX = 0;
				personagemPrincipal.imagemY = 1 * al_get_bitmap_height(personagemPrincipal.imagem) / 4;
				break;
			case ALLEGRO_KEY_RIGHT:
				personagemPrincipal.movimento.direcaoX = DIRECAOXDIREITA;
				personagemPrincipal.imagemX = 0;
				personagemPrincipal.imagemY = 2 * al_get_bitmap_height(personagemPrincipal.imagem) / 4;
				break;
			case ALLEGRO_KEY_UP:
				personagemPrincipal.movimento.direcaoY = DIRECAOYCIMA;
				personagemPrincipal.imagemX = 0;
				personagemPrincipal.imagemY = 3 * al_get_bitmap_height(personagemPrincipal.imagem) / 4;
				break;
		}
	else if (event.type == ALLEGRO_EVENT_KEY_UP) //Entra na tecla
		switch (event.keyboard.keycode)
		{
			case ALLEGRO_KEY_UP:
				personagemPrincipal.movimento.direcaoY = DIRECAOYNENHUM;
				break;
			case ALLEGRO_KEY_DOWN:
				personagemPrincipal.movimento.direcaoY = DIRECAOYNENHUM;
				break;
			case ALLEGRO_KEY_RIGHT:
				personagemPrincipal.movimento.direcaoX = DIRECAOXNENHUM;
				break;
			case ALLEGRO_KEY_LEFT:
				personagemPrincipal.movimento.direcaoX = DIRECAOXNENHUM;
				break;
		}
	else if (event.type == ALLEGRO_EVENT_TIMER && al_is_event_queue_empty(eventos))
	{
		switch (personagemPrincipal.movimento.direcaoY)
		{
			case DIRECAOYCIMA:
				personagemPrincipal.movimento.posicao.posicaoY -= personagemPrincipal.movimento.posicao.velocidadeX;
				break;
			case DIRECAOYBAIXO:
				personagemPrincipal.movimento.posicao.posicaoY += personagemPrincipal.movimento.posicao.velocidadeX;
				break;
			default :
				personagemPrincipal.movimento.direcaoY = DIRECAOYNENHUM;
				break;
		}
		switch (personagemPrincipal.movimento.direcaoX)
		{
			case DIRECAOXESQUERDA:
				personagemPrincipal.movimento.posicao.posicaoX -= personagemPrincipal.movimento.posicao.velocidadeX;
				break;
			case DIRECAOXDIREITA:
				personagemPrincipal.movimento.posicao.posicaoX += personagemPrincipal.movimento.posicao.velocidadeX;
				break;
			default:
				personagemPrincipal.movimento.direcaoX = DIRECAOXNENHUM;
				break;
		}

		if (emMovimento(personagemPrincipal.movimento)) {
			if (fpsAnimacao == 10) {
				personagemPrincipal.imagemX += al_get_bitmap_width(personagemPrincipal.imagem) / 4;
				fpsAnimacao = 0;
			}

			if (personagemPrincipal.imagemX >= al_get_bitmap_width(personagemPrincipal.imagem))
				personagemPrincipal.imagemX = 0;

			fpsAnimacao++;
		}
		else
			personagemPrincipal.imagemX = 0;
		
		if (personagemPrincipal.imagemX != 0)
			printf("X: %i\nY: %i\n", personagemPrincipal.movimento.posicao.posicaoX, personagemPrincipal.movimento.posicao.posicaoY);

		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_draw_bitmap(background, 0, 0, 0);
		desenharPersonagem(personagemPrincipal);


		if (!posicaoColidiu(personagemPrincipal.movimento.posicao, posicoes, sizeof(posicoes) / sizeof(Posicao))) {
			Posicao posicaoItem;
			posicaoItem.posicaoX = 100;
			posicaoItem.posicaoY = 100;
			posicaoItem.tamanhoX = posicaoItem.tamanhoY = 300;
			posicoes[0] = posicaoItem;

			desenhaQuadrado(posicaoItem, al_map_rgb(255, 255, 255));
		}

		cameraUpdate(cameraPosition, &personagemPrincipal.movimento.posicao);
		al_identity_transform(&camera);
		al_translate_transform(&camera, -cameraPosition[0], -cameraPosition[1]);
		al_use_transform(&camera);
	}
	else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		paginaPrincipal.aberta = false;
}

void cameraUpdate(float * cameraPosition, Posicao * posicaoBase)
{
	cameraPosition[0] = -(paginaPrincipal.posicao.tamanhoX / 2.0) + (posicaoBase->posicaoX + posicaoBase->tamanhoX / 2.0);
	cameraPosition[1] = -(paginaPrincipal.posicao.tamanhoY / 2.0) + (posicaoBase->posicaoY + posicaoBase->tamanhoY / 2.0);

	if (cameraPosition[0] < 0)
		cameraPosition[0] = 0;
	if (cameraPosition[1] < 0)
		cameraPosition[1] = 0;
}