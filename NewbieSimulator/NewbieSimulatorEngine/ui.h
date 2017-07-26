#pragma once
#include "core.h"

extern void ui_set_button(object_t *o);
extern void ui_set_on_click_listener(object_t *o, void(*on_click)());
extern void ui_set_text(object_t *o, ALLEGRO_COLOR color, char* path, int align, char* text, int font_size);

void ui_set_scrollbar(object_t *o, object_t *target, char *b_top_path, char *b_bot_path, ALLEGRO_COLOR body_color, ALLEGRO_COLOR thumb_color);