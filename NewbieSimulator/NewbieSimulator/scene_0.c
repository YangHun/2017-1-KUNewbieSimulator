#include "engine.h"

int init_scene_0() {

	//�ش� ���� ���۵� ��, �� �� �� ����Ǵ� �Լ�
	
	printf("Scene 0 start! \n");

	Object bg = SetObject("Resources\\dummy\\main.jpg", 0, 0);
	Background = bg;

	return 0;
}


int main_scene_0() {

	//Scene 0�� Main��
	//while�� �ȿ� �ִ� --> �� frame���� �����
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

	// �� ������ �ٸ� ������ �Ѿ ��, �� �� ����Ǵ� �Լ�.


	return 0;
}


