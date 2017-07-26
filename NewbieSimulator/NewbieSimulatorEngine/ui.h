#pragma once
#include "core.h"

extern void ui_set_button(object_t *o);
extern void ui_set_on_click_listener(object_t *o, void(*on_click)());
extern void ui_set_text(object_t *o, ALLEGRO_COLOR color, char* path, int align, char* text, int font_size);
