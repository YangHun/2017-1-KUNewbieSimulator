#include "engine.h"

int scene_0_init() {

	//�ش� ���� ���۵� ��, �� �� �� ����Ǵ� �Լ�
	
	printf("Scene 0 start! \n");

	object_t bg = create_object("Resources\\dummy\\main.jpg", 0, 0);
	Background = bg;

	return 0;
}


int scene_0_update() {

	//Scene 0�� Main��
	//while�� �ȿ� �ִ� --> �� frame���� �����
	printf("Scene 0 act! \n");

	return 0;
}

int scene_0_fin() {

	// �� ������ �ٸ� ������ �Ѿ ��, �� �� ����Ǵ� �Լ�.


	return 0;
}


