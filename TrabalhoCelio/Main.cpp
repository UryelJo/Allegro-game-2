#include "Entidade.h"
#include "Mapa.h"

//Include das bibliotecas do Allegro
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_native_dialog.h>


ALLEGRO_DISPLAY* telaGame = NULL;
ALLEGRO_TIMER* fps = NULL;
ALLEGRO_EVENT_QUEUE* filaEventos = NULL;

Entidade playerPrimario = Entidade();
Entidade playerSecundario = Entidade();
Mapa mapa = Mapa();

void inicializacao();
void atualizarLimparDesenhar();
void colisao(int larguraMapa, int alturaMapa);
void encerramento();

int main() {
	inicializacao();
	al_clear_to_color(al_map_rgb(200, 200, 200));
	al_flip_display();

	al_start_timer(fps);

	while (true) {
		ALLEGRO_EVENT evento;
		al_wait_for_event(filaEventos, &evento);

		if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
			break;
		}

		if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (evento.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				playerPrimario.__movesetEntidade.__movendo_baixo = true;
				break;
			case ALLEGRO_KEY_DOWN:
				playerPrimario.__movesetEntidade.__movendo_cima = true;
				break;
			case ALLEGRO_KEY_LEFT:
				playerPrimario.__movesetEntidade.__movendo_esquerda = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				playerPrimario.__movesetEntidade.__movendo_direita = true;
				break;
			case ALLEGRO_KEY_W:
				playerSecundario.__movesetEntidade.__movendo_baixo = true;
				break;
			case ALLEGRO_KEY_S:
				playerSecundario.__movesetEntidade.__movendo_cima = true;
				break;
			case ALLEGRO_KEY_A:
				playerSecundario.__movesetEntidade.__movendo_esquerda = true;
				break;
			case ALLEGRO_KEY_D:
				playerSecundario.__movesetEntidade.__movendo_direita = true;
				break;
			}
		}

		//Movimentação do Player
		playerPrimario.movimentacaoEntidade();
		playerSecundario.movimentacaoEntidade();
		colisao(mapa.__largura__tela, mapa.__altura__tela);


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

		atualizarLimparDesenhar();

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

	playerPrimario.carregarImagemEntidade("Assets/teste.png");
	playerSecundario.carregarImagemEntidade("Assets/teste.png");

}

void atualizarLimparDesenhar() {
	al_clear_to_color(al_map_rgb(255, 255, 255));
	al_draw_bitmap_region(playerPrimario.__imagemEntidade, 0, 0, 32, 32, playerPrimario.posicao.__posicao_x, playerPrimario.posicao.__posicao_y, 0);
	al_draw_bitmap_region(playerSecundario.__imagemEntidade, 0, 0, 32, 32, playerSecundario.posicao.__posicao_x, playerSecundario.posicao.__posicao_y, 0);
	al_flip_display();
}

void colisao(int larguraMapa, int alturaMapa) {
	if (playerPrimario.posicao.__posicao_x + 32 > mapa.__largura__tela) {
		playerPrimario.posicao.__posicao_x = mapa.__largura__tela - 32;
	}
	if (playerPrimario.posicao.__posicao_x < 0) {
		playerPrimario.posicao.__posicao_x = 0;
	}
	if (playerPrimario.posicao.__posicao_y + 32 > mapa.__altura__tela) {
		playerPrimario.posicao.__posicao_y = mapa.__altura__tela - 32;
	}
	if (playerPrimario.posicao.__posicao_y < 0) {
		playerPrimario.posicao.__posicao_y = 0;
	}

	if (playerSecundario.posicao.__posicao_x + 32 > mapa.__largura__tela) {
		playerSecundario.posicao.__posicao_x = mapa.__largura__tela - 32;
	}
	if (playerSecundario.posicao.__posicao_x < 0) {
		playerSecundario.posicao.__posicao_x = 0;
	}
	if (playerSecundario.posicao.__posicao_y + 32 > mapa.__altura__tela) {
		playerSecundario.posicao.__posicao_y = mapa.__altura__tela - 32;
	}
	if (playerSecundario.posicao.__posicao_y < 0) {
		playerSecundario.posicao.__posicao_y = 0;
	}
}

void encerramento() {
	al_destroy_display(telaGame);
	al_destroy_bitmap(playerPrimario.__imagemEntidade);
	al_destroy_bitmap(playerSecundario.__imagemEntidade);
	al_destroy_timer(fps);
	al_destroy_event_queue(filaEventos);
}