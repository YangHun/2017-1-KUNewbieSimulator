#pragma once

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <Windows.h>
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_primitives.h>
#include <time.h>
#include<allegro5\allegro_font.h>
#include<allegro5\allegro_native_dialog.h>
#include<allegro5\allegro_ttf.h>

#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>

#include <stdbool.h>


struct positioni_t;
typedef struct positioni_t positioni_t;
struct positioni_t {
	int x;
	int y;
};

bool positioni_equals(positioni_t a, positioni_t b);

struct positionf_t;
typedef struct positionf_t position_t;
struct positionf_t {
	float x;
	float y;
};

struct rect_t;
typedef struct rect_t rect_t;
struct rect_t {
	int left;
	int top;
	int width;
	int height;
};


enum object_modifier_type_t;
typedef enum object_modifier_type_t object_modifier_type_t;
enum object_modifier_type_t {
	OBJECT_MODIFIER_DRAWABLE_ONLY,
	OBJECT_MODIFIER_BUTTON,
	OBJECT_MODIFIER_FONT,
	OBJECT_MODIFIER_SCROLLBAR,
	OBJECT_MODIFIER_SCROLLBAR_CHILD,
	OBJECT_MODIFIER_LINE,
};

struct object_modifier_t;
typedef struct object_modifier_t object_modifier_t;
struct object_t;
typedef struct object_t object_t;


typedef void(*on_click_listener_t)(object_t *);

struct object_modifier_t {
	object_modifier_type_t type;
	union {
		struct {
			on_click_listener_t on_click_listener;
		} button_value;
		struct {
			ALLEGRO_FONT *font;
			int align;
			ALLEGRO_COLOR color;
			char* text;
		}font_value;
		struct {
			ALLEGRO_MOUSE_STATE state;
			object_t *target;
			object_t *body;
			object_t *thumb;
			object_t *button_top;
			object_t *button_bottom;
		}scrollbar;
		struct {
			float x1;
			float y1;
			float x2;
			float y2;
			float thickness;
		}line;
	} value;
};

struct object_t {
	ALLEGRO_BITMAP *image;
	ALLEGRO_COLOR color;
	position_t pos;

	bool enable; // enable�̸� draw, disable�̸� not draw
	bool blocks;
	
	float opacity; //transparancy

	bool rotated;
	float angle;

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
	int (*clear)(objstack_t *stack); //������ ����

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
extern fsm_t null_fsm;

extern scene_t current_scene;
extern scene_t next_scene;
extern scene_t null_scene;

#define NULLFSM null_fsm;
#define NULLSCENE null_scene;

extern int state_num;

object_t create_object(char* imgpath, float x, float y);
object_t create_colored_object(ALLEGRO_COLOR c, float width, float height, float top, float left);
object_t create_line_object(ALLEGRO_COLOR c, float x1, float y1, float x2, float y2, float thickness);

void rotate_object(object_t* obj, float angle);
void enable_object(object_t*obj, bool b);


bool rect_contains_point(rect_t rect, positioni_t point);
bool positionf_transparancy(object_t *obj, positioni_t point);

void load_scene(scene_t next);
int transit_state(fsm_t p, fsm_t n);

void initialization();
