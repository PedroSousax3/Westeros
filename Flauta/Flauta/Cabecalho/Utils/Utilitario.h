#ifndef Cabecalho_Utilitario
#define Cabecalho_Utilitario

#include <allegro5/allegro_primitives.h>
#include "../Posicao.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int gerarNumeroAleatorioInt(int inicio, int fim);
void desenhaQuadrado(Posicao posicao, ALLEGRO_COLOR color);
#endif