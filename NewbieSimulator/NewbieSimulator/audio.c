#include "audio.h"

ALLEGRO_SAMPLE *AudioSamples[AUDIOSAMPLES_SZ] = { NULL, };
static ALLEGRO_SAMPLE_ID AudioSamples_ID[AUDIOSAMPLES_SZ];
static bool AudioSamples_isPlaying[AUDIOSAMPLES_SZ] = { false, };
static float AudioSamples_Gain[AUDIOSAMPLES_SZ] = { 1.0, };

void init_audiosamples() {
	if (!al_reserve_samples(AUDIOSAMPLES_SZ)) {
		fprintf(stderr, "failed to reserve samples!\n");
	}
	else {
		AudioSamples[0] = al_load_sample("Resources\\sound\\click.ogg");
		AudioSamples_Gain[0] = 5.0;
		AudioSamples[1] = al_load_sample("Resources\\sound\\clock.ogg");
		AudioSamples_Gain[1] = 2.0;
		AudioSamples[2] = al_load_sample("Resources\\sound\\theme1.ogg");
		AudioSamples_Gain[2] = 1.0;
		AudioSamples[3] = al_load_sample("Resources\\sound\\theme2.ogg");
		AudioSamples_Gain[3] = 3.0;
	}
}

void fin_audiosamples() {
	for (size_t i = 0; i < AUDIOSAMPLES_SZ; i++) {
		al_destroy_sample(AudioSamples[i]);
	}
}

void play_audiosample(size_t i, bool loop) {
	if (loop) {
		if (!AudioSamples_isPlaying[i]) {
			al_play_sample(AudioSamples[i], AudioSamples_Gain[i], 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &AudioSamples_ID[i]);
			AudioSamples_isPlaying[i] = true;
		}
	}
	else {
		if (AudioSamples_isPlaying[i]) {
			stop_audiosample(i);
		}
		al_play_sample(AudioSamples[i], AudioSamples_Gain[i], 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &AudioSamples_ID[i]);
	}
}

void stop_audiosample(size_t i) {
	al_stop_sample(&AudioSamples_ID[i]);
}
