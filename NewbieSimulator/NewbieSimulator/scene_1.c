#include "engine.h"

int scene_1_init(){

	//�ش� ���� ���۵� ��, �� �� �� ����Ǵ� �Լ�
	printf("Scene 1 start!");

	object_t bg = create_object("Resources\\dummy\\tutorial.jpg", 0, 0);
	Background = bg;
	

	return 0;
}


int scene_1_update() {

	//Scene 1�� Main��
	//while�� �ȿ� �ִ� --> �� frame���� �����
	printf("Scene 1 act! \n");


	return 0;
}


int scene_1_fin() {

	// �� ������ �ٸ� ������ �Ѿ ��, �� �� ����Ǵ� �Լ�.




	return 0;
}