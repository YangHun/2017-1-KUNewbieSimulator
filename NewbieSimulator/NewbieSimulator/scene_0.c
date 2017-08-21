#include "engine.h"
#include "audio.h"

static void on_click_button_0(object_t *o);

int scene_0_init() {

	//해당 씬이 시작될 때, 딱 한 번 실행되는 함수

	object_t bg = create_object("Resources\\dummy\\main.jpg", 0, 0);
	Background = bg;

	object_t button = create_object("Resources\\UI\\splash\\start_button.png", 1117, 567);
	ui_set_button(&button);
	ui_set_on_click_listener(&button, on_click_button_0);
	Stack.push(&Stack, button);
	
//	object_t scrollbar = create_object("Resources\\dummy\\scroller\\object.png", 150, 150);
//	Stack.push(&Stack, scrollbar);
//	object_t target = create_object("Resources\\dummy\\scroller\\target.png", 150, 150);
//	Stack.push(&Stack, target);
//	ui_set_scrollbar(&Stack.objs[1], &Stack.objs[2], "Resources\\dummy\\scroller\\b_top.png", 
//		"Resources\\dummy\\scroller\\b_bot.png", al_map_rgb(255, 255, 255), al_map_rgb(0, 0, 0));

	play_audiosample(2, true);

	return 0;
}

int scene_0_update() {

	return 0;
}

int scene_0_fin() {

	// 이 씬에서 다른 씬으로 넘어갈 때, 한 번 실행되는 함수.

	Stack.clear(&Stack);

	printf("counter : %d \n", Stack.counter);

	return 0;
}

void on_click_button_0(object_t *o) {

	play_audiosample(0, false);
	load_scene(Scenes.scenes[1]);

}

