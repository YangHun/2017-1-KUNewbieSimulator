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

// Object Stack : 오브젝트를 등록하는 스택
typedef struct tag_objstack {

#define STACK_SIZE 1000000

	Object objs[STACK_SIZE]; // 0번부터 등록된다
	int counter; //현재 스택에 몇개가 등록되어있는지를 가리킨다. 0부터 시작

	void(*init)(struct tag_objstack *stack); //초기화

	int (*isStackFull)(struct tag_objstack *stack); //스택이 가득 찼으면 1을 반환, 아니면 0
	int (*isStackEmpty)(struct tag_objstack *stack); //스택이 비어있으면 1을 반환, 아니면 0
	int (*push)(struct tag_objstack *stack, Object obj); //스택에 새 오브젝트를 추가한다
	int (*pull)(struct tag_objstack *stack); //스택에 맨 마지막으로 등록된 오브젝트를 삭제한다

}ObjStack;


//--------------------------------------------------------

// Static Variables
static ObjStack Stack;


void initialization();

