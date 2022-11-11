#ifndef Cabecalho_Personagem
#define Cabecalho_Personagem

#include <allegro5/bitmap.h>
#include "./Movimento.h"
#include "./Equipamento.h"
#include "./Itens.h"
#include "./Inventario.h"

typedef struct Personagem {
	char * nome[30];
	char * sobreNome[70];
	int idade;
	int inv[8];

	int imagemX;
	int imagemY;

	ALLEGRO_BITMAP * imagem;
	Movimento movimento;
	Inventario * inventario;

	Equipamento equipamentos[10];
} Personagem;

Personagem iniciarPersonagem();
void coletaItens(int id, Personagem * personagem);
void desenharPersonagem(Personagem personagem);

#endif // !Cabecalho_Personagem