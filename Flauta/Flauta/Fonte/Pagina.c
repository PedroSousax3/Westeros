#include "../Cabecalho/Pagina.h"

void iniciarPagina(Pagina * pagina) {
	pagina->altura = 0;
	pagina->largura = 0;
	//pagina->nome = "";
	ocultarPagina(pagina);
}
void exibirPagina(Pagina* pagina) {
	pagina->aberta = true;
}
void ocultarPagina(Pagina* pagina) {
	pagina->aberta = false;
}