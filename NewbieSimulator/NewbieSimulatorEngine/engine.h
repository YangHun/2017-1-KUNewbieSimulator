#pragma once
#include <stdio.h>
#include <allegro5\allegro.h>
#include "core.h"

static int engine();

extern void state_manage(ALLEGRO_EVENT ev);
extern void start();
extern void end();

void engine_action(ALLEGRO_EVENT ev);
void engine_draw();
int game();

void re_draw();
void load_scene(scene_t next);
ALLEGRO_EVENT catch_event();

extern object_t Background;
extern ALLEGRO_EVENT ev;
