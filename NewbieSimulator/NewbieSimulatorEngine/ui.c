#include "ui.h"
#include "core.h"

void ui_set_button(object_t *o) {
	o->modifier.type = OBJECT_MODIFIER_BUTTON;
}

void ui_set_on_click_listener(object_t *o, on_click_listener_t listener) {
	o->modifier.value.button_value.on_click_listener = listener;
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

	int button_size = al_get_bitmap_width(al_load_bitmap(b_top_path));
	int thumb_size = 0;

	object_t mbody = create_colored_object(body_color, button_size, o->rect.height, o->rect.top, o->rect.left + o->rect.width - button_size);
	object_t mbtop = create_object(b_top_path, mbody.pos.x, mbody.pos.y);
	object_t mbbot = create_object(b_bot_path, mbody.pos.x, mbody.pos.y + o->rect.height - button_size);
	object_t mthumb;

	//al_set_clipping_rectangle(o->pos.x, o->pos.y, o->rect.width, o->rect.height);

	o->modifier.type = OBJECT_MODIFIER_SCROLLBAR;
	o->modifier.value.scrollbar.target = target;

	target->modifier.type = OBJECT_MODIFIER_SCROLLBAR_CHILD;
	(o->modifier.value.scrollbar.target) = target;

	mbody.modifier.type = OBJECT_MODIFIER_SCROLLBAR_CHILD;
	Stack.push(&Stack, mbody);
	o->modifier.value.scrollbar.body = &Stack.objs[Stack.counter - 1]; 

	mbtop.modifier.type = OBJECT_MODIFIER_SCROLLBAR_CHILD;
	Stack.push(&Stack, mbtop);
	o->modifier.value.scrollbar.button_top = &Stack.objs[Stack.counter - 1];

	mbbot.modifier.type = OBJECT_MODIFIER_SCROLLBAR_CHILD;
	Stack.push(&Stack, mbbot);
	o->modifier.value.scrollbar.button_bottom = &Stack.objs[Stack.counter - 1]; //it must be free();
	
	//printf("enter\n");

	if (target->rect.height > o->rect.height) {

		thumb_size = (int)(((float)o->rect.height / (float)target->rect.height * ((float)o->rect.height - (float)button_size * 2.0)));
	}

	

	mthumb.modifier.type = OBJECT_MODIFIER_SCROLLBAR_CHILD;
	mthumb = create_colored_object(thumb_color, button_size, thumb_size, mbody.rect.top + button_size, mbody.rect.left);
	Stack.push(&Stack, mthumb);
	o->modifier.value.scrollbar.thumb = &Stack.objs[Stack.counter - 1];


}

