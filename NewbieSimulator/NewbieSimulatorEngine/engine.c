#include "core.h"
#include "engine.h"


#define FPS 60
#define SCREEN_W 1024
#define SCREEN_H 720
#define BOUNCER_SIZE 64

object_t Background;
ALLEGRO_EVENT ev;

static positioni_t last_mouse_down_coord;
static positioni_t last_mouse_up_coord;

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

ALLEGRO_EVENT catch_event() {
	return ev;
}

void event_manage() {
	switch (catch_event().type) {
	
	case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN: {
		last_mouse_down_coord.x = catch_event().mouse.x;
		last_mouse_down_coord.y = catch_event().mouse.y;
		last_mouse_up_coord.x = -1;
		last_mouse_up_coord.y = -1; 
		break;
	}
	
	case ALLEGRO_EVENT_MOUSE_BUTTON_UP: {
		positioni_t cur_mouse_up_coord;

		cur_mouse_up_coord.x = catch_event().mouse.x;
		cur_mouse_up_coord.y = catch_event().mouse.y;

		if (positioni_equals(last_mouse_up_coord, cur_mouse_up_coord))
			break;
		
		for (int i = 0; i < Stack.counter; i++) {
			object_t *o = &(Stack.objs[i]);
			
			if (o->enable == true) {
				if (o->modifier.type == OBJECT_MODIFIER_BUTTON) {
					if (rect_contains_point(o->rect, last_mouse_down_coord) && rect_contains_point(o->rect, cur_mouse_up_coord)) {
						if (positionf_transparancy(o, last_mouse_down_coord) == true) {
							o->modifier.value.button_value.on_click();
						}
					}
				}
			}
		}
		
		last_mouse_up_coord.x = catch_event().mouse.x;
		last_mouse_up_coord.y = catch_event().mouse.y;

		break;
	}

	}
}

void scene_manage() {

	if (next_scene.num >= 0) {

		if (!current_scene.fin()) {
			current_scene = next_scene;
			next_scene = NULLSCENE;
		}
		else {
			printf("scene fin error, return");
			return;
		}
	}

	if (current_scene.isFirst) {
		if (!redraw) {
			redraw = 1;
		}
		current_scene.init();
		current_scene.isFirst = 0;
	}
	else {
		current_scene.act();
	}
}


void engine_action(ALLEGRO_EVENT ev) {

	if (current_scene.num >= 0) {
		
		// 0. check event and execute handler

		event_manage();

		//1. check scene and execute current scene
		scene_manage();
	
		if (prev.state_num >= 0) {
	
			//2. manage Game States; execute current state	
			state_manage(ev);			
		}
	
	}
}

void engine_draw_background() {
	al_draw_bitmap(Background.image, 0 , 0, 0);
}

void engine_draw_objs() {
	
	int i = 0;
	for (i = 0; i < Stack.counter; i++) {
		object_t* o = &(Stack.objs[i]);

		if (o->enable == true) {

			if (o->rotated == true) {
				al_draw_rotated_bitmap(o->image, (o->rect.width / 2.0), (o->rect.height / 2.0),
					o->pos.x + o->rect.width / 2, o->pos.y + o->rect.height / 2, o->angle, 0);
				o->rotated = false;
				if (o->angle >= 360.0) {
					o->angle -= 360.0f;
				}
			}
			else {
				//al_set_target_bitmap(o->image);
				//al_set_blender(ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA, ALLEGRO_ALPHA);
				al_draw_tinted_bitmap(o->image,al_map_rgba(1,1,1,o->opacity), o->pos.x, o->pos.y, 0);
			}
		}
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
