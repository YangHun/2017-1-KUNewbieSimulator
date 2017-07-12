#include "engine.h"

object_t *hos;

static void scene_1_on_click_button_0();

int scene_1_init(){

	//�ش� ���� ���۵� ��, �� �� �� ����Ǵ� �Լ�
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

	//Scene 1�� Main��
	//while�� �ȿ� �ִ� --> �� frame���� �����

	re_draw();

	return 0;
}


int scene_1_fin() {

	// �� ������ �ٸ� ������ �Ѿ ��, �� �� ����Ǵ� �Լ�.




	return 0;
}

void scene_1_on_click_button_0() {

	puts("clicked");

}