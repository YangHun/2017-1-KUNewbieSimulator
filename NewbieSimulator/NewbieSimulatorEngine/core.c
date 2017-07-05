#include "core.h"
#include "scenes.h"
#include "fsms.h"

static int isStackFull(objstack_t *stack);
static int isStackEmpty(objstack_t *stack);
static int push_stack(objstack_t *stack, object_t obj);
static int pull_stack(objstack_t *stack);

static int isSceneStackFull(scenearray_t *stack);
static int isSceneStackEmpty(scenearray_t *stack);
static int scene_push_stack(scenearray_t *stack, scene_t obj);
static int scene_pull_stack(scenearray_t *stack);

//--------------------------------------------------------
// Core Variables
//--------------------------------------------------------
objstack_t Stack;
scenearray_t Scenes;
fsmarray_t FSMs;

fsm_t prev;
fsm_t next;
fsm_t NULLFSM;

scene_t current;

int state_num = 0;

//---------------------------------------------------
// Stack functions
//---------------------------------------------------
int isStackFull(objstack_t *stack) {
	if (stack->counter == STACK_SIZE) {
		return 1;
	}
	else if (stack->counter >= 0 && stack->counter < STACK_SIZE) {
		return 0;
	}
	else {
		return -1; // error code
	}
}

int isStackEmpty(objstack_t *stack) {
	if (stack->counter == 0) {
		return 1;
	}
	else if (stack->counter < 0) {
		return 0;
	}
	else {
		return -1; //error code
	}
}

int push_stack(objstack_t *stack, object_t obj) {
	if (!(stack->is_full(stack))) {
		stack->objs[stack->counter - 1] = obj;
		stack->counter++;
		return 0;
	}
	else {
		printf("stack is full! \n");
		return 1;
	}
}

int pull_stack(objstack_t *stack) {

	if (!(stack->is_empty(stack))) {
		stack->counter--;
		return 0;
	}
	else {
		printf("stack is empty! \n");
		return 1;
	}
}

//---------------------------------------------------
// Scene Stack functions
//---------------------------------------------------

int isSceneStackFull(scenearray_t *arr) {
	if (arr->counter == SCENE_SIZE) {
		return 1;
	}
	else if (arr->counter >= 0 && arr->counter < SCENE_SIZE) {
		return 0;
	}
	else {
		return -1; // error code
	}
}

int isSceneStackEmpty(scenearray_t *arr) {
	if (arr->counter == 0) {
		return 1;
	}
	else if (arr->counter < 0) {
		return 0;
	}
	else {
		return -1; //error code
	}
}

int scene_push_stack(scenearray_t *arr, scene_t obj) {
	if (!(arr->is_full(arr))) {
		arr->scenes[arr->counter - 1] = obj;
		arr->counter++;
		return 0;
	}
	else {
		printf("stack is full! \n");
		return 1;
	}
}

int scene_pull_stack(scenearray_t *arr) {

	if (!(arr->is_empty(arr))) {
		arr->counter--;
		return 0;
	}
	else {
		printf("stack is empty! \n");
		return 1;
	}
}

//---------------------------------------------------
// Object functions
//---------------------------------------------------

object_t create_object(char* imgpath, float x, float y) {

	object_t obj;

	obj.image = al_load_bitmap(imgpath);
	if (obj.image == NULL) {
		printf("failed load bitmap image! \n");
	}
	obj.pos.x = x;
	obj.pos.y = y;

	return obj;
}

//---------------------------------------------------
// Managing Scene functions
//---------------------------------------------------

int register_scenes(int n) {

	//register scenes at this function!

	int i;

	for (i = 0; i < n; i++) {
		scene_t s;
		s.num = i;
		s.isFirst = 1;

		if (!(Scenes.is_full(&Scenes))) {
			Scenes.push(&Scenes, s);
		}
		else {
			break;
			printf("error : scene stack is full!!");
			return i;
		}
	}

	return 0;
}

int init_scene_obj(scene_t *s, int ((*init)()), int ((*act)()), int ((*transit)())) {

	s->init = init;
	s->act = act;
	s->fin = transit;

	return 0;
}

//---------------------------------------------------
// FSM functions & Managing FSM functions
//---------------------------------------------------


int transit_state(fsm_t p, fsm_t n) {

	p.transition(p, n);
	prev = p;
	next = n;

	return n.state_num;
}

int register_states(int n) {

	//register states at this function!

	int i;

	for (i = 0; i < n; i++) {
		
		fsm_t fsm;
		fsm.state_num = 0;
		fsm.adress = i;
		fsm.isFirst = 1;


		FSMs.states[i] = fsm;
	}

	return 0;
}

int init_fsm(fsm_t *f, int ((*firstframe)()), int((*action)()), int((*lateupdate)())) {

	f->firstframe = firstframe;
	f->action = action;
	f->lateupdate = lateupdate;

	return 0;
}

//---------------------------------------------------
// Engine Init Function
//---------------------------------------------------

void initialization() {

	//-------------------------------------------
	// Function Pointers init
	//-------------------------------------------
	
	Stack.counter = 0;
	Stack.is_full = isStackFull;
	Stack.is_empty = isStackEmpty;
	Stack.push = push_stack;
	Stack.pull = pull_stack;

	Scenes.counter = 0;
	Scenes.is_full = isSceneStackFull;
	Scenes.is_empty = isSceneStackEmpty;
	Scenes.push = scene_push_stack;
	Scenes.pull = scene_pull_stack;

	FSMs.transition = transit_state;

	//-------------------------------------------
	// FSM init
	//-------------------------------------------
	
#define EXIST_STATE_NUM 30 

	//1. register
	if (register_states(EXIST_STATE_NUM)) {
		printf("error : register scene crash");
		return;
	}

	//2. init - link function pointer
	//Plz add functions and call init() when new state has been added.
	//please add "all the" functions whether the function is empty or not. 
	init_fsm(&FSMs.states[0], first_frame_0, action_0, late_update_0);
	init_fsm(&FSMs.states[1], first_frame_1, action_1, late_update_1);
	init_fsm(&FSMs.states[2], first_frame_100, action_100, late_update_100);


	//3. init variables
	NULLFSM.adress = -1;
	NULLFSM.state_num = -1;

	prev = FSMs.states[0];
	next = NULLFSM;

	//-------------------------------------------
	// Scene init
	//-------------------------------------------

#define EXIST_SCENE_NUM 3

	//1. register
	if (register_scenes(EXIST_SCENE_NUM)) {
		printf("error : register scene crash");
		return;
	}

	//2. init each scene
	//Plz add functions and call init() when new scene has been added. 
	//please add "all the" functions whether the function is empty or not. 
	init_scene_obj(&Scenes.scenes[0], scene_0_init, scene_0_update, scene_0_fin);
	init_scene_obj(&Scenes.scenes[1], scene_1_init, scene_1_update, scene_1_fin);
	init_scene_obj(&Scenes.scenes[2], scene_2_init, scene_2_update, scene_2_fin);


	//3. init variables
	current = Scenes.scenes[0];

}



