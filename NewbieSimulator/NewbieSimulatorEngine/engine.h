#pragma once
#include <stdio.h>
#include "core.h"
#include "ui.h"

static int engine();

extern void state_manage(ALLEGRO_EVENT ev);
extern void start();
extern void end();

void engine_action(ALLEGRO_EVENT ev);
void engine_draw();
int game();

void re_draw();
ALLEGRO_EVENT catch_event();

extern object_t Background;
extern ALLEGRO_EVENT ev;
