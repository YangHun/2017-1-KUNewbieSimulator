#include "engine.h"

int init_scene_1(){

	//�ش� ���� ���۵� ��, �� �� �� ����Ǵ� �Լ�
	printf("Scene 1 start!");

	Object bg = SetObject("Resources\\dummy\\tutorial.jpg", 0, 0);
	Background = bg;
	

	return 0;
}


int main_scene_1() {

	//Scene 1�� Main��
	//while�� �ȿ� �ִ� --> �� frame���� �����
	printf("Scene 1 act! \n");


	return 0;
}


int transition_scene_1() {

	// �� ������ �ٸ� ������ �Ѿ ��, �� �� ����Ǵ� �Լ�.




	return 0;
}