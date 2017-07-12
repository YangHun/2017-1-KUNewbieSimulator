#include "ui.h"
#include "core.h"

void ui_set_button(object_t *o) {
	o->modifier.type = OBJECT_MODIFIER_BUTTON;
}

void ui_set_on_click_listener(object_t *o, void(*on_click)()) {
	o->modifier.value.button_value.on_click = on_click;
}
