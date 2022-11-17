#ifndef Cabecalho_PaginaCombincao
#define Cabecalho_PaginaCombincao

#include <allegro5/allegro_primitives.h>
#include "Cabecalho/Pagina.h"
//typedef struct PaginaCombicacao {
//
//} PaginaCombinacao;
void desenharItemInventarioTelaConbinacao(Inventario* inventario, Posicao posicaoDoItemAnterior, Pagina* pagina);
void executarPaginaCombinacao(Pagina* pagina, Inventario * inventario);
#endif // !Cabecalho_PaginaCombincao

