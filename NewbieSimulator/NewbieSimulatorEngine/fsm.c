#include "core.h"
#include "engine.h"

//----------------------------------------
// Scene 0
//----------------------------------------

// state 000
int first_frame_0() {

	return 0;
}

int action_0() {


	return 0;
}

int late_update_0() {

	//action�� ������ ��.
	
	if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
		//transition
		// if mouse clicked, change scene 0 --> 1
		transition_0_to_1();
	}

	return 0;
}

int transition_0_to_1() {

	// state_000���� state_001���� ����.

	printf("mouse click \n");
	current = Scenes.scenes[1];

	return 0;
}


// state 001
int first_frame_1() {


	return 0;
}

int action_1() {



	return 0;
}

int late_update_1() {

	return 0;
}

//----------------------------------------
// Scene 1
//----------------------------------------

// state 100
int first_frame_100() {


	return 0;
}

int action_100() {



	return 0;
}

int late_update_100() {

	current = Scenes.scenes[1]; //���� scene���� �̵�

	return 0;
}