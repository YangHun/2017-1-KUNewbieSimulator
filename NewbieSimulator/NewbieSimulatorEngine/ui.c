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

void ui_set_scrollbar(object_t *o, object_t *target, ALLEGRO_COLOR bar_color, int button_size ) {
	o->modifier.type = OBJECT_MODIFIER_SCROLLER;
/*	o->modifier.value.scroller.target = target;

	*(o->modifier.value.scroller.bar) = (create_colored_object(bar_color, button_size, o->rect.height, o->rect.top + o->rect.width - button_size, o->rect.left));
	*/


}

