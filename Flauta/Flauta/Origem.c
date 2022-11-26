﻿//Libs externas
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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
#include "Cabecalho/Utils/Utilitario.h"
#include "Cabecalho/Posicao.h"
#include "Cabecalho/Movimento.h"
#include "Cabecalho/Personagem.h"
#include "Cabecalho/Pagina.h"
#include "PaginaCombinacao.h"
#include "Cabecalho/Cenario.h"
#include "Cabecalho/Utils/Imagem.h"
#include "Cabecalho/Missao.h"
#include <locale.h>

const int fps = 60;
int fpsAnimacao = 0;

Pagina paginaPrincipal;
Posicao posicaoMouse;
Pagina paginaCombinacao;
Personagem personagemPrincipal;
Posicao posicoes[1];
Mistura * misturas;
CenarioItem * cenarioItemInicial;
Missao* missaoInicial;
cJSON* jsonCenario;
cJSON* jsonMissoes;

ALLEGRO_EVENT_QUEUE* eventos = NULL;
ALLEGRO_BITMAP* bgCasa = NULL;
ALLEGRO_TRANSFORM camera;
ALLEGRO_FONT *  fonte = NULL;
ALLEGRO_KEYBOARD_STATE keyState;
ALLEGRO_TIMER * tempoRenderizacao = NULL;
ALLEGRO_FONT* fontePasso;
ALLEGRO_BITMAP* mapaImagem = NULL;
bool primeiraVolta = true;

float cameraPosition[2] = { 0 , 0 };

Personagem configurarPersonagemPrincipal(void);
void abrirPaginaComposicao();
void configuracaoInicial(void);
void registrarEventos(void);
void gerenciarPosicaoPersonagem(ALLEGRO_EVENT* evento);
void cameraUpdate(float* cameraPosition, Posicao * posicaoBase);
void carregarInformacaoesCenario(void);
void carregarInformacoesMissoes(void);
char* concatenarTexto(char* mensagem, char* conteudo, char* separador);
void desenharPassoMissao(PassoMissao* passoMissao);


void gerarMapa() {
	al_set_new_display_flags(ALLEGRO_NOFRAME);
	ALLEGRO_DISPLAY * displayMapa = al_create_display(
		4000,
		2500
	); //Cria a tela do programa
	al_set_target_backbuffer(displayMapa);
	//al_set_window_title(displayMapa, "Mapa");

	al_flip_display();
	al_clear_to_color(al_map_rgb(0, 0, 0), 0, 0);
	al_clear_to_color(al_map_rgb(0, 0, 0));

	desenharImagem(paginaPrincipal.background, paginaPrincipal.posicaoBackGroud);

	//cameraUpdate(cameraPosition, &personagemPrincipal.movimento.posicao);
	//al_identity_transform(&camera);
	//al_translate_transform(&camera, -cameraPosition[0], -cameraPosition[1]);
	//al_use_transform(&camera);

	//desenharPersonagem(personagemPrincipal);
	desenharCenarioItens(cenarioItemInicial);
	desenharPassoMissao(personagemPrincipal.missaoAtual->passosMissao);

	al_save_bitmap("screenshot.bmp", al_get_backbuffer(displayMapa));
	//mapaImagem = al_load_bitmap("screenshot.bmp");

	al_destroy_display(displayMapa);

	al_set_target_backbuffer(paginaPrincipal.display);
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

	//setlocale(LC_ALL, "");
	//ALLEGRO_CONFIG * config = al_load_config_file("Utils/configuracao.cfg");
	//const char* lang = get_config_string("system", "language", "EN");
	//al_set_config_value(config, "system", "language", "PT-BR");

	configuracaoInicial();
	personagemPrincipal = configurarPersonagemPrincipal();

	paginaPrincipal.personagemPrincipal = &personagemPrincipal;
	paginaCombinacao.personagemPrincipal = &personagemPrincipal;

	if (!paginaPrincipal.display)
		return -1;

	//paginaPrincipal.background.imagem = al_load_bitmap("Mapa.png");
	paginaPrincipal.background.imagem = al_load_bitmap("Utils/Imagens/Mapa.png");
	paginaPrincipal.posicaoBackGroud.posicaoX = 0;
	paginaPrincipal.posicaoBackGroud.tamanhoX = 3833;
	paginaPrincipal.posicaoBackGroud.posicaoY = 0;
	paginaPrincipal.posicaoBackGroud.tamanhoY = 2152;

	paginaPrincipal.backgroundCasa.imagem = al_load_bitmap("Utils/Imagens/Casa_Int.png");
	paginaPrincipal.posicaoBgCasa.posicaoX = 4500;
	paginaPrincipal.posicaoBgCasa.tamanhoX = 1277;
	paginaPrincipal.posicaoBgCasa.posicaoY = 4500;
	paginaPrincipal.posicaoBgCasa.tamanhoY = 898;

	bgCasa = al_load_bitmap("Utils/Imagens/Casa_Int.png");
	carregarInformacaoesCenario();
	carregarInformacoesMissoes();

	personagemPrincipal.missaoAtual = missaoInicial;
	misturas = iniciarMisturas(cenarioItemInicial);
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
			executarPaginaCombinacao(&paginaCombinacao, personagemPrincipal.inventario);
		else if (paginaPrincipal.aberta) {

			if (primeiraVolta) {
				/*gerarMapa();*/
				primeiraVolta = false;
			}
			gerenciarPosicaoPersonagem(&evento);

			if(personagemPrincipal.movimento.posicao.posicaoX <= 5140 && personagemPrincipal.movimento.posicao.posicaoX >= 5050 && personagemPrincipal.movimento.posicao.posicaoY >= 5240) {
				personagemPrincipal.movimento.posicao.posicaoX = 533;
				personagemPrincipal.movimento.posicao.posicaoY = 680;
			}
			if (personagemPrincipal.movimento.posicao.posicaoX >= 530 && personagemPrincipal.movimento.posicao.posicaoX <= 540 && personagemPrincipal.movimento.posicao.posicaoY >= 644 && personagemPrincipal.movimento.posicao.posicaoY <= 660) {
				personagemPrincipal.movimento.posicao.posicaoX = 5105;
				personagemPrincipal.movimento.posicao.posicaoY = 5220;
			}
		}

		
	}

	destruirCenarioItens(cenarioItemInicial);
	cJSON_Delete(jsonCenario);
	destruirMissoes(missaoInicial);
	cJSON_Delete(jsonMissoes);
	al_destroy_font(fonte);
	al_destroy_display(paginaPrincipal.display);
	al_destroy_event_queue(eventos);
	al_destroy_bitmap(personagemPrincipal.imagem);
	al_destroy_bitmap(paginaPrincipal.background.imagem);
	al_destroy_bitmap(paginaPrincipal.backgroundCasa.imagem);
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
		.imagem = al_load_bitmap("Serena.png")
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
	posicao.posicaoX = 5485;
	posicao.posicaoY = 4770;
	posicao.tamanhoX = al_get_bitmap_width(personagem.imagem) / 4;
	posicao.tamanhoY = al_get_bitmap_height(personagem.imagem) / 4;

	movimento.posicao = posicao;
	personagem.movimento = movimento;

	return personagem;
}

void configuracaoInicial(void) {
	paginaPrincipal = iniciarPagina();
	paginaPrincipal.aberta = true;
	paginaPrincipal.posicao.tamanhoX = 1280;
	paginaPrincipal.posicao.tamanhoY = 720;
	paginaPrincipal.display = al_create_display(
		paginaPrincipal.posicao.tamanhoX ,
		paginaPrincipal.posicao.tamanhoY
	); //Cria a tela do programa

	posicaoMouse.tamanhoX = 5;
	posicaoMouse.tamanhoY = 5;

	paginaCombinacao = iniciarPagina();
	fonte = al_load_font("arial_narrow_7.ttf", 12, 0);
	fontePasso = al_load_font("arial_narrow_7.ttf", 22, 0);

	registrarEventos();
}

void registrarEventos(void) {
	tempoRenderizacao = al_create_timer(1.0 / fps);//60 quadros por segundo
	eventos = al_create_event_queue();//Cria uma lista de eventos

	al_register_event_source(eventos, al_get_keyboard_event_source());
	al_register_event_source(eventos, al_get_display_event_source(paginaPrincipal.display));
	al_register_event_source(eventos, al_get_timer_event_source(tempoRenderizacao));
	al_register_event_source(eventos, al_get_mouse_event_source());
}

void abrirPaginaComposicao() {
	paginaCombinacao.posicao.posicaoX = 0;
	paginaCombinacao.posicao.posicaoY = 0;
	paginaCombinacao.posicao.tamanhoX = 500;
	paginaCombinacao.posicao.tamanhoY = 500;
	exibirPagina(&paginaCombinacao);
}

void gerenciarPosicaoPersonagem(ALLEGRO_EVENT* evento) {
	int posicaoXPersonagem = personagemPrincipal.movimento.posicao.posicaoX;
	int posicaoYPersonagem = personagemPrincipal.movimento.posicao.posicaoY;

	ALLEGRO_EVENT event = *evento;

	if (event.type == ALLEGRO_EVENT_KEY_DOWN) //Entra na tecla
	{
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
	}
	else if (event.type == ALLEGRO_EVENT_KEY_UP) //Entra na tecla
	{
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

		if (colediuComCenario(cenarioItemInicial, personagemPrincipal.movimento.posicao, true)) {
			personagemPrincipal.movimento.posicao.posicaoX = posicaoXPersonagem;
			personagemPrincipal.movimento.posicao.posicaoY = posicaoYPersonagem;
		}

		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0), 0, 0);
		al_clear_to_color(al_map_rgb(0, 0, 0));

		desenharImagem(paginaPrincipal.background, paginaPrincipal.posicaoBackGroud);
		desenharImagem(paginaPrincipal.backgroundCasa, paginaPrincipal.posicaoBgCasa);

		cameraUpdate(cameraPosition, &personagemPrincipal.movimento.posicao);
		al_identity_transform(&camera);
		al_translate_transform(&camera, -cameraPosition[0], -cameraPosition[1]);
		al_use_transform(&camera);
		
		desenharPersonagem(personagemPrincipal);
		desenharCenarioItens(cenarioItemInicial);
		desenharPassoMissao(personagemPrincipal.missaoAtual->passosMissao);
	}
	else if (event.type == ALLEGRO_EVENT_MOUSE_AXES) 
	{
		printf("\nMouse:\n\tX: %i\n\tY: %i", event.mouse.x, event.mouse.y);
		posicaoMouse.posicaoX = event.mouse.x + cameraPosition[0],
		posicaoMouse.posicaoY = event.mouse.y + cameraPosition[1];
		if (colediuComCenario(cenarioItemInicial, posicaoMouse, false) && obterElementoCenarioEmPosicao(cenarioItemInicial, posicaoMouse, false)->cenarioItem->coletavelPeloJogador)
			al_set_system_mouse_cursor(paginaPrincipal.display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
		else
			al_set_system_mouse_cursor(paginaPrincipal.display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
	}
	else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN || event.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) {
		if (event.mouse.button == 1 && colediuComCenario(cenarioItemInicial, posicaoMouse, false)) {
			ElementoCenario* elementoCenario = obterElementoCenarioEmPosicao(cenarioItemInicial, posicaoMouse, false);
			CenarioItem* cernarioItem = elementoCenario->cenarioItem;
			if (elementoCenario->cenarioItem->coletavelPeloJogador) {
				if (personagemPrincipal.inventario == NULL) {
					personagemPrincipal.inventario = inserirItemInventario(personagemPrincipal.inventario, elementoCenario->cenarioItem);
					elementoCenario = removerElementoCenario(elementoCenario);
					if (elementoCenario->indice == 0)
						cernarioItem->elementoInical = elementoCenario;
				}
				else if ((*personagemPrincipal.inventario->count) < 3) {
					Inventario* ultimoInventario = ultimoItemInventario(personagemPrincipal.inventario);
					if (ultimoInventario != NULL) {
						inserirItemInventario(ultimoInventario, elementoCenario->cenarioItem);
						elementoCenario = removerElementoCenario(elementoCenario);
					}
				}

				if (elementoCenario->indice == 0)
					cernarioItem->elementoInical = elementoCenario;
			}
		}
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

void carregarInformacaoesCenario(void) {
	jsonCenario = obterCJsonCenario();
	cJSON * elementosJson = bucarItemCJson(jsonCenario->child, "canarioItem");
	cenarioItemInicial = mapearCenariosItemCJson(NULL, elementosJson->child, NULL);
}
 
void carregarInformacoesMissoes(void) {
	jsonMissoes = obterMissoesJson();
	cJSON * missoesCJSON = bucarItemCJson(jsonMissoes->child, "missoes");
	missaoInicial = mapearMissoesDeJson(NULL, missoesCJSON->child, cenarioItemInicial);
}

char* concatenarTexto(char* mensagem1, char* mensagem2, char * separador) {
	if (mensagem1 != NULL) {
		//Mensagem Atual
		int countMensagem = strlen(mensagem1);
		//Separador
		int countSeparador = strlen(separador);
		//Nova Mensagem
		int count = strlen(mensagem2);
		char* mensagemFinal = (char*)malloc((count + countMensagem + countSeparador) * sizeof(char) + 1);

		strcpy(mensagemFinal, mensagem1);
		strcat(mensagemFinal, separador);
		strcat(mensagemFinal, mensagem2);

		return mensagemFinal;
	}

	return mensagem2;
}

void desenharPassoMissao(PassoMissao * passoMissao) {
	PassoMissao * atual = passoMissao;
	char* mensagem = concatenarTexto("Informacoes da missao: \n-------------------------", "", "");

	while (atual != NULL) {
		if (atual->obrigatorio)
			mensagem = concatenarTexto(mensagem, atual->mensagemInicial, "\n\n");
		atual = atual->proxima;
	}

	Posicao posicao = {
		.posicaoX = cameraPosition[0] + paginaPrincipal.posicao.tamanhoX - 300, //X inicial
		.posicaoY = cameraPosition[1] + 5, //Y inicial
		.tamanhoX = cameraPosition[0] + paginaPrincipal.posicao.tamanhoX - 5, //X Maximo
		.tamanhoY = cameraPosition[1] + paginaPrincipal.posicao.tamanhoY - 5 //Y Maximo
	};

	//Desenha o container que terá o conteúdo das missões
	al_draw_filled_rectangle(
		posicao.posicaoX,
		posicao.posicaoY,
		posicao.tamanhoX,
		posicao.tamanhoY,
		al_map_rgb(255, 255, 255)
	);

	//Escreve o texto com todos os passos obrigatorios para a conclusão da missão
	al_draw_multiline_textf(
		fontePasso,
		al_map_rgb(0, 0, 0),
		posicao.posicaoX + 10,
		posicao.posicaoY + 10,
		275,
		-1,
		0,
		mensagem
	);
}