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

// objstack_t: 오브젝트를 등록하는 스택
struct objstack_t;
typedef struct objstack_t objstack_t;
struct objstack_t {

#define STACK_SIZE 1000000

	object_t objs[STACK_SIZE]; // 0번부터 등록된다
	int counter; //현재 스택에 몇개가 등록되어있는지를 가리킨다. 0부터 시작

	void(*init)(objstack_t *stack); //초기화

	int (*is_full)(objstack_t *stack); //스택이 가득 찼으면 1을 반환, 아니면 0
	int (*is_empty)(objstack_t *stack); //스택이 비어있으면 1을 반환, 아니면 0
	int (*push)(objstack_t *stack, object_t obj); //스택에 새 오브젝트를 추가한다
	int (*pull)(objstack_t *stack); //스택에 맨 마지막으로 등록된 오브젝트를 삭제한다

};

// scene_t: 게임의 씬
struct scene_t;
typedef struct scene_t scene_t;
struct scene_t {
	int isFirst;
	int num; //Scene number

	int(*init)(); //해당 씬으로 넘어올때 딱 한번 실행
	int(*act)(); //scene의 main문
	int(*fin)(); //다음 씬으로 넘어갈 때 딱 한 번 실행

};

struct scenearray_t;
typedef struct scenearray_t scenearray_t;
struct scenearray_t {

#define SCENE_SIZE 20

	scene_t scenes[SCENE_SIZE]; //0번부터 등록
	int counter; //현재 스택에 몇 개가 등록되어있는지를 가리킨다. 0부터 시작

	int(*is_full)(scenearray_t *stack); //배열이 가득 찼으면 1을 반환, 아니면 0
	int(*is_empty)(scenearray_t *stack); //배열이 비어있으면 1을 반환, 아니면 0
	int(*push)(scenearray_t *stack, scene_t s); //배열에 새 오브젝트를 추가한다
	int(*pull)(scenearray_t *stack); //배열에 맨 마지막으로 등록된 오브젝트를 삭제한다

};

// fsm_t: game flow를 구현하는 데 쓰는 녀석
struct fsm_t;
typedef struct fsm_t fsm_t;
struct fsm_t {

	int isFirst;
	int state_num;
	int address;

	int(*firstframe)(); //첫 프레임에 한 번 실행
	int(*action)(); //매 프레임마다 실행됨
	int(*lateupdate)(); //액션이 끝난 후 실행됨

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
