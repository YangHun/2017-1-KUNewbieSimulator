#include "engine.h"


int scene_3_init() {

	//�ش� ���� ���۵� ��, �� �� �� ����Ǵ� �Լ�

	printf("Scene 0 start! \n");

	object_t bg = create_object("Resources\\UI\\enroll_2\\background.jpg", 0, 0);
	Background = bg;

	return 0;
}


int scene_3_update() {

	//Scene 0�� Main��
	//while�� �ȿ� �ִ� --> �� frame���� �����
	printf("Scene 0 act! \n");
	re_draw();

	return 0;
}

int scene_3_fin() {

	// �� ������ �ٸ� ������ �Ѿ ��, �� �� ����Ǵ� �Լ�.
	Stack.clear(&Stack);

	printf("counter : %d \n", Stack.counter);

	return 0;
}



