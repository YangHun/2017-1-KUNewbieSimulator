#include "engine.h"

void selected1();
void selected2();
bool ongoing1 = false, ongoing2 = false;

int scene_4_init() {

	//�ش� ���� ���۵� ��, �� �� �� ����Ǵ� �Լ�

	printf("Scene 4 start! \n");

	object_t map = create_object("Resources\\UI\\routegame\\campus_map.jpg", 0, 0);
	Background = map;

	object_t player = create_object("Resources\\UI\\routegame\\character.png", 100, 100);
	Stack.push(&Stack, player);
#define CHARACTER 1

	return 0;
}

int scene_4_update() {

	//Scene 0�� Main��
	//while�� �ȿ� �ִ� --> �� frame���� �����
	printf("Scene 4 act! \n");

	object_t route1 = create_object("Resources\\UI\\routegame\\route1.png", 100, 200);
	ui_set_button(&route1);
	ui_set_on_click_listener(&route1, selected1);
	Stack.push(&Stack, route1);
	object_t route2 = create_object("Resources\\UI\\routegame\\route2.png", 200, 300);
	ui_set_button(&route2);
	ui_set_on_click_listener(&route2, selected2);
	Stack.push(&Stack, route2);

	re_draw();

	return 0;
}

int scene_4_fin() {

	// �� ������ �ٸ� ������ �Ѿ ��, �� �� ����Ǵ� �Լ�.
	Stack.clear(&Stack);

	printf("counter : %d \n", Stack.counter);

	return 0;
}

void selected1()
{
	ongoing1 = true;
}

void selected2()
{
	ongoing2 = true;
}