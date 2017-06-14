#include "core.h"

int isStackFull(ObjStack *stack) {
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

int isStackEmpty(ObjStack *stack) {
	if (stack->counter == 0) {
		return 1;
	}
	else if(stack->counter < 0){
		return 0;
	}
	else {
		return -1; //error code
	}
}

int push_stack(ObjStack *stack, Object obj) {
	if (!(stack->isStackFull(stack))) {
		stack->objs[stack->counter - 1] = obj;
		stack->counter++;
		return 0;
	}
	else {
		printf("stack is full! \n");
		return 1;
	}
}

int pull_stack(ObjStack *stack) {

	if (!(stack->isStackEmpty(stack))) {
		stack->counter--;
		return 0;
	}
	else {
		printf("stack is empty! \n");
		return 1;
	}
}

void initialization() {
	Stack.counter = 0;
	Stack.isStackFull = isStackFull;
	Stack.isStackEmpty = isStackEmpty;
	Stack.push = push_stack;
	Stack.pull = pull_stack;
}



