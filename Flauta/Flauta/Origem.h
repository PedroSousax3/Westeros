//Libs externas
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

void gerarMapa();
void startGame();
int main(void);
Personagem configurarPersonagemPrincipal(void);
void configuracaoInicial(void);
void registrarEventos(void);
void menu(ALLEGRO_EVENT evento);
void abrirPaginaComandos(ALLEGRO_EVENT evento);
void abrirPaginaComposicao();
int gerenciarPosicaoPersonagem(ALLEGRO_EVENT* evento);
void cameraUpdate(float* cameraPosition, Posicao* posicaoBase);
void carregarInformacaoesCenario(void);
void carregarInformacoesMissoes(void);
char* concatenarTexto(char* mensagem1, char* mensagem2, char* separador);
void desenharPassoMissao(PassoMissao* passoMissao);