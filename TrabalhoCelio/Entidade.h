#include "Moveset.h"

#include<allegro5/allegro.h>
#include<allegro5/allegro_image.h>

struct Frame {
	int __frame_x = 0;
	int __frame_y = 0;
	int __delay_troca_frame = 0;
};
struct Tamanho {
	int __largura = 0;
	int __altura = 0;
};
struct Posicao {
	float __posicao_x = 0.f;
	float __posicao_y = 0.f;
};

class Entidade {

public:
	ALLEGRO_BITMAP* __imagemEntidade = NULL;

	Frame frame;
	Tamanho tamanho;
	Posicao posicao;

	int __flags = 0;

	Moveset __movesetEntidade;

	Entidade() {};

	Entidade(const char* caminhoImagem, int largura, int altura, float posicao_x, float posicao_y) {
		carregarImagemEntidade(caminhoImagem);
		frame.__frame_x = 0;
		frame.__frame_y = 0;
		frame.__delay_troca_frame = 0;
		tamanho.__largura = largura;
		tamanho.__altura = altura;
		posicao.__posicao_x = posicao_x;
		posicao.__posicao_y = posicao_y;
	}

	void carregarImagemEntidade(const char* caminhoImagem);
	void movimentacaoEntidade();
	void movimentacaoParadaEntidade();
};

void Entidade::carregarImagemEntidade(const char* caminhoImagem) {
	__imagemEntidade = al_load_bitmap(caminhoImagem);
}

void Entidade::movimentacaoEntidade() {
	if (__movesetEntidade.__movendo_esquerda) {
		posicao.__posicao_x -= 3;
	}
	if (__movesetEntidade.__movendo_direita) {
		posicao.__posicao_x += 3;
	}
	if (__movesetEntidade.__movendo_cima) {
		posicao.__posicao_y += 3;
	}
	if (__movesetEntidade.__movendo_baixo) {
		posicao.__posicao_y -= 3;
	}
}