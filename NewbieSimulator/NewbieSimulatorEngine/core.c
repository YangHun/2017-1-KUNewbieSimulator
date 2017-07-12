#include "core.h"

static int isStackFull(objstack_t *stack);
static int isStackEmpty(objstack_t *stack);
static int push_stack(objstack_t *stack, object_t obj);
static int pull_stack(objstack_t *stack);

static int isSceneStackFull(scenearray_t *stack);
static int isSceneStackEmpty(scenearray_t *stack);
static int scene_push_stack(scenearray_t *stack, scene_t obj);
static int scene_pull_stack(scenearray_t *stack);

extern void start();
extern void end();

//--------------------------------------------------------
// Core Variables
//--------------------------------------------------------
objstack_t Stack;
scenearray_t Scenes;
fsmarray_t FSMs;

fsm_t prev;
fsm_t next;
fsm_t null_fsm = {-1, -1, -1, NULL, NULL, NULL, NULL};

scene_t current_scene;
scene_t next_scene;
scene_t null_scene = {-1, -1, NULL, NULL, NULL};



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
	else if (stack->counter > 0) {
		return 0;
	}
	else {
		return -1; //error code
	}
}

int push_stack(objstack_t *stack, object_t obj) {
	if (!(stack->is_full(stack))) {
		stack->objs[stack->counter] = obj;
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

int clear_stack(objstack_t *stack) {

	printf("enter \n");

	if (!(stack->is_empty(stack))) {

		while (!(stack->is_empty(stack))) {
			stack->pull(&Stack);
		}
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
	else if (arr->counter > 0) {
		return 0;
	}
	else {
		return -1; //error code
	}
}

int scene_push_stack(scenearray_t *arr, scene_t obj) {
	if (!(arr->is_full(arr))) {
		arr->scenes[arr->counter] = obj;
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

	obj.rotated = false;
	obj.angle = 0.0f;

	obj.rect.width = al_get_bitmap_width(obj.image);
	obj.rect.height = al_get_bitmap_height(obj.image);
	obj.rect.left = x;
	obj.rect.top = y;

	obj.pos.x = x;
	obj.pos.y = y;

	return obj;
}

void rotate_object(object_t* obj, float angle) {

	obj->angle += angle;
	obj->rotated = true;

	printf("%f %d", obj->angle, obj->rotated);
}

//---------------------------------------------------
// FSM functions & Managing FSM functions
//---------------------------------------------------

int transit_state(fsm_t p, fsm_t n) {

	prev = p;
	next = n;

	return n.state_num;
}

//---------------------------------------------------
// Scene functions & Managing FSM functions
//---------------------------------------------------

void load_scene(scene_t next) {
	next_scene = next;
	next_scene.isFirst = 1;
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
	Stack.clear = clear_stack;

	Scenes.counter = 0;
	Scenes.is_full = isSceneStackFull;
	Scenes.is_empty = isSceneStackEmpty;
	Scenes.push = scene_push_stack;
	Scenes.pull = scene_pull_stack;

	FSMs.transition = transit_state;


	//-------------------------------------------
	// FSM & State register
	//-------------------------------------------
	
	start();

	//-------------------------------------------
	// Init variables
	//-------------------------------------------
	
	prev = FSMs.states[0];
	next = NULLFSM;

	current_scene = Scenes.scenes[0];
	next_scene = NULLSCENE;
	
}



