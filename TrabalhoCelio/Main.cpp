#include "Entidade.h"
#include "Mapa.h"
#include "Projetil.h"
#include "Inimigo.h"

//Include das bibliotecas do Allegro
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_native_dialog.h>
#include <vector>

ALLEGRO_DISPLAY* telaGame = NULL;
ALLEGRO_TIMER* fps = NULL;
ALLEGRO_EVENT_QUEUE* filaEventos = NULL;

Entidade playerPrimario = Entidade(32, 32, 300, 50);
Entidade playerSecundario = Entidade(32, 32, 250, 60);
Mapa mapa = Mapa();
std::vector<Projetil> projectiles; // Create a vector to store projectiles
std::vector<Inimigo> inimigos; // Create a vector to store enemies
enum Move { CIMA, BAIXO, DIREITA, ESQUERDA };
Move direcao;
Move direcaoSecundario;
float ultimoTempoInimigo = 0; // Armazena o tempo desde a última geração de inimigo
float intervaloInimigo = 1.0; // Intervalo em segundos entre gerações de inim

void atirarTiroPersonagemPrincipal();
void atirarTiroPersonagemSecundario();
void inicializacao();
void atualizarLimparDesenhar();
void encerramento();
void atualizarProjeteis();
void spawnarInimigos();

int main() {
	inicializacao();
	al_clear_to_color(al_map_rgb(255, 255, 255));
	al_flip_display();

	al_start_timer(fps);

	bool desenhar = false;

	while (true) {
		ALLEGRO_EVENT evento;
		al_wait_for_event(filaEventos, &evento);

		if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
			break;
		}

		if (evento.type == ALLEGRO_EVENT_TIMER) {
			desenhar = true;
		}

		if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (evento.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				playerPrimario.__movesetEntidade.__movendo_baixo = true;
				playerPrimario.__frame.__frame_x = 3;
				playerPrimario.__frame.__frame_y = 2;
				direcaoSecundario = CIMA;
				break;
			case ALLEGRO_KEY_DOWN:
				playerPrimario.__movesetEntidade.__movendo_cima = true;
				playerPrimario.__frame.__frame_x = 3;
				playerPrimario.__frame.__frame_y = 1;
				direcaoSecundario = BAIXO;
				break;
			case ALLEGRO_KEY_LEFT:
				playerPrimario.__movesetEntidade.__movendo_esquerda = true;
				playerPrimario.__frame.__frame_x = 3;
				playerPrimario.__frame.__frame_y = 0;
				playerPrimario.__flags = ALLEGRO_FLIP_HORIZONTAL;
				direcaoSecundario = ESQUERDA;
				break;
			case ALLEGRO_KEY_RIGHT:
				playerPrimario.__movesetEntidade.__movendo_direita = true;
				playerPrimario.__frame.__frame_x = 3;
				playerPrimario.__frame.__frame_y = 0;
				playerPrimario.__flags = 0;
				direcaoSecundario = DIREITA;
				break;
			case ALLEGRO_KEY_W:
				playerSecundario.__movesetEntidade.__movendo_baixo = true;
				playerSecundario.__frame.__frame_x = 3;
				playerSecundario.__frame.__frame_y = 2;
				direcao = CIMA;
				break;
			case ALLEGRO_KEY_S:
				playerSecundario.__movesetEntidade.__movendo_cima = true;
				playerSecundario.__frame.__frame_x = 3;
				playerSecundario.__frame.__frame_y = 1;
				direcao = BAIXO;
				break;
			case ALLEGRO_KEY_A:
				playerSecundario.__movesetEntidade.__movendo_esquerda = true;
				playerSecundario.__frame.__frame_x = 3;
				playerSecundario.__frame.__frame_y = 0;
				playerSecundario.__flags = ALLEGRO_FLIP_HORIZONTAL;
				direcao = ESQUERDA;
				break;
			case ALLEGRO_KEY_D:
				playerSecundario.__movesetEntidade.__movendo_direita = true;
				playerSecundario.__frame.__frame_x = 3;
				playerSecundario.__frame.__frame_y = 0;
				playerSecundario.__flags = 0;
				direcao = DIREITA;
				break;
			case ALLEGRO_KEY_SPACE:
				atirarTiroPersonagemSecundario();
				break;
			case ALLEGRO_KEY_ENTER:
				atirarTiroPersonagemPrincipal();
				break;
			}
		}

		if (evento.type == ALLEGRO_EVENT_KEY_UP) {
			switch (evento.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				playerPrimario.__movesetEntidade.__movendo_baixo = false;
				break;
			case ALLEGRO_KEY_DOWN:
				playerPrimario.__movesetEntidade.__movendo_cima = false;
				break;
			case ALLEGRO_KEY_LEFT:
				playerPrimario.__movesetEntidade.__movendo_esquerda = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				playerPrimario.__movesetEntidade.__movendo_direita = false;
				break;
			case ALLEGRO_KEY_W:
				playerSecundario.__movesetEntidade.__movendo_baixo = false;
				break;
			case ALLEGRO_KEY_S:
				playerSecundario.__movesetEntidade.__movendo_cima = false;
				break;
			case ALLEGRO_KEY_A:
				playerSecundario.__movesetEntidade.__movendo_esquerda = false;
				break;
			case ALLEGRO_KEY_D:
				playerSecundario.__movesetEntidade.__movendo_direita = false;
				break;
			}
		}

		if (desenhar && al_is_event_queue_empty(filaEventos)) {
			playerPrimario.colisaoPersonagemComEntidade(&playerSecundario);
			playerPrimario.movimentacaoEntidade();
			playerPrimario.colisaoPersonagemComBordasMapa(mapa.__largura__tela, mapa.__altura__tela);
			playerSecundario.colisaoPersonagemComEntidade(&playerPrimario);
			playerSecundario.movimentacaoEntidade();
			playerSecundario.colisaoPersonagemComBordasMapa(mapa.__largura__tela, mapa.__altura__tela);
			
			atualizarLimparDesenhar();

			desenhar = false;
		}

		atualizarProjeteis();
		spawnarInimigos();
	}

	encerramento();
}

void inicializacao() {
	al_init();
	al_init_primitives_addon();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_keyboard();

	al_set_new_display_flags(ALLEGRO_NOFRAME);
	telaGame = al_create_display(mapa.__largura__tela, mapa.__altura__tela);
	if (!telaGame)
	{
		al_show_native_message_box(telaGame, "ERRO", "ERRO", "Erro ao criar o display", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return;
	}

	//Inicialização do Timer do Game
	fps = al_create_timer(1.0 / mapa.__fpsGame);
	if (!fps) {
		al_show_native_message_box(telaGame, "ERRO", "ERRO", "Erro ao criar o timer", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return;
	}

	//Inicialização da Fila de Eventos
	filaEventos = al_create_event_queue();
	if (!filaEventos)
	{
		al_show_native_message_box(telaGame, "ERRO", "ERRO", "Erro ao criar a fila de eventos", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return;
	}

	//Registro de Eventos
	al_register_event_source(filaEventos, al_get_display_event_source(telaGame));
	al_register_event_source(filaEventos, al_get_timer_event_source(fps));
	al_register_event_source(filaEventos, al_get_keyboard_event_source());

	playerPrimario.carregarImagemEntidade("Assets/PlayerTileMap.png");
	playerSecundario.carregarImagemEntidade("Assets/PlayerTileMap.png");
	mapa.carregarImagemChao("Assets/Chao.png");
}

void atualizarLimparDesenhar() {
	int i = 0;
	al_clear_to_color(al_map_rgb(0, 0, 0));
	mapa.construirMapa(mapa.__representacaoMapa);
	al_draw_bitmap_region(playerPrimario.__imagemEntidade, (playerPrimario.__frame.__frame_x * playerPrimario.__tamanho.__largura) , (playerPrimario.__frame.__frame_y * playerPrimario.__tamanho.__altura), playerPrimario.__tamanho.__largura, playerPrimario.__tamanho.__altura, playerPrimario.__posicao.__posicao_x, playerPrimario.__posicao.__posicao_y, playerPrimario.__flags);
	al_draw_bitmap_region(playerSecundario.__imagemEntidade, (playerSecundario.__frame.__frame_x * playerSecundario.__tamanho.__largura), (playerSecundario.__frame.__frame_y * playerSecundario.__tamanho.__altura), playerSecundario.__tamanho.__largura, playerSecundario.__tamanho.__altura, playerSecundario.__posicao.__posicao_x, playerSecundario.__posicao.__posicao_y, playerSecundario.__flags);
	for (auto it = projectiles.begin(); it != projectiles.end();)
	{
		Projetil& projectile = *it;
		i += 1;
		projectile.x += projectile.x_velocity;
		projectile.y += projectile.y_velocity;
		al_draw_bitmap(projectile.image, projectile.x + 50, projectile.y, 0);
		if (projectile.isOutOfBounds(mapa.__largura__tela, mapa.__altura__tela))
		{
			std::cout << "Destroyed a projectile" << std::endl;
			al_destroy_bitmap(projectile.image); // Deallocate the memory used by the bitmap
			it = projectiles.erase(it);
			std::cout << "Number of projectiles left: " << projectiles.size() << std::endl;
		}
		else
		{
			++it;
		}
	}
	for (auto& inimigo : inimigos) {
		inimigo.moverPara(playerPrimario.__posicao.__posicao_x, playerPrimario.__posicao.__posicao_y);
	}
	for (auto& inimigo : inimigos) {
		al_draw_bitmap(inimigo.image, inimigo.x, inimigo.y, 0); // Supondo que você tenha uma imagem para o inimigo
	}
	al_flip_display();
}

void encerramento() {
	al_destroy_display(telaGame);
	al_destroy_bitmap(playerPrimario.__imagemEntidade);
	al_destroy_bitmap(playerSecundario.__imagemEntidade);
	al_destroy_timer(fps);
	al_destroy_event_queue(filaEventos);
}

void atirarTiroPersonagemPrincipal()
{
	// Carrega a imagem do projétil
	ALLEGRO_BITMAP* imagemProj = al_load_bitmap("Assets/pilula_8bit.png");
	if (!imagemProj) {
		al_show_native_message_box(telaGame, "ERRO", "Falha ao carregar a imagem", "Não foi possível carregar a imagem do projétil.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return; // Sai da função se a imagem não puder ser carregada
	}

	// Cria um novo projétil na posição do jogador
	Projetil proj = Projetil(playerPrimario.__posicao.__posicao_x, playerPrimario.__posicao.__posicao_y + 32, 5, 0, imagemProj);
	// Adiciona o projétil à lista de projéteis
	projectiles.push_back(proj);

	Projetil& novoProjetil = projectiles.back();
	// Define a velocidade do projétil

	switch (direcaoSecundario)
	{
	case CIMA:
		novoProjetil.x_velocity = 0;
		novoProjetil.y_velocity = -5;
		break;
	case BAIXO:
		novoProjetil.x_velocity = 0;
		novoProjetil.y_velocity = 5;
		break;
	case DIREITA:
		novoProjetil.x_velocity = 5;
		novoProjetil.y_velocity = 0;
		break;
	case ESQUERDA:
		novoProjetil.x_velocity = -5;
		novoProjetil.y_velocity = 0;
		break;
	}
}

void atirarTiroPersonagemSecundario() {
	// Carrega a imagem do projétil
	ALLEGRO_BITMAP* imagemProj = al_load_bitmap("Assets/pilula_8bit.png");
	if (!imagemProj) {
		al_show_native_message_box(telaGame, "ERRO", "Falha ao carregar a imagem", "Não foi possível carregar a imagem do projétil.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return; // Sai da função se a imagem não puder ser carregada
	}

	// Cria um novo projétil na posição do jogador
	Projetil proj = Projetil(playerSecundario.__posicao.__posicao_x, playerSecundario.__posicao.__posicao_y + 32, 5, 0, imagemProj);
	// Adiciona o projétil à lista de projéteis
	projectiles.push_back(proj);

	Projetil& novoProjetil = projectiles.back();
	// Define a velocidade do projétil

	switch (direcao)
	{
	case CIMA:
		novoProjetil.x_velocity = 0;
		novoProjetil.y_velocity = -5;
		break;
	case BAIXO:
		novoProjetil.x_velocity = 0;
		novoProjetil.y_velocity = 5;
		break;
	case DIREITA:
		novoProjetil.x_velocity = 5;
		novoProjetil.y_velocity = 0;
		break;
	case ESQUERDA:
		novoProjetil.x_velocity = -5;
		novoProjetil.y_velocity = 0;
		break;
	}
}

void atualizarProjeteis() {
	for (auto& proj : projectiles) {
		// Atualiza a posição do projétil com base na sua velocidade
		proj.x += proj.x_velocity;
		proj.y += proj.y_velocity;
	}
}

void spawnarInimigos() {
	// Carrega a imagem do inimigo
	ALLEGRO_BITMAP* imagemInimigo = al_load_bitmap("Assets/inimigo.png");
	if (!imagemInimigo) {
		al_show_native_message_box(telaGame, "ERRO", "Falha ao carregar a imagem", "Não foi possível carregar a imagem do inimigo.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return; // Sai da função se a imagem não puder ser carregada
	}

	// Cria um novo inimigo em uma posição aleatória
	Inimigo inimigo = Inimigo(rand() % mapa.__largura__tela, rand() % mapa.__altura__tela, 2, 0, imagemInimigo);
	// Adiciona o inimigo à lista de inimigos
	float tempoAtual = al_get_time(); // Obtém o tempo atual
	if (tempoAtual - ultimoTempoInimigo > intervaloInimigo) {
		// Gera um novo inimigo
		inimigos.push_back(inimigo);

		ultimoTempoInimigo = tempoAtual; // Atualiza o tempo da última geração de inimigo
	}
}