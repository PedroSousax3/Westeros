#include <allegro5/allegro5.h>
#include <stdbool.h>

#include "../Cabecalho/Personagem.h"

Personagem persoInv;


Personagem iniciarPersonagem() {
	Personagem personagem = {
		.nome = NULL,
		.sobreNome = NULL,
		.idade = 0,
		.imagemX = 0,
		.imagemY = 0
	};

	return personagem;
}

void desenharPersonagem(Personagem personagem) {
	al_draw_bitmap_region(
		personagem.imagem,
		personagem.imagemX,
		personagem.imagemY,
		personagem.movimento.posicao.tamanhoX,
		personagem.movimento.posicao.tamanhoY,
		personagem.movimento.posicao.posicaoX,
		personagem.movimento.posicao.posicaoY,
		0
	);
}

void coletaItens(int id, Personagem * personagem)
{
	int n = 0;
	
	while (n < 8 && personagem->inventario[n] != 0)
	{
		n++;
	}
	if (personagem->inventario[n] == 0)
	{
		personagem->inventario[n] = id;
		
	}
}

void popularInv()
{
	int n = 1;
	while (n < 8) {
		persoInv.inventario[n] = n;
		n++;
	}
}
