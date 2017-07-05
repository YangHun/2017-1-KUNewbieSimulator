#pragma once
#include <stdio.h>
#include <allegro5\allegro.h>
#include "core.h"

static int engine();

int register_scenes(int n);
void engine_action(ALLEGRO_EVENT ev);
void engine_draw();
int start();

Object Background;
