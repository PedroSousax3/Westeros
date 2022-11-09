#ifndef Cabecalho_Personagem
#define Cabecalho_Personagem

#include <allegro5/bitmap.h>
#include "../Cabecalho/Movimento.h"
#include "../Cabecalho/Equipamento.h"
#include "../Cabecalho/Itens.h"

typedef struct Personagem {
	char * nome[30];
	char * sobreNome[70];
	int idade;
	int inventario[8];

	int imagemX;
	int imagemY;

	ALLEGRO_BITMAP * imagem;
	Movimento movimento;
	Inventario * inventario;

	Equipamento equipamentos[10];
} Personagem;

Personagem iniciarPersonagem();
void coletaItens(int id);
void desenharPersonagem(Personagem personagem);
void popularInv();

#endif // !Cabecalho_Personagem