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

	Frame __frame;
	Tamanho __tamanho;
	Posicao __posicao;

	int __flags = 0;

	Moveset __movesetEntidade;

	Entidade() {};

	Entidade(int largura, int altura, float posicao_x, float posicao_y) {
		__frame.__frame_x = 0;
		__frame.__frame_y = 0;
		__frame.__delay_troca_frame = 0;
		__tamanho.__largura = largura;
		__tamanho.__altura = altura;
		__posicao.__posicao_x = posicao_x;
		__posicao.__posicao_y = posicao_y;
	}

	void carregarImagemEntidade(const char* caminhoImagem);
	void movimentacaoEntidade();
	void colisaoPersonagemComBordasMapa(int larguraMapa, int alturaMapa);
	void colisaoPersonagemComEntidade(Entidade* entidade);
};

void Entidade::carregarImagemEntidade(const char* caminhoImagem) {
	__imagemEntidade = al_load_bitmap(caminhoImagem);
}

void Entidade::movimentacaoEntidade() {
	if (this->__movesetEntidade.__movendo_esquerda && !this->__movesetEntidade.__colidindo_esquerda) {
		this->__posicao.__posicao_x -= 3;
	}
	if (this->__movesetEntidade.__movendo_direita && !this->__movesetEntidade.__colidindo_direita) {
		this->__posicao.__posicao_x += 3;
	}
	if (this->__movesetEntidade.__movendo_cima && !this->__movesetEntidade.__colidindo_cima) {
		this->__posicao.__posicao_y += 3;
	}
	if (this->__movesetEntidade.__movendo_baixo && !this->__movesetEntidade.__colidindo_baixo) {
		this->__posicao.__posicao_y -= 3;
	}

	if (this->__movesetEntidade.__movendo_esquerda 
		|| this->__movesetEntidade.__movendo_direita 
		|| this->__movesetEntidade.__movendo_baixo 
		|| this->__movesetEntidade.__movendo_cima) {

		this->__movesetEntidade.__delay_troca_frame++;	
		if (this->__movesetEntidade.__delay_troca_frame == 15) {
			this->__frame.__frame_x++;
			if (this->__frame.__frame_x == 6) {
				this->__frame.__frame_x = 3;
			}
			this->__movesetEntidade.__delay_troca_frame = 0;
		}
	} else {
		this->__frame.__frame_x = 0;
		this->__movesetEntidade.__delay_troca_frame = 0;
	}
}

void Entidade::colisaoPersonagemComBordasMapa(int larguraMapa, int alturaMapa) {
	if (this->__posicao.__posicao_x < 0) {
		this->__posicao.__posicao_x = 0;
	}
	if (this->__posicao.__posicao_x + this->__tamanho.__largura > larguraMapa) {
		this->__posicao.__posicao_x = larguraMapa - this->__tamanho.__largura;
	}
	if (this->__posicao.__posicao_y < 0) {
		this->__posicao.__posicao_y = 0;
	}
	if (this->__posicao.__posicao_y + this->__tamanho.__altura > alturaMapa) {
		this->__posicao.__posicao_y = alturaMapa - this->__tamanho.__altura;
	}
}

void Entidade::colisaoPersonagemComEntidade(Entidade* entidade) {
	if (this->__posicao.__posicao_x + this->__tamanho.__largura > entidade->__posicao.__posicao_x &&
		this->__posicao.__posicao_x < entidade->__posicao.__posicao_x + entidade->__tamanho.__largura &&
		this->__posicao.__posicao_y + this->__tamanho.__altura > entidade->__posicao.__posicao_y &&
		this->__posicao.__posicao_y < entidade->__posicao.__posicao_y + entidade->__tamanho.__altura) {
		if (this->__posicao.__posicao_x + this->__tamanho.__largura > entidade->__posicao.__posicao_x &&
			this->__posicao.__posicao_x < entidade->__posicao.__posicao_x + entidade->__tamanho.__largura) {
			if (this->__posicao.__posicao_y + this->__tamanho.__altura > entidade->__posicao.__posicao_y &&
				this->__posicao.__posicao_y < entidade->__posicao.__posicao_y + entidade->__tamanho.__altura) {
				if (this->__posicao.__posicao_x < entidade->__posicao.__posicao_x) {
					this->__movesetEntidade.__colidindo_direita = true;
				}
				if (this->__posicao.__posicao_x > entidade->__posicao.__posicao_x) {
					this->__movesetEntidade.__colidindo_esquerda = true;
				}
				if (this->__posicao.__posicao_y < entidade->__posicao.__posicao_y) {
					this->__movesetEntidade.__colidindo_cima = true;
				}
				if (this->__posicao.__posicao_y > entidade->__posicao.__posicao_y) {
					this->__movesetEntidade.__colidindo_baixo = true;
				}
			}
		}
	}
	else {
		this->__movesetEntidade.__colidindo_direita = false;
		this->__movesetEntidade.__colidindo_esquerda = false;
		this->__movesetEntidade.__colidindo_cima = false;
		this->__movesetEntidade.__colidindo_baixo = false;
	}
}