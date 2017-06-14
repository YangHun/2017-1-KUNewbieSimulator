#pragma once
#include <stdio.h>
#include <Windows.h>
#include <allegro5\allegro.h>

typedef struct tag_position {
	float x, y;
}Position;

typedef struct tag_object {

	ALLEGRO_BITMAP *image;
	float width, height;
	Position pos;

}Object;

//--------------------------------------------------------

// Object Stack : ������Ʈ�� ����ϴ� ����
typedef struct tag_objstack {

#define STACK_SIZE 1000000

	Object objs[STACK_SIZE]; // 0������ ��ϵȴ�
	int counter; //���� ���ÿ� ��� ��ϵǾ��ִ����� ����Ų��. 0���� ����

	void(*init)(struct tag_objstack *stack); //�ʱ�ȭ

	int (*isStackFull)(struct tag_objstack *stack); //������ ���� á���� 1�� ��ȯ, �ƴϸ� 0
	int (*isStackEmpty)(struct tag_objstack *stack); //������ ��������� 1�� ��ȯ, �ƴϸ� 0
	int (*push)(struct tag_objstack *stack, Object obj); //���ÿ� �� ������Ʈ�� �߰��Ѵ�
	int (*pull)(struct tag_objstack *stack); //���ÿ� �� ���������� ��ϵ� ������Ʈ�� �����Ѵ�

}ObjStack;


//--------------------------------------------------------

// Static Variables
static ObjStack Stack;


void initialization();

