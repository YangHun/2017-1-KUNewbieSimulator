#pragma once
#include <stdio.h>
#include <Windows.h>
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>

typedef struct tag_position {
	float x, y;
}Position;

typedef struct tag_object {
	ALLEGRO_BITMAP *image;
	Position pos;

}Object;

typedef struct tag_animation {
	int num;
	float speed;
	ALLEGRO_BITMAP *images;
	Position pos;

}Animation;

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

// Scene : 게임의 씬
typedef struct tag_scene {
	int isFirst;
	int num; //Scene number

	int(*init)(); //해당 씬으로 넘어올때 딱 한번 실행
	int(*act)(); //scene의 main문
	int(*transit)(); //다음 씬으로 넘어갈 때 딱 한 번 실행

}Scene;

typedef struct tag_scenearray {

#define SCENE_SIZE 20

	Scene scenes[SCENE_SIZE]; //0번부터 등록
	int counter; //현재 스택에 몇 개가 등록되어있는지를 가리킨다. 0부터 시작

	int(*isArrayFull)(struct tag_scenearray *stack); //배열이 가득 찼으면 1을 반환, 아니면 0
	int(*isArrayEmpty)(struct tag_scenearray *stack); //배열이 비어있으면 1을 반환, 아니면 0
	int(*push)(struct tag_scenearray *stack, Scene s); //배열에 새 오브젝트를 추가한다
	int(*pull)(struct tag_scenearray *stack); //배열에 맨 마지막으로 등록된 오브젝트를 삭제한다

}SceneArray;


// FSM : game flow를 구현하는 데 쓰는 녀석
typedef struct tag_fsm {

	int isFirst;
	int state_num;
	int adress;

	int(*firstframe)(); //첫 프레임에 한 번 실행
	int(*action)(); //매 프레임마다 실행됨
	int(*lateupdate)(); //액션이 끝난 후 실행됨

	int(*transition)(struct tag_fsm prev, struct tag_fsm next);

}FSM;

typedef struct tag_fsmarray {

#define FSM_NUM 50

	FSM states[FSM_NUM];

	int(*transition)(FSM prev, FSM next);

}FSMArray;


//--------------------------------------------------------

// Static Variables
ObjStack Stack;
SceneArray Scenes;
FSMArray FSMs;

FSM prev;
FSM next;
FSM NULLFSM;

Scene current;

int state_num;

Object SetObject(char* imgpath, float x, float y);


int isStackFull(ObjStack *stack);
int isStackEmpty(ObjStack *stack);
int push_stack(ObjStack *stack, Object obj);
int pull_stack(ObjStack *stack);

int isSceneStackFull(SceneArray *stack);
int isSceneStackEmpty(SceneArray *stack);
int scene_push_stack(SceneArray *stack, Scene obj);
int scene_pull_stack(SceneArray *stack);

Object SetObject(char* imgpath, float x, float y);

int register_scenes(int n);
int init_scene_obj(Scene *s, int((*init)()), int((*act)()), int((*transit)()));

int transit_state(FSM p, FSM n);

void initialization();
