#pragma once
#include "event_structure.h"

static void sto_event_dummy0();
static void sto_event_dummy1();
static void sto_event_dummy2();
static void seq_event_dummy0();
static void seq_event_dummy1();
static void seq_event_dummy2();
static void spe_event_dummy0();
static void spe_event_dummy1();
static void spe_event_dummy2();
static void click_yes(object_t* o);
void click_no(object_t* o);

void init_sto_event(event_function sto_event_func[]);
void init_seq_event(event_function seq_event_func[]);
void init_spe_event(event_function spe_event_func[]);

extern int yes_or_no_UI_starting;
extern bool event_waiting;

void init_event(event_function sto_event_func[], event_function seq_event_func[], event_function spe_event_func[]) {
	init_sto_event(sto_event_func);
	init_seq_event(seq_event_func);
	init_spe_event(spe_event_func);
}

void init_sto_event(event_function sto_event_func[]) {
	sto_event_func[0].func = sto_event_dummy0;
	sto_event_func[1].func = sto_event_dummy1;
	sto_event_func[2].func = sto_event_dummy2;
	for (int i = 0; i < STO_EVENTCOUNT; i++) {
		sto_event_func[i].isStarted = false;
	}
}
void init_seq_event(event_function seq_event_func[]) {
	seq_event_func[0].func = seq_event_dummy0;
	seq_event_func[1].func = seq_event_dummy1;
	seq_event_func[2].func = seq_event_dummy2;
	for (int i = 0; i < SEQ_EVENTCOUNT; i++) {
		seq_event_func[i].isStarted = false;
	}
}

void init_spe_event(event_function spe_event_func[]) {
	spe_event_func[0].func = spe_event_dummy0;
	spe_event_func[1].func = spe_event_dummy1;
	spe_event_func[2].func = spe_event_dummy2;
	for (int i = 0; i < SPE_EVENTCOUNT; i++) {
		spe_event_func[i].isStarted = false;
	}
}


void sto_event_dummy0() {
	char copycat[] = "0";
	printf("sto %s is on \n", copycat);
}

void sto_event_dummy1() {
	char copycat[] = "1";
	printf("sto %s is on \n", copycat);
}

void sto_event_dummy2() {
	char copycat[] = "2";
	printf("sto %s is on \n", copycat);
}

void seq_event_dummy0() {
	char copycat[] = "0";
	printf("seq %s is on \n", copycat);
	Stack.objs[yes_or_no_UI_starting + 2].modifier.value.font_value.text = "seq0";
	Stack.objs[yes_or_no_UI_starting + 3].modifier.value.font_value.text = "seq0";
	for (int i = 0; i < 4; i++) {
		Stack.objs[yes_or_no_UI_starting + i].enable = true;
	}
	ui_set_on_click_listener(&Stack.objs[yes_or_no_UI_starting + 2], click_yes);
	ui_set_on_click_listener(&Stack.objs[yes_or_no_UI_starting + 3], click_no);

}

void seq_event_dummy1() {
	char copycat[] = "1";
	printf("seq %s is on \n", copycat);
}

void seq_event_dummy2() {
	char copycat[] = "2";
	printf("seq %s is on \n", copycat);
}

void spe_event_dummy0() {
	char copycat[] = "0";
	printf("spe %s is on \n", copycat);
}

void spe_event_dummy1() {
	char copycat[] = "1";
	printf("spe %s is on \n", copycat);
}

void spe_event_dummy2() {
	char copycat[] = "2";
	printf("spe %s is on \n", copycat);
}

void click_yes(object_t* o) {

	switchs(o->modifier.value.font_value.text) {
		cases("seq0")
			printf("seq0 yes");
		defaults

	} switchs_end;
	
	o->modifier.value.font_value.text = "";
	event_waiting = true;
}

void click_no(object_t* o) {

	switchs(o->modifier.value.font_value.text) {
		cases("seq0")
			printf("seq0 no");
		defaults

	} switchs_end;
	o->modifier.value.font_value.text = "";
	event_waiting = true;
}