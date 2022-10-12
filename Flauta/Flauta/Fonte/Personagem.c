#include <allegro5/allegro5.h>
#include <stdbool.h>

#include "../Cabecalho/Personagem.h"

Personagem * iniciarPersonagem() {
	Personagem personagem = {
		.nome = NULL,
		.sobreNome = NULL,
		.idade = 0,
		.imagemX = 0,
		.imagemY = 0
	};

	return &personagem;
}

void desenharPersonagem(Personagem * personagem) {
	al_draw_bitmap_region(
		personagem->imagem,
		personagem->imagemX,
		personagem->imagemY,
		personagem->movimento->posicao->tamanhoX,
		personagem->movimento->posicao->tamanhoY,
		personagem->movimento->posicao->posicaoX,
		personagem->movimento->posicao->posicaoY,
		NULL
	);
}