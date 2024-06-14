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

Entidade playerPrimario = Entidade(32, 32, 0, 0);
Entidade playerSecundario = Entidade(32, 32, 0, 0);
Mapa mapa = Mapa();

void inicializacao();
void atualizarLimparDesenhar();
void encerramento();

int main() {
	inicializacao();
	al_clear_to_color(al_map_rgb(0, 0, 0));
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
			playerPrimario.movimentacaoEntidade();
			playerSecundario.movimentacaoEntidade();
			playerPrimario.colisaoPersonagem(mapa.__largura__tela, mapa.__altura__tela);
			playerSecundario.colisaoPersonagem(mapa.__largura__tela, mapa.__altura__tela);

			atualizarLimparDesenhar();

			desenhar = false;
		}

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
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_bitmap_region(playerPrimario.__imagemEntidade, playerPrimario.frame.__frame_x, playerPrimario.frame.__frame_y, playerPrimario.tamanho.__largura, playerPrimario.tamanho.__altura, playerPrimario.posicao.__posicao_x, playerPrimario.posicao.__posicao_y, 0);
	al_draw_bitmap_region(playerSecundario.__imagemEntidade, playerSecundario.frame.__frame_x, playerSecundario.frame.__frame_y, playerSecundario.tamanho.__largura, playerSecundario.tamanho.__altura, playerSecundario.posicao.__posicao_x, playerSecundario.posicao.__posicao_y, 0);
	al_flip_display();
}

void encerramento() {
	al_destroy_display(telaGame);
	al_destroy_bitmap(playerPrimario.__imagemEntidade);
	al_destroy_bitmap(playerSecundario.__imagemEntidade);
	al_destroy_timer(fps);
	al_destroy_event_queue(filaEventos);
}