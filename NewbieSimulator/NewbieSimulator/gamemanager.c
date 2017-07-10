#include "engine.h"
#include "scenes.h"
#include "fsms.h"

static int register_scene_obj(scene_t *s, int((*init)()), int((*act)()), int((*transit)()));
static int register_fsm_obj(fsm_t *f, int statenum, int((*firstframe)()), int((*action)()), int((*lateupdate)()), fsm_transition_t* trs);
static int register_fsm_obj_no_transit(fsm_t *f, int statenum, int((*firstframe)()), int((*action)()), int((*lateupdate)()));

extern ALLEGRO_EVENT ev;


static fsm_transition_t *trns;

//-----------------------------------------------------------------

void start () {

	//initialization scenes and fsms
	//called once

	// 1) Init scenes at Scene Array
	int i;
#define EXIST_SCENE_NUM 30 
	int n = EXIST_SCENE_NUM;

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
			return;
		}
	}

	// 2) Register function at each function pointer
	//link function pointer
	//Plz add functions and call register_scene_obj() when new state has been added.
	//please add "all the" functions whether the function is empty or not. 
	register_scene_obj(&Scenes.scenes[0], scene_0_init, scene_0_update, scene_0_fin);
	register_scene_obj(&Scenes.scenes[1], scene_1_init, scene_1_update, scene_1_fin);
	register_scene_obj(&Scenes.scenes[2], scene_2_init, scene_2_update, scene_2_fin);



	// 3) Init scenes at Scene Array
#define EXIST_STATE_NUM 30 
	n = EXIST_STATE_NUM;

	for (i = 0; i < n; i++) {
		fsm_t s;
		s.address = i;
		s.state_num = 0;
		s.isFirst = 1;

		FSMs.states[i] = s;
	}

	// 4) Register function at each function pointer
	//link function pointer
	//Plz add functions and call register_fsm_obj() when new state has been added.
	//please add "all the" functions whether the function is empty or not. 


	trns = malloc(sizeof(fsm_transition_t) * 1);
	trns[0] = transition_0_to_1;
	register_fsm_obj(&FSMs.states[0], 0, first_frame_0, action_0, late_update_0, trns);
	
	register_fsm_obj_no_transit(&FSMs.states[1], 1, first_frame_1, action_1, late_update_1);
	register_fsm_obj_no_transit(&FSMs.states[2], 100, first_frame_100, action_100, late_update_100);


}


void end () {

	//free memory and destroy elements
	//called once

	free(trns);
}

//------------------------------------------------------------------

void state_manage(ALLEGRO_EVENT ev) {

	if (next.address >= 0) {
		prev = next;
		next = NULLFSM;
	}

	switch (prev.state_num) {

		//--------------------------------------
		// Scene 0
		//--------------------------------------

	case 0: //when app starts : initialization
		if (prev.isFirst) {
			prev.firstframe();
			prev.isFirst = 0;
		}
		else {
			prev.action();
			prev.lateupdate();

		}
		break;

		//--------------------------------------
		// Scene 1
		//--------------------------------------

	case 100:
		if (prev.isFirst) {
			prev.firstframe();
			prev.isFirst = 0;
		}
		else {
			prev.action();
			prev.lateupdate();
		}
		break;


		/*

		TODO : Generate Game Flow FSM
		rule :
		scene_0 --> 000, 001, 002, ...
		scene_1 --> 100, 101, 102, ...
		scene_2 --> 200, 201, 202, ...

		*/


	case 9999: //when app ends
		break;
	}
}

//------------------------------------------------------------------

static int register_scene_obj(scene_t *s, int((*init)()), int((*act)()), int((*transit)())) {

	s->init = init;
	s->act = act;
	s->fin = transit;

	return 0;
}

static int register_fsm_obj(fsm_t *f, int statenum, int((*firstframe)()), int((*action)()), int((*lateupdate)()), fsm_transition_t* trs) {

	f->state_num = statenum;
	f->firstframe = firstframe;
	f->action = action;
	f->lateupdate = lateupdate;
	f->transition = trs;

	return 0;
}

static int register_fsm_obj_no_transit(fsm_t *f, int statenum, int((*firstframe)()), int((*action)()), int((*lateupdate)())) {

	f->state_num = statenum;
	f->firstframe = firstframe;
	f->action = action;
	f->lateupdate = lateupdate;

	return 0;
}