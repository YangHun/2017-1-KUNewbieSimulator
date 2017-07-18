#include "ui.h"
#include "core.h"

void ui_set_button(object_t *o) {
	o->modifier.type = OBJECT_MODIFIER_BUTTON;
}

void ui_set_on_click_listener(object_t *o, void(*on_click)()) {
	o->modifier.value.button_value.on_click = on_click;
}

void ui_set_text(object_t *o, ALLEGRO_COLOR color, char* path, char* text, int font_size) {
	o->modifier.type = OBJECT_MODIFIER_FONT;
	o->modifier.value.font_value.font = al_load_font(path, font_size, 0);
	o->modifier.value.font_value.color = color;
	o->modifier.value.font_value.text = text;
}