#include "core.h"
#include "engine.h"
#include "game.h"


#define FPS 60
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

	if (!al_init_font_addon()) {
		fprintf(stderr, "failed to initialize the font!\n");
		return -1;
	}
	if (!al_init_ttf_addon()) {
		fprintf(stderr, "failed to initialize the ttf!\n");
		return -1;
	}
	if (!al_init_primitives_addon()) {
		fprintf(stderr, "failed to initialize the primitives addon!\n");
		return -1;
	}
	if (!al_install_audio()) {
		printf("failed to initialize audio!\n");
		return -1;
	}
	if (!al_init_acodec_addon()) {
		printf("failed to initialize audio codecs!\n");
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

	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();
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

		int last_match_index = -1;
		
		for (int i = 0; i < Stack.counter; i++) {
			object_t *o = &(Stack.objs[i]);
			
			if (o->enable == true) {
				if (o->blocks) {
					if (rect_contains_point(o->rect, last_mouse_down_coord) && rect_contains_point(o->rect, cur_mouse_up_coord)) {
						if (positionf_transparancy(o, last_mouse_down_coord) == true) {
							last_match_index = i;
						}
					}
				}
			}
		}

		if (last_match_index != -1) {
			object_t *o = &(Stack.objs[last_match_index]);
			if (o->modifier.type == OBJECT_MODIFIER_BUTTON&& o->modifier.value.button_value.on_click_listener != NULL) {
			o->modifier.value.button_value.on_click_listener(o);
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
			al_clear_to_color(al_map_rgb(0,0,0));
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
	
//	printf("enter");

	int i = 0;
	for (i = 0; i < Stack.counter; i++) {
		object_t* o = &(Stack.objs[i]);

		if (o->enable == true) {

			if (o->modifier.type == OBJECT_MODIFIER_FONT) {
				al_draw_text(o->modifier.value.font_value.font, o->modifier.value.font_value.color, o->pos.x, o->pos.y, o->modifier.value.font_value.align, o->modifier.value.font_value.text);
			}
			else if (o->modifier.type == OBJECT_MODIFIER_SCROLLBAR) {
				object_t* target = o->modifier.value.scrollbar.target;
				object_t* body = o->modifier.value.scrollbar.body;
				object_t* btop = o->modifier.value.scrollbar.button_top;
				object_t* bbot = o->modifier.value.scrollbar.button_bottom;
				object_t* thumb = o->modifier.value.scrollbar.thumb;
				
				al_draw_tinted_bitmap(target->image, al_map_rgba_f(1.0, 1.0, 1.0, 1.0), target->pos.x, target->pos.y, 0);
				al_draw_filled_rectangle(body->pos.x, body->pos.y, body->pos.x + body->rect.width, body->pos.y + body->rect.height, body->color);
				al_draw_tinted_bitmap(btop->image, al_map_rgba_f(1.0, 1.0, 1.0, 1.0), btop->pos.x, btop->pos.y, 0);
				al_draw_tinted_bitmap(bbot->image, al_map_rgba_f(1.0, 1.0, 1.0, 1.0), bbot->pos.x, bbot->pos.y, 0);
				al_draw_filled_rectangle(thumb->pos.x, thumb->pos.y, thumb->pos.x + thumb->rect.width, thumb->pos.y + thumb->rect.height, thumb->color);

			}
			else if (o->modifier.type == OBJECT_MODIFIER_SCROLLBAR_CHILD) {
				// do nothing
			}
			else if (o->modifier.type == OBJECT_MODIFIER_LINE) {
				float x1, x2, y1, y2, t;
				x1 = o->modifier.value.line.x1;
				y1 = o->modifier.value.line.y1;
				x2 = o->modifier.value.line.x2;
				y2 = o->modifier.value.line.y2;
				t = o->modifier.value.line.thickness;

				al_draw_line(x1, y1, x2, y2, o->color, t);
			}
			else{
				if (o->image == NULL) {
					al_draw_filled_rectangle(o->pos.x, o->pos.y, o->pos.x + o->rect.width, o->pos.y + o->rect.height, o->color);
				}
				else if (o->rotated) {
					al_draw_rotated_bitmap(o->image, (o->rect.width / 2.0), (o->rect.height / 2.0),
						o->pos.x + o->rect.width / 2, o->pos.y + o->rect.height / 2, o->angle, 0);
					o->rotated = false;
					if (o->angle >= 360.0) {
						o->angle -= 360.0f;
					}
				}
				else {
					al_draw_tinted_bitmap(o->image, al_map_rgba_f(1, 1, 1, o->opacity), o->pos.x, o->pos.y, 0);
				}
				//al_set_target_bitmap(o->image);
				//al_set_blender(ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA, ALLEGRO_ALPHA);
				//al_draw_bitmap(o->image, o->pos.x, o->pos.y, 0);
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
