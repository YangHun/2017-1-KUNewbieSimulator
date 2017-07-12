#include "engine.h"

static void on_click_button_0();

int scene_0_init() {

	//�ش� ���� ���۵� ��, �� �� �� ����Ǵ� �Լ�
	
	printf("Scene 0 start! \n");

	object_t bg = create_object("Resources\\dummy\\main.jpg", 0, 0);
	Background = bg;

	object_t hos = create_object("Resources\\dummy\\hos.png", 100, 100);
	ui_set_button(&hos);
	ui_set_on_click_listener(&hos, on_click_button_0);
	Stack.push(&Stack, hos);

	return 0;
}

#define HOSBUTTON Stack.objs[0]

int scene_0_update() {

	//Scene 0�� Main��
	//while�� �ȿ� �ִ� --> �� frame���� �����
	printf("Scene 0 act! \n");
	rotate_object(&HOSBUTTON, 0.005f);
	re_draw();

	return 0;
}

int scene_0_fin() {

	// �� ������ �ٸ� ������ �Ѿ ��, �� �� ����Ǵ� �Լ�.
	Stack.clear(&Stack);

	return 0;
}

void on_click_button_0() {

	load_scene(Scenes.scenes[1]);

}

