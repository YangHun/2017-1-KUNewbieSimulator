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
	printf("Scene 0 act! \n");


	//return 되는 때가 해당 scene이 끝날 때
	return 0;
}

int transition_scene_0() {

	// 이 씬에서 다른 씬으로 넘어갈 때, 한 번 실행되는 함수.


	return 0;
}


