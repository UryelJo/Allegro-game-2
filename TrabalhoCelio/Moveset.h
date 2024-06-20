class Moveset {
public:
	bool __movendo_esquerda = false;
	bool __movendo_direita = false;
	bool __movendo_cima = false;
	bool __movendo_baixo = false;

	bool __parado_esquerda = false;
	bool __parado_direita = false;
	bool __parado_cima = false;
	bool __parado_baixo = false;

	bool __colidindo_esquerda = false;
	bool __colidindo_direita = false;
	bool __colidindo_cima = false;
	bool __colidindo_baixo = false;

	int __delay_troca_frame = 0;

	Moveset() {};
};