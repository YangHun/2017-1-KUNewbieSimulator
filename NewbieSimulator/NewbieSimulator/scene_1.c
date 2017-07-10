#include "engine.h"

object_t *hos;

static void scene_1_on_click_button_0();

int scene_1_init(){

	//해당 씬이 시작될 때, 딱 한 번 실행되는 함수
	printf("Scene 1 start!");

	object_t bg = create_object("Resources\\dummy\\tutorial.jpg", 0, 0);
	Background = bg;
	
	object_t hos = create_object("Resources\\dummy\\hos.png", 200, 200);
	ui_set_button(&hos);
	ui_set_on_click_listener(&hos, scene_1_on_click_button_0);
	Stack.push(&Stack, hos);

	return 0;
}


int scene_1_update() {

	//Scene 1의 Main문
	//while문 안에 있다 --> 매 frame마다 실행됨

	re_draw();

	return 0;
}


int scene_1_fin() {

	// 이 씬에서 다른 씬으로 넘어갈 때, 한 번 실행되는 함수.




	return 0;
}

void scene_1_on_click_button_0() {

	puts("clicked");

}