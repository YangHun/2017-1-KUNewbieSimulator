#pragma once

#include <stdbool.h>
#include "engine.h"

#ifndef AUDIOSAMPLES_SZ
#define AUDIOSAMPLES_SZ 4
#endif

extern ALLEGRO_SAMPLE *AudioSamples[];

extern void init_audiosamples();
extern void fin_audiosamples();
extern void play_audiosample(size_t i, bool loop);
extern void stop_audiosample(size_t i);
