#include "Origem.h"

const int fps = 60;
int fpsAnimacao = 0;

Pagina paginaPrincipal;
Posicao posicaoMouse;
Pagina paginaCombinacao;
Pagina paginaMenu;
Pagina paginaComandos;
Personagem personagemPrincipal;
Posicao posicoes[1];
Mistura * misturas;
Posicao * posicaoRealizarMistura;
Posicao * posicaoFinalizarMissao;
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

void gerarMapa() {
	al_set_new_display_flags(ALLEGRO_NOFRAME);
	ALLEGRO_DISPLAY * displayMapa = al_create_display(
		paginaPrincipal.posicaoBackGroud.tamanhoX,
		paginaPrincipal.posicaoBackGroud.tamanhoY
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
	//desenharPassoMissao(personagemPrincipal.missaoAtual->passosMissao);

	al_save_bitmap("screenshot.bmp", al_get_backbuffer(displayMapa));
	mapaImagem = al_load_bitmap("screenshot.bmp");

	al_destroy_display(displayMapa);

	al_set_target_backbuffer(paginaPrincipal.display);
}

void startGame() {

	carregarInformacaoesCenario();
	carregarInformacoesMissoes();

	personagemPrincipal.missaoAtual = missaoInicial;
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

	setlocale(LC_ALL, "Portuguese");

	configuracaoInicial();
	personagemPrincipal = configurarPersonagemPrincipal();
	bgCasa = al_load_bitmap("Utils/Imagens/Casa_Int.png");
	paginaPrincipal.personagemPrincipal = &personagemPrincipal;
	paginaCombinacao.personagemPrincipal = &personagemPrincipal;

	paginaComandos.background.imagem = al_load_bitmap("Utils/Imagens/Comandos.png");
	paginaComandos.posicaoBackGroud.posicaoX = 0;
	paginaComandos.posicaoBackGroud.tamanhoX = 1280;
	paginaComandos.posicaoBackGroud.posicaoY = 0;
	paginaComandos.posicaoBackGroud.tamanhoY = 720;
	paginaComandos.aberta = false;

	paginaMenu.background.imagem = al_load_bitmap("Utils/Imagens/placeholder.png");
	paginaMenu.posicaoBackGroud.posicaoX = 0;
	paginaMenu.posicaoBackGroud.tamanhoX = 1280;
	paginaMenu.posicaoBackGroud.posicaoY = 0;
	paginaMenu.posicaoBackGroud.tamanhoY = 720;
	paginaMenu.backgroundCasa.imagem = al_load_bitmap("Utils/Imagens/Lore.png");
	paginaMenu.aberta = true;

	Iniciar:
	startGame();

	if (!paginaPrincipal.display)
		return -1;

	al_start_timer(tempoRenderizacao);

	//gerarMapa();

	while (paginaPrincipal.aberta) {
		ALLEGRO_EVENT evento;
		al_wait_for_event(eventos, &evento);

		//Gerenciador de display

		if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
			if (evento.keyboard.keycode == ALLEGRO_KEY_I) {
				if (paginaCombinacao.aberta)
					ocultarPagina(&paginaCombinacao, &paginaPrincipal);
				else
					abrirPaginaComposicao();

				personagemPrincipal.movimento.direcaoY = DIRECAOYNENHUM;
				personagemPrincipal.movimento.direcaoX = DIRECAOXNENHUM;
			}
			else if (evento.keyboard.keycode == ALLEGRO_KEY_C) {
				personagemPrincipal.movimento.direcaoY = DIRECAOYNENHUM;
				personagemPrincipal.movimento.direcaoX = DIRECAOXNENHUM;
				paginaComandos.aberta = !(paginaComandos.aberta);
			}
		}
		else if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			paginaPrincipal.aberta = false;
		
		//Execucao de dislay
		if (paginaMenu.aberta)
			menu(evento);
		else if (paginaComandos.aberta) {			
			abrirPaginaComandos(evento);
			if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
				paginaComandos.aberta = false;
			}
		}
		else if (paginaCombinacao.aberta)
			executarPaginaCombinacao(&paginaCombinacao, personagemPrincipal.inventario);
		else if (paginaPrincipal.aberta) {
			int retorno = gerenciarPosicaoPersonagem(&evento);
			if (retorno != NULL) {
				if (retorno == 1)
					goto Restart;
				else
					goto FinalizarGame;
			}

			if(personagemPrincipal.movimento.posicao.posicaoX <= 5140 && personagemPrincipal.movimento.posicao.posicaoX >= 5050 && personagemPrincipal.movimento.posicao.posicaoY >= 5240) {
				personagemPrincipal.movimento.posicao.posicaoX = 533;
				personagemPrincipal.movimento.posicao.posicaoY = 680;
			}
			if (personagemPrincipal.movimento.posicao.posicaoX >= 535 && personagemPrincipal.movimento.posicao.posicaoX <= 540 && personagemPrincipal.movimento.posicao.posicaoY >= 644 && personagemPrincipal.movimento.posicao.posicaoY <= 660) {
				personagemPrincipal.movimento.posicao.posicaoX = 5105;
				personagemPrincipal.movimento.posicao.posicaoY = 5220;
			}
		}
	}

	Restart:
		if (paginaPrincipal.aberta) {
			destruirCenarioItens(cenarioItemInicial);
			free(posicaoRealizarMistura);
			destruirMissoes(missaoInicial);
			destruirInvetario(personagemPrincipal.inventario);
			free(posicaoFinalizarMissao);
			cJSON_Delete(jsonCenario);
			cJSON_Delete(jsonMissoes);
			goto Iniciar;
		}

	FinalizarGame:
		//Remover dados do programa da memoria
		destruirCenarioItens(cenarioItemInicial);
		free(posicaoRealizarMistura);
		destruirMissoes(missaoInicial);
		destruirInvetario(personagemPrincipal.inventario);
		free(posicaoFinalizarMissao);
		cJSON_Delete(jsonCenario);
		cJSON_Delete(jsonMissoes);
		//Remover dados do ALLEGRO da memoria
		al_destroy_font(fontePasso);
		al_destroy_font(fonte);
		al_destroy_bitmap(mapaImagem);
		al_destroy_display(paginaPrincipal.display);
		al_destroy_event_queue(eventos);
		al_destroy_bitmap(personagemPrincipal.imagem);
		al_destroy_bitmap(paginaPrincipal.background.imagem);
		al_destroy_bitmap(paginaPrincipal.backgroundCasa.imagem);
		al_destroy_bitmap(paginaCombinacao.backgroundCasa.imagem);
		al_destroy_bitmap(paginaMenu.background.imagem);
		al_destroy_bitmap(paginaMenu.backgroundCasa.imagem);
		al_destroy_bitmap(paginaComandos.background.imagem);
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

	paginaPrincipal.background.imagem = al_load_bitmap("Utils/Imagens/Mapa.png");
	paginaPrincipal.posicaoBackGroud.posicaoX = 0;
	paginaPrincipal.posicaoBackGroud.tamanhoX = 5268;
	paginaPrincipal.posicaoBackGroud.posicaoY = 0;
	paginaPrincipal.posicaoBackGroud.tamanhoY = 2160;

	paginaPrincipal.backgroundCasa.imagem = al_load_bitmap("Utils/Imagens/Casa_Int.png");
	paginaPrincipal.posicaoBgCasa.posicaoX = 4500;
	paginaPrincipal.posicaoBgCasa.tamanhoX = 1277;
	paginaPrincipal.posicaoBgCasa.posicaoY = 4500;
	paginaPrincipal.posicaoBgCasa.tamanhoY = 898;

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

void menu(ALLEGRO_EVENT evento) {
	desenharImagem(paginaMenu.background, paginaMenu.posicaoBackGroud);

	if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
		if (evento.keyboard.keycode == ALLEGRO_KEY_SPACE) {
			paginaMenu.aberta = false;
		
			desenharImagem(paginaMenu.backgroundCasa, paginaMenu.posicaoBackGroud);
			al_flip_display();
			al_rest(1);

			abrirPaginaComandos(evento);
			al_flip_display();
			al_rest(1);

			paginaPrincipal.aberta = true;
		}
	}

	al_flip_display();
	al_clear_to_color(al_map_rgb(0, 0, 0));
	/*if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
		if (evento.keyboard.keycode == ALLEGRO_KEY_C) {
			paginaMenu.aberta = false;
			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_flip_display();
			al_rest(2);
			abrirPaginaComandos(evento);
		}
	}
	if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
		if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
			return 0;
		}
	}*/
}

void abrirPaginaComandos(ALLEGRO_EVENT evento) {

	al_draw_bitmap(
		paginaComandos.background.imagem,
		cameraPosition[0],
		cameraPosition[1],
		paginaComandos.posicaoBackGroud.tamanhoX,
		paginaComandos.posicaoBackGroud.tamanhoY,
		0
	);
	al_flip_display();
	//al_clear_to_color(al_map_rgb(0, 0, 0));
	/*if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
		if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
			paginaComandos.aberta = false;
			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_flip_display();
			al_rest(1);
			paginaMenu.aberta = true;
		}
	}*/
}

void abrirPaginaComposicao() {
	paginaCombinacao.background.imagem = al_load_bitmap("Utils/Imagens/Inventario.png");
	paginaCombinacao.posicao.posicaoX = 0;
	paginaCombinacao.posicao.posicaoY = 0;
	paginaCombinacao.posicao.tamanhoX = 230;
	paginaCombinacao.posicao.tamanhoY = 104;
	exibirPagina(&paginaCombinacao);
}

int gerenciarPosicaoPersonagem(ALLEGRO_EVENT* evento) {
	int posicaoXPersonagem = personagemPrincipal.movimento.posicao.posicaoX;
	int posicaoYPersonagem = personagemPrincipal.movimento.posicao.posicaoY;

	ALLEGRO_EVENT event = *evento;

	if (event.type == ALLEGRO_EVENT_KEY_DOWN) //Entra na tecla
	{
		switch (event.keyboard.keycode)
		{
			case ALLEGRO_KEY_S:
				personagemPrincipal.movimento.direcaoY = DIRECAOYBAIXO;
				personagemPrincipal.imagemX = 0;
				personagemPrincipal.imagemY = 0 * al_get_bitmap_height(personagemPrincipal.imagem) / 4;
				break;
			case ALLEGRO_KEY_A:
				personagemPrincipal.movimento.direcaoX = DIRECAOXESQUERDA;
				personagemPrincipal.imagemX = 0;
				personagemPrincipal.imagemY = 1 * al_get_bitmap_height(personagemPrincipal.imagem) / 4;
				break;
			case ALLEGRO_KEY_D:
				personagemPrincipal.movimento.direcaoX = DIRECAOXDIREITA;
				personagemPrincipal.imagemX = 0;
				personagemPrincipal.imagemY = 2 * al_get_bitmap_height(personagemPrincipal.imagem) / 4;
				break;
			case ALLEGRO_KEY_W:
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
			case ALLEGRO_KEY_W:
				personagemPrincipal.movimento.direcaoY = DIRECAOYNENHUM;
				break;
			case ALLEGRO_KEY_S:
				personagemPrincipal.movimento.direcaoY = DIRECAOYNENHUM;
				break;
			case ALLEGRO_KEY_D:
				personagemPrincipal.movimento.direcaoX = DIRECAOXNENHUM;
				break;
			case ALLEGRO_KEY_A:
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
		if (personagemPrincipal.missaoAtual != NULL)
			desenharPassoMissao(personagemPrincipal.missaoAtual->passosMissao);
	}
	else if (event.type == ALLEGRO_EVENT_MOUSE_AXES) 
	{
		posicaoMouse.posicaoX = event.mouse.x + cameraPosition[0],
		posicaoMouse.posicaoY = event.mouse.y + cameraPosition[1];

		if (posicaoColediu(*posicaoFinalizarMissao, posicaoMouse) || posicaoColediu(*posicaoRealizarMistura, posicaoMouse) || (colediuComCenario(cenarioItemInicial, posicaoMouse, false) && obterElementoCenarioEmPosicao(cenarioItemInicial, posicaoMouse, false)->cenarioItem->coletavelPeloJogador))
			al_set_system_mouse_cursor(paginaPrincipal.display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
		else
			al_set_system_mouse_cursor(paginaPrincipal.display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
	}
	else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN || event.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) {
		if (event.mouse.button == 1) {
			if (personagemPrincipal.missaoAtual != NULL && posicaoColediu(*posicaoFinalizarMissao, posicaoMouse)) {
				Inventario * itemInventario = buscarItemInventario(personagemPrincipal.inventario, personagemPrincipal.missaoAtual->misturaFinal->produto->codigo);

				if (itemInventario == NULL) {
					printf("Para concluir essa missao é necessário ter em seu inventario um %s", personagemPrincipal.missaoAtual->misturaFinal->produto->nome);
				}
				else
				{
					destruirInvetario(personagemPrincipal.inventario);
					personagemPrincipal.inventario = NULL;
					printf("Missão finalizada.");

					if (personagemPrincipal.missaoAtual->proxima != NULL) {
						al_show_native_message_box(paginaPrincipal.display, "Missao concluida", "Parabens,", "voce finalizou a missão, vamos para a proxima tarefa.", "Sim", ALLEGRO_MESSAGEBOX_WARN);
						personagemPrincipal.missaoAtual = personagemPrincipal.missaoAtual->proxima;
					}
					else {
						personagemPrincipal.missaoAtual = NULL;
						return al_show_native_message_box(paginaPrincipal.display, "Final do jogo", "Parabens,", "voce chegou ao final do jogo. Deseja reiniciar o game?", "Sim", ALLEGRO_MESSAGEBOX_YES_NO);
					}
				};
			}
			else if (posicaoColediu(*posicaoRealizarMistura, posicaoMouse)) {
				if (personagemPrincipal.missaoAtual != NULL && misturaPossuiTodosIngredientes(personagemPrincipal.missaoAtual->misturaFinal->ingrediente, personagemPrincipal.inventario)) {
					destruirInvetario(personagemPrincipal.inventario);
					personagemPrincipal.inventario = inserirItemInventario(NULL, personagemPrincipal.missaoAtual->misturaFinal->produto);
					abrirPaginaComposicao();
				} 
				else
				{
					destruirInvetario(personagemPrincipal.inventario);
					personagemPrincipal.inventario = NULL;
					al_show_native_message_box(paginaPrincipal.display, "Ingredientes incorretos", "Ingredientes incorretos", "Nao foi possivel realizar a mistura com os ingredientes em seu inventario, colete os itens corretos e tente novamente.", NULL, ALLEGRO_MESSAGEBOX_WARN);
				}
			}
			else if (colediuComCenario(cenarioItemInicial, posicaoMouse, false)) {
				ElementoCenario* elementoCenario = obterElementoCenarioEmPosicao(cenarioItemInicial, posicaoMouse, false);
				CenarioItem* cernarioItem = elementoCenario->cenarioItem;
				
				if (elementoCenario->cenarioItem->coletavelPeloJogador) {
					if (personagemPrincipal.inventario == NULL) {
						personagemPrincipal.inventario = inserirItemInventario(personagemPrincipal.inventario, elementoCenario->cenarioItem);
						if (cernarioItem->removeItenCenarioAposColeta)
							elementoCenario = removerElementoCenario(elementoCenario);
					}
					else if ((*personagemPrincipal.inventario->count) < 3) {
						Inventario* ultimoInventario = ultimoItemInventario(personagemPrincipal.inventario);
						if (ultimoInventario != NULL) {
							ultimoInventario->proximo = inserirItemInventario(ultimoInventario, elementoCenario->cenarioItem);
							if (cernarioItem->removeItenCenarioAposColeta)
								elementoCenario = removerElementoCenario(elementoCenario);
						}
					}

					if (cernarioItem->removeItenCenarioAposColeta) {
						if (elementoCenario == NULL)
							cernarioItem->elementoInical = NULL;
						else if (elementoCenario->indice == 0)
							cernarioItem->elementoInical = elementoCenario;
					}
				}
			}
		}
	}

	return NULL;
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
	
	cJSON* possicaoRealizarMisturaCJson = bucarItemCJson(jsonMissoes->child, "posicoesRealizarMistura");
	posicaoRealizarMistura = mapearPosicaoMistura(possicaoRealizarMisturaCJson);

	cJSON* posicaoFinalizarMissaoCJson = bucarItemCJson(jsonMissoes->child, "posicaoFinalizarMissao");
	posicaoFinalizarMissao = mapearPosicaoMistura(posicaoFinalizarMissaoCJson);

	cJSON* missoesCJSON = bucarItemCJson(jsonMissoes->child, "missoes");
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