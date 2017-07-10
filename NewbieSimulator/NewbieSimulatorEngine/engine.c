#include "core.h"
#include "engine.h"


#define FPS 60
#define SCREEN_W 1024
#define SCREEN_H 720
#define BOUNCER_SIZE 64

object_t Background;
ALLEGRO_EVENT ev;

int redraw = 0; //1일때마다 다시 그린다

void re_draw() {
	if(!redraw )
		redraw = 1;

}

static int engine() {

	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *bouncer = NULL;
	ALLEGRO_TIMEOUT timeout;

	if (!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}

	if (!al_init_image_addon()) {
		fprintf(stderr, "failed to initialize al_innit_image_addon!\n");
		return -1;
	}

	if (!al_install_mouse()) {
		fprintf(stderr, "failed to initialize the mouse!\n");
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

	event_queue = al_create_event_queue();
	if (!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_bitmap(bouncer);
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}

	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_mouse_event_source());

	al_init_timeout(&timeout, 0.1);

	//core initialization
	initialization();

//-------------------------


	while (1) {

		al_wait_for_event_until(event_queue, &ev, &timeout);

		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}

		engine_action(ev);
		
		if (redraw) {

			engine_draw();
			al_flip_display();
			redraw = 0;
		
		}
	}

//-------------------------

	end();

	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();
	
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);

	return 0;
}


void scene_manage() {

	// Plz add a new case when new scene is added
	if (current.isFirst) {
		if (!redraw) {
			redraw = 1;
		}
		current.init();
		current.isFirst = 0;
	}
	else {
		current.act();
	}
}

void load_scene(scene_t next) {
	current = next;
	current.isFirst = 1;
}

void engine_action(ALLEGRO_EVENT ev) {

	if (current.num >= 0) {
		
		//1. check scene and execute current scene
		scene_manage();
	
		if (prev.state_num >= 0) {
	
			//2. manage Game States; execute current state	
			state_manage(ev);			
		}
	
	}
}

ALLEGRO_EVENT catch_event() {
	return ev;
}

void engine_draw_background() {
	al_draw_bitmap(Background.image, 0 , 0, 0);
}

void engine_draw_objs() {
	
	int i = 0;
	for (i = 0; i < Stack.counter; i++) {
		object_t o = Stack.objs[i];
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

int game() {
	return engine();
}
