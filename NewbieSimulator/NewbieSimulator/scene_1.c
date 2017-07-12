#include "engine.h"

object_t *hos;

int scene_1_init(){

	//해당 씬이 시작될 때, 딱 한 번 실행되는 함수
	printf("Scene 1 start!");

	object_t bg = create_object("Resources\\dummy\\tutorial.jpg", 0, 0);
	Background = bg;
	
	Stack.push(&Stack, create_object("Resources\\dummy\\hos.png", 100, 100));

	hos = &Stack.objs[0];

	return 0;
}


int scene_1_update() {

	//Scene 1의 Main문
	//while문 안에 있다 --> 매 frame마다 실행됨
	printf("Scene 1 act! \n");

	hos->pos.x++;
	re_draw();

	return 0;
}


int scene_1_fin() {

	// 이 씬에서 다른 씬으로 넘어갈 때, 한 번 실행되는 함수.




	return 0;
}