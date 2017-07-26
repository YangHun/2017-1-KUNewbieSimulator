#include "ui.h"
#include "core.h"

void ui_set_button(object_t *o) {
	o->modifier.type = OBJECT_MODIFIER_BUTTON;
}

void ui_set_on_click_listener(object_t *o, void(*on_click)()) {
	o->modifier.value.button_value.on_click = on_click;
}

void ui_set_text(object_t *o, ALLEGRO_COLOR color, char* path, int align, char* text, int font_size) {
	o->modifier.type = OBJECT_MODIFIER_FONT;
	o->modifier.value.font_value.font = al_load_font(path, font_size, 0);
	o->modifier.value.font_value.color = color;
	o->modifier.value.font_value.text = text;
	o->modifier.value.font_value.align = align;
}

void ui_set_scrollbar(object_t *o, object_t *target, char *b_top_path, char *b_bot_path, ALLEGRO_COLOR body_color, ALLEGRO_COLOR thumb_color) {
	// set 'vertical' scrollbar
	// o : scrollbar object
	// target : target which to be scrolled
	// button_top, bot : button in this scrollbar
	// buttons must be square.

	object_t *mbody = malloc(sizeof(object_t));
	object_t *mbtop = malloc(sizeof(object_t));
	object_t *mbbot = malloc(sizeof(object_t));
	object_t *mthumb = malloc(sizeof(object_t));
	int button_size;
	int thumb_size = 0;

	o->modifier.type = OBJECT_MODIFIER_SCROLLBAR;
	o->modifier.value.scrollbar.target = target;

	(o->modifier.value.scrollbar.target) = target;

	*mbtop = create_object(b_top_path, mbody->pos.x, mbody->pos.y);
	button_size = mbtop->rect.width;
	o->modifier.value.scrollbar.button_top = mbtop; //it must be free();

	*mbbot = create_object(b_bot_path, mbody->pos.x, mbody->pos.y);;
	o->modifier.value.scrollbar.button_bottom = mbbot; //it must be free();

	*mbody = (create_colored_object(body_color, button_size, o->rect.height, o->rect.top, o->rect.left + o->rect.width - button_size));
	o->modifier.value.scrollbar.body = mbody; //it must be free();
		
	if (target->rect.height > o->rect.height) {
		thumb_size = (int)(o->rect.height / target->rect.height * o->rect.height);
	}
	*mthumb = create_colored_object(thumb_color, button_size, thumb_size, mbody->rect.top, mbody->rect.left);
	o->modifier.value.scrollbar.thumb = mthumb; //it must be free();
}

