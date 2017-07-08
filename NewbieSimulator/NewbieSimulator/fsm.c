#include "core.h"
#include "engine.h"
<<<<<<< Updated upstream:NewbieSimulator/NewbieSimulator/fsm.c
#include "fsms.h"
=======
<<<<<<< Updated upstream:NewbieSimulator/NewbieSimulatorEngine/fsm.c
=======
#include "fsms.h"
 
>>>>>>> Stashed changes:NewbieSimulator/NewbieSimulator/fsm.c
>>>>>>> Stashed changes:NewbieSimulator/NewbieSimulatorEngine/fsm.c

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

	//action이 끝났을 때.
	
<<<<<<< Updated upstream:NewbieSimulator/NewbieSimulator/fsm.c
	int clicked = 0;

	if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
		//transition
		// if mouse clicked, change scene 0 --> 1
		clicked++;

		if (clicked == 1) {
			transition_0_to_1();
		}
	}
=======
<<<<<<< Updated upstream:NewbieSimulator/NewbieSimulatorEngine/fsm.c
	if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
		//transition
		// if mouse clicked, change scene 0 --> 1
		transition_0_to_1();
=======
	static int down = 0;	
>>>>>>> Stashed changes:NewbieSimulator/NewbieSimulatorEngine/fsm.c

	if ( catch_event().type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
		if (!down) {
			down = 1;
		}
	}
	if (catch_event().type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
		
		if (down) {
			transition_0_to_1();
			down = 0;
		}
>>>>>>> Stashed changes:NewbieSimulator/NewbieSimulator/fsm.c
	}
	
	return 0;
}

int transition_0_to_1() {

	// state_000에서 state_001로의 전이.

	printf("mouse click \n");
<<<<<<< Updated upstream:NewbieSimulator/NewbieSimulator/fsm.c
	load_scene(Scenes.scenes[1]);
=======
<<<<<<< Updated upstream:NewbieSimulator/NewbieSimulatorEngine/fsm.c
	current = Scenes.scenes[1];
=======

	//다음 frame에 1번째 state를 로드
	next = FSMs.states[1];

	//다음 scene을 로드
	load_scene(Scenes.scenes[1]);
>>>>>>> Stashed changes:NewbieSimulator/NewbieSimulator/fsm.c
>>>>>>> Stashed changes:NewbieSimulator/NewbieSimulatorEngine/fsm.c

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

	current = Scenes.scenes[1]; //다음 scene으로 이동

	return 0;
}