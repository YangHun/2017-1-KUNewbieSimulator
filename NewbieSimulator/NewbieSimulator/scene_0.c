#include "engine.h"

static void on_click_button_0(object_t *o);

int scene_0_init() {

	//�ش� ���� ���۵� ��, �� �� �� ����Ǵ� �Լ�
	
	printf("Scene 0 start! \n");

	object_t bg = create_object("Resources\\dummy\\main.jpg", 0, 0);
	Background = bg;

	object_t hos = create_object("Resources\\dummy\\hos.png", 100, 100);
	ui_set_button(&hos);
	ui_set_on_click_listener(&hos, on_click_button_0);
	Stack.push(&Stack, hos);

	
	object_t scrollbar = create_object("Resources\\dummy\\scroller\\object.png", 150, 150);
	Stack.push(&Stack, scrollbar);
	object_t target = create_object("Resources\\dummy\\scroller\\target.png", 150, 150);
	Stack.push(&Stack, target);
	ui_set_scrollbar(&Stack.objs[1], &Stack.objs[2], "Resources\\dummy\\scroller\\b_top.png", 
		"Resources\\dummy\\scroller\\b_bot.png", al_map_rgb(255, 255, 255), al_map_rgb(0, 0, 0));
	
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

	printf("counter : %d \n", Stack.counter);

	return 0;
}

void on_click_button_0(object_t *o) {

	load_scene(Scenes.scenes[1]);

}

