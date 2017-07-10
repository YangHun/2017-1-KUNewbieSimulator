#include "engine.h"

static void on_click_button_0();

int scene_0_init() {

	//해당 씬이 시작될 때, 딱 한 번 실행되는 함수
	
	printf("Scene 0 start! \n");

	object_t bg = create_object("Resources\\dummy\\main.jpg", 0, 0);
	Background = bg;

	object_t hos = create_object("Resources\\dummy\\hos.png", 100, 100);
	ui_set_button(&hos);
	ui_set_on_click_listener(&hos, on_click_button_0);
	Stack.push(&Stack, hos);

	return 0;
}


int scene_0_update() {

	//Scene 0의 Main문
	//while문 안에 있다 --> 매 frame마다 실행됨
	printf("Scene 0 act! \n");

	return 0;
}

int scene_0_fin() {

	// 이 씬에서 다른 씬으로 넘어갈 때, 한 번 실행되는 함수.


	return 0;
}

void on_click_button_0() {

	current = Scenes.scenes[1];

}

