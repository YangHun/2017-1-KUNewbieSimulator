#pragma once

#include <stdio.h>
#include <Windows.h>
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include "basictyps.h"

enum object_modifier_type_t;
typedef enum object_modifier_type_t object_modifier_type_t;
enum object_modifier_type_t {
	OBJECT_MODIFIER_DRAWABLE_ONLY,
	OBJECT_MODIFIER_BUTTON,
};

struct object_modifier_t;
typedef struct object_modifier_t object_modifier_t;
struct object_modifier_t {
	object_modifier_type_t type;
	union {
		struct {
			void(*on_click)();
		} button_value;
	} value;
};

struct object_t;
typedef struct object_t object_t;
struct object_t {
	ALLEGRO_BITMAP *image;
	position_t pos;
	object_modifier_t modifier;
	rect_t rect;
};

struct animation_t;
typedef struct animation_t animation_t;
struct animation_t {
	int num;
	float speed;
	ALLEGRO_BITMAP *images;
	position_t pos;

};

//--------------------------------------------------------

// objstack_t: ������Ʈ�� ����ϴ� ����
struct objstack_t;
typedef struct objstack_t objstack_t;
struct objstack_t {

#define STACK_SIZE 1000000

	object_t objs[STACK_SIZE]; // 0������ ��ϵȴ�
	int counter; //���� ���ÿ� ��� ��ϵǾ��ִ����� ����Ų��. 0���� ����

	void(*init)(objstack_t *stack); //�ʱ�ȭ

	int (*is_full)(objstack_t *stack); //������ ���� á���� 1�� ��ȯ, �ƴϸ� 0
	int (*is_empty)(objstack_t *stack); //������ ��������� 1�� ��ȯ, �ƴϸ� 0
	int (*push)(objstack_t *stack, object_t obj); //���ÿ� �� ������Ʈ�� �߰��Ѵ�
	int (*pull)(objstack_t *stack); //���ÿ� �� ���������� ��ϵ� ������Ʈ�� �����Ѵ�

};

// scene_t: ������ ��
struct scene_t;
typedef struct scene_t scene_t;
struct scene_t {
	int isFirst;
	int num; //Scene number

	int(*init)(); //�ش� ������ �Ѿ�ö� �� �ѹ� ����
	int(*act)(); //scene�� main��
	int(*fin)(); //���� ������ �Ѿ �� �� �� �� ����

};

struct scenearray_t;
typedef struct scenearray_t scenearray_t;
struct scenearray_t {

#define SCENE_SIZE 20

	scene_t scenes[SCENE_SIZE]; //0������ ���
	int counter; //���� ���ÿ� �� ���� ��ϵǾ��ִ����� ����Ų��. 0���� ����

	int(*is_full)(scenearray_t *stack); //�迭�� ���� á���� 1�� ��ȯ, �ƴϸ� 0
	int(*is_empty)(scenearray_t *stack); //�迭�� ��������� 1�� ��ȯ, �ƴϸ� 0
	int(*push)(scenearray_t *stack, scene_t s); //�迭�� �� ������Ʈ�� �߰��Ѵ�
	int(*pull)(scenearray_t *stack); //�迭�� �� ���������� ��ϵ� ������Ʈ�� �����Ѵ�

};

// fsm_t: game flow�� �����ϴ� �� ���� �༮
struct fsm_t;
typedef struct fsm_t fsm_t;
struct fsm_t {

	int isFirst;
	int state_num;
	int address;

	int(*firstframe)(); //ù �����ӿ� �� �� ����
	int(*action)(); //�� �����Ӹ��� �����
	int(*lateupdate)(); //�׼��� ���� �� �����

	int(*transition)(fsm_t prev, fsm_t next);

};

struct fsmarray_t;
typedef struct fsmarray_t fsmarray_t;
struct fsmarray_t {

#define FSM_NUM 50

	fsm_t states[FSM_NUM];

	int(*transition)(fsm_t prev, fsm_t next);

};


//--------------------------------------------------------
// Core Variables
//--------------------------------------------------------

extern objstack_t Stack;
extern scenearray_t Scenes;
extern fsmarray_t FSMs;

extern fsm_t prev;
extern fsm_t next;
extern fsm_t NULLFSM;

extern scene_t current;

extern int state_num;

object_t create_object(char* imgpath, float x, float y);

int transit_state(fsm_t p, fsm_t n);

void initialization();
