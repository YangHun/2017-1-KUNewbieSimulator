#include "engine.h"

static void on_click_button_0(object_t *o);

int scene_0_init() {

	//해당 씬이 시작될 때, 딱 한 번 실행되는 함수

	object_t bg = create_object("Resources\\dummy\\main.jpg", 0, 0);
	Background = bg;
	
//	object_t scrollbar = create_object("Resources\\dummy\\scroller\\object.png", 150, 150);
//	Stack.push(&Stack, scrollbar);
//	object_t target = create_object("Resources\\dummy\\scroller\\target.png", 150, 150);
//	Stack.push(&Stack, target);
//	ui_set_scrollbar(&Stack.objs[1], &Stack.objs[2], "Resources\\dummy\\scroller\\b_top.png", 
//		"Resources\\dummy\\scroller\\b_bot.png", al_map_rgb(255, 255, 255), al_map_rgb(0, 0, 0));
	
	return 0;
}

#define HOSBUTTON Stack.objs[0]

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

	load_scene(Scenes.scenes[1]);

}

