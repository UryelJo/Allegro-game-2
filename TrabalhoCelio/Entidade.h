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

	bool __vivo = true;

	int __flags = 0;

	Moveset __movesetEntidade;

	Entidade() {};

	Entidade(int largura, int altura, float posicao_x, float posicao_y) {
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
	void colisaoPersonagemBordasMapa(int larguraMapa, int alturaMapa);
};

void Entidade::carregarImagemEntidade(const char* caminhoImagem) {
	__imagemEntidade = al_load_bitmap(caminhoImagem);
}

void Entidade::movimentacaoEntidade() {
	if (this->__movesetEntidade.__movendo_esquerda && __vivo) {
		posicao.__posicao_x -= 3;
	}
	if (this->__movesetEntidade.__movendo_direita && __vivo) {
		this->posicao.__posicao_x += 3;
	}
	if (this->__movesetEntidade.__movendo_cima && __vivo) {
		this->posicao.__posicao_y += 3;
	}
	if (this->__movesetEntidade.__movendo_baixo && __vivo) {
		this->posicao.__posicao_y -= 3;
	}
}

void Entidade::colisaoPersonagemBordasMapa(int larguraMapa, int alturaMapa) {
	if (this->posicao.__posicao_x < 0) {
		this->posicao.__posicao_x = 0;
	}
	if (this->posicao.__posicao_x + this->tamanho.__largura > larguraMapa) {
		this->posicao.__posicao_x = larguraMapa - this->tamanho.__largura;
	}
	if (this->posicao.__posicao_y < 0) {
		this->posicao.__posicao_y = 0;
	}
	if (this->posicao.__posicao_y + this->tamanho.__altura > alturaMapa) {
		this->posicao.__posicao_y = alturaMapa - this->tamanho.__altura;
	}
}