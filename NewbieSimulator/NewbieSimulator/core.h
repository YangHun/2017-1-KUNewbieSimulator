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

// Scene : ������ ��
typedef struct tag_scene {
	int isFirst;
	int num; //Scene number

	int(*init)(); //�ش� ������ �Ѿ�ö� �� �ѹ� ����
	int(*act)(); //scene�� main��
	int(*transit)(); //���� ������ �Ѿ �� �� �� �� ����

}Scene;

typedef struct tag_scenearray {

#define SCENE_SIZE 20

	Scene scenes[SCENE_SIZE]; //0������ ���
	int counter; //���� ���ÿ� �� ���� ��ϵǾ��ִ����� ����Ų��. 0���� ����

	int(*isArrayFull)(struct tag_scenearray *stack); //�迭�� ���� á���� 1�� ��ȯ, �ƴϸ� 0
	int(*isArrayEmpty)(struct tag_scenearray *stack); //�迭�� ��������� 1�� ��ȯ, �ƴϸ� 0
	int(*push)(struct tag_scenearray *stack, Scene s); //�迭�� �� ������Ʈ�� �߰��Ѵ�
	int(*pull)(struct tag_scenearray *stack); //�迭�� �� ���������� ��ϵ� ������Ʈ�� �����Ѵ�

}SceneArray;


// FSM : game flow�� �����ϴ� �� ���� �༮
typedef struct tag_fsm {

	int isFirst;
	int state_num;
	int adress;

	int(*firstframe)(); //ù �����ӿ� �� �� ����
	int(*action)(); //�� �����Ӹ��� �����
	int(*lateupdate)(); //�׼��� ���� �� �����

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
