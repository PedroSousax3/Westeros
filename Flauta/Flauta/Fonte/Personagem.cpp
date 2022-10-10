#include <allegro5/allegro5.h>

#include "../Cabecalho/Personagem.h"

Personagem::Personagem() { }

void Personagem::desenharPersonagem() {
	al_draw_bitmap_region(
		this->imagem,
		this->imagemX,
		this->imagemY,
		this->movimento.posicao.tamanhoX,
		this->movimento.posicao.tamanhoY,
		this->movimento.posicao.posicaoX,
		this->movimento.posicao.posicaoY,
		NULL
	);
}