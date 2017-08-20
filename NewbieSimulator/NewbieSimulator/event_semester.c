#include "event_structure.h"

static void sto_event_dummy0();
static void sto_event_dummy1();
static void sto_event_dummy2();
static void seq_event_dummy0();
static void seq_event_dummy1();
static void seq_event_dummy2();

void init_sto_event(event_function sto_event_func[]);
void init_seq_event(event_function seq_event_func[]);

void init_event(event_function sto_event_func[], event_function seq_event_func[]) {
	init_sto_event(sto_event_func);
	init_seq_event(seq_event_func);
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
	for (int i = 0; i < STO_EVENTCOUNT; i++) {
		seq_event_func[i].isStarted = false;
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
}

void seq_event_dummy1() {
	char copycat[] = "1";
	printf("seq %s is on \n", copycat);
}

void seq_event_dummy2() {
	char copycat[] = "2";
	printf("seq %s is on \n", copycat);
}

