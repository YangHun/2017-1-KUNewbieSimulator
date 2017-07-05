#include "engine.h"

int init_scene_0() {

	//해당 씬이 시작될 때, 딱 한 번 실행되는 함수
	
	printf("Scene 0 start! \n");

	Object bg = SetObject("Resources\\dummy\\main.jpg", 0, 0);
	Background = bg;

	return 0;
}


int main_scene_0() {

	//Scene 0의 Main문
	//while문 안에 있다 --> 매 frame마다 실행됨
	printf("Scene 0 act! \n");

	//transition
	// if mouse clicked, change scene 0 --> 1
	if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {

		printf("mouse click \n");

		transition_scene_0();
		current = Scenes.scenes[1];
	}

	return 0;
}

int transition_scene_0() {

	// 이 씬에서 다른 씬으로 넘어갈 때, 한 번 실행되는 함수.


	return 0;
}


