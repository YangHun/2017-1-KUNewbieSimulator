#include "engine.h"

object_t *hos;

int scene_1_init(){

	//�ش� ���� ���۵� ��, �� �� �� ����Ǵ� �Լ�
	printf("Scene 1 start!");

	object_t bg = create_object("Resources\\dummy\\tutorial.jpg", 0, 0);
	Background = bg;
	
	Stack.push(&Stack, create_object("Resources\\dummy\\hos.png", 100, 100));

	hos = &Stack.objs[0];

	return 0;
}


int scene_1_update() {

	//Scene 1�� Main��
	//while�� �ȿ� �ִ� --> �� frame���� �����
	printf("Scene 1 act! \n");

	hos->pos.x++;
	re_draw();

	return 0;
}


int scene_1_fin() {

	// �� ������ �ٸ� ������ �Ѿ ��, �� �� ����Ǵ� �Լ�.




	return 0;
}