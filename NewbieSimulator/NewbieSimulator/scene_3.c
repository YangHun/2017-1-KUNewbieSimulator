#include "engine.h"


int scene_3_init() {

	//해당 씬이 시작될 때, 딱 한 번 실행되는 함수

	printf("Scene 0 start! \n");

	object_t bg = create_object("Resources\\UI\\enroll_2\\background.jpg", 0, 0);
	Background = bg;

	return 0;
}


int scene_3_update() {

	//Scene 0의 Main문
	//while문 안에 있다 --> 매 frame마다 실행됨
	printf("Scene 0 act! \n");
	re_draw();

	return 0;
}

int scene_3_fin() {

	// 이 씬에서 다른 씬으로 넘어갈 때, 한 번 실행되는 함수.
	Stack.clear(&Stack);

	printf("counter : %d \n", Stack.counter);

	return 0;
}



