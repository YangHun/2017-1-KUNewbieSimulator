#include "engine.h"
#include "core.h"

#define FPS 60
#define SCREEN_W 1280
#define SCREEN_H 720
#define BOUNCER_SIZE 64

void engine_action();
void engine_draw();
int start();

static int engine() {

	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *bouncer = NULL;

	if (!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}

	if (!al_init_image_addon()) {
		fprintf(stderr, "failed to initialize al_innit_image_addon!\n");
		return -1;
	}

	timer = al_create_timer(1.0 / FPS);
	if (!timer) {
		fprintf(stderr, "failed to create timer!\n");
		return -1;
	}

	display = al_create_display(SCREEN_W, SCREEN_H);
	if (!display) {
		fprintf(stderr, "failed to create display!\n");
		al_destroy_timer(timer);
		return -1;
	}

	bouncer = al_create_bitmap(BOUNCER_SIZE, BOUNCER_SIZE);
	if (!bouncer) {
		fprintf(stderr, "failed to create bouncer bitmap!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}

//-------------------------
	
	while (1) {

	//	engine_action();
	//	engine_draw();
		al_flip_display();

	}

//-------------------------

	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_flip_display();

	al_rest(10.0);

	al_destroy_display(display);

	return 0;
}

void engine_action() {
	// 매 프레임마다 호출된다
}

void engine_draw_background() {
	al_clear_to_color(al_map_rgb(0, 0, 0));
}

void engine_draw_objs() {
	int i = 0;
	for (i = 0; i < Stack.counter; i++) {
		Object o = Stack.objs[i];
		al_draw_bitmap(o.image, o.pos.x, o.pos.y, 0);
	}
}

void engine_draw_UI() {
	//TODO : UI Drawing
}

void engine_draw() {
	engine_draw_background();
	engine_draw_objs();
	engine_draw_UI();
}

int start() {
	return engine();
}

int main() {
	return start();
}