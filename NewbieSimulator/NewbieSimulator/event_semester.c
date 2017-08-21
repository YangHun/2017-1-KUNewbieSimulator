#pragma once
#include "event_structure.h"
#include "data.h"

static void click_yes(object_t* o);
static void click_no(object_t* o);

void init_sto_event(event_function sto_event_func[]);
void init_seq_event(event_function seq_event_func[]);
void init_spe_event(event_function spe_event_func[]);
static void gaechong_0();
static void shin_ip_daemyun_1();
static void gohak_daemyun_2();
static void sabal_3();
static void ung_ti_4();
static void hap_ung_5();

extern int yes_or_no_UI_starting;
extern bool event_choose;

void init_event(event_function sto_event_func[], event_function seq_event_func[], event_function spe_event_func[]) {
	init_sto_event(sto_event_func);
	init_seq_event(seq_event_func);
	init_spe_event(spe_event_func);
}

int trigger_sequencial_event(int month, whatDay day_of_week, int week, event_function event_func[]) {
	int hash = month * 100 + week * 10 + day_of_week; // 310 = 3월 1째주 0(월 = 0 ~ 금 = 4)
	switch (hash) {
		case 310:
			event_func[0].func();
			event_func[0].isStarted = true;
		break;
		case 312:
			event_func[1].func();
			event_func[1].isStarted = true;
		break;
		case 314:
			event_func[2].func();
			event_func[2].isStarted = true;
		break;
		case 323:
			event_func[3].func();
			event_func[3].isStarted = true;
		break;
		case 324:
			event_func[4].func();
			event_func[4].isStarted = true;
		break;
		case 334:
			event_func[5].func();
			event_func[5].isStarted = true;
		break;
		case 422:
			event_func[6].func();
			event_func[6].isStarted = true;
		break;
		case 431:
			event_func[7].func();
			event_func[7].isStarted = true;
		break;
		case 534:
			event_func[9].func();
			event_func[9].isStarted = true;
		break;
		case 544:
			event_func[10].func();
			event_func[10].isStarted = true;
		break;
		case 642:
			event_func[12].func();
			event_func[12].isStarted = true;
		break;
	default:
		return 0;
		break;
	}
	return 1;
}

void init_sto_event(event_function sto_event_func[]) {
	;
	for (int i = 0; i < STO_EVENTCOUNT; i++) {
		sto_event_func[i].isStarted = false;
	}
}
void init_seq_event(event_function seq_event_func[]) { // 8과 11은 현재 보류 - 중간 기말
	seq_event_func[0].func = gaechong_0;
	seq_event_func[1].func = shin_ip_daemyun_1;
	seq_event_func[2].func = gohak_daemyun_2;
	seq_event_func[3].func = sabal_3;
	seq_event_func[4].func = ung_ti_4;
	seq_event_func[5].func = hap_ung_5;

	for (int i = 0; i < SEQ_EVENTCOUNT; i++) {
		seq_event_func[i].isStarted = false;
	}
}

void init_spe_event(event_function spe_event_func[]) {
	
	for (int i = 0; i < SPE_EVENTCOUNT; i++) {
		spe_event_func[i].isStarted = false;
	}
}

void standard_event_form() { // 기본적인 형태
	Stack.objs[yes_or_no_UI_starting + 1].modifier.value.font_value.text = "message of event";
	Stack.objs[yes_or_no_UI_starting + 2].modifier.value.font_value.text = "message of event";
	for (int i = 0; i < 3; i++) {
		Stack.objs[yes_or_no_UI_starting + i].enable = true;
	}
	ui_set_on_click_listener(&Stack.objs[yes_or_no_UI_starting + 1], click_yes);
	ui_set_on_click_listener(&Stack.objs[yes_or_no_UI_starting + 2], click_no);
}

void gaechong_0() { 
	Stack.objs[yes_or_no_UI_starting + 1].modifier.value.font_value.text = "gaechong";
	Stack.objs[yes_or_no_UI_starting + 2].modifier.value.font_value.text = "gaechong";
	for (int i = 0; i < 3; i++) {
		Stack.objs[yes_or_no_UI_starting + i].enable = true;
	}
	ui_set_on_click_listener(&Stack.objs[yes_or_no_UI_starting + 1], click_yes);
	ui_set_on_click_listener(&Stack.objs[yes_or_no_UI_starting + 2], click_no);
}

void shin_ip_daemyun_1() { 
	Stack.objs[yes_or_no_UI_starting + 1].modifier.value.font_value.text = "shinip daemyun";
	Stack.objs[yes_or_no_UI_starting + 2].modifier.value.font_value.text = "shinip daemyun";
	for (int i = 0; i < 3; i++) {
		Stack.objs[yes_or_no_UI_starting + i].enable = true;
	}
	ui_set_on_click_listener(&Stack.objs[yes_or_no_UI_starting + 1], click_yes);
	ui_set_on_click_listener(&Stack.objs[yes_or_no_UI_starting + 2], click_no);
}

void gohak_daemyun_2() { 
	Stack.objs[yes_or_no_UI_starting + 1].modifier.value.font_value.text = "gohak daemyun";
	Stack.objs[yes_or_no_UI_starting + 2].modifier.value.font_value.text = "gohak daemyun";
	for (int i = 0; i < 3; i++) {
		Stack.objs[yes_or_no_UI_starting + i].enable = true;
	}
	ui_set_on_click_listener(&Stack.objs[yes_or_no_UI_starting + 1], click_yes);
	ui_set_on_click_listener(&Stack.objs[yes_or_no_UI_starting + 2], click_no);
}

void sabal_3() { 
	Stack.objs[yes_or_no_UI_starting + 1].modifier.value.font_value.text = "sabal";
	Stack.objs[yes_or_no_UI_starting + 2].modifier.value.font_value.text = "sabal";
	for (int i = 0; i < 3; i++) {
		Stack.objs[yes_or_no_UI_starting + i].enable = true;
	}
	ui_set_on_click_listener(&Stack.objs[yes_or_no_UI_starting + 1], click_yes);
	ui_set_on_click_listener(&Stack.objs[yes_or_no_UI_starting + 2], click_no);
}

void ung_ti_4() { // 기본적인 형태
	Stack.objs[yes_or_no_UI_starting + 1].modifier.value.font_value.text = "ungti";
	Stack.objs[yes_or_no_UI_starting + 2].modifier.value.font_value.text = "ungti";
	for (int i = 0; i < 3; i++) {
		Stack.objs[yes_or_no_UI_starting + i].enable = true;
	}
	ui_set_on_click_listener(&Stack.objs[yes_or_no_UI_starting + 1], click_yes);
	ui_set_on_click_listener(&Stack.objs[yes_or_no_UI_starting + 2], click_no);
}

void hap_ung_5() { // 기본적인 형태
	Stack.objs[yes_or_no_UI_starting + 1].modifier.value.font_value.text = "hapung";
	Stack.objs[yes_or_no_UI_starting + 2].modifier.value.font_value.text = "hapung";
	for (int i = 0; i < 3; i++) {
		Stack.objs[yes_or_no_UI_starting + i].enable = true;
	}
	ui_set_on_click_listener(&Stack.objs[yes_or_no_UI_starting + 1], click_yes);
	ui_set_on_click_listener(&Stack.objs[yes_or_no_UI_starting + 2], click_no);
}

void click_yes(object_t* o) {
	event_choose = true;
	char compareText[20] = "";
	strcpy(compareText, o->modifier.value.font_value.text);
	o->modifier.value.font_value.text = "";
	
	switchs(compareText) {
		cases("gaechong") {
			printf("gaechong yes \n");
			social_point += 2;
			return;
		}
		cases("shinip daemyun") {
			printf("shinip yes \n");
			social_point += 1;
			health_point -= 1;
			return;
		}
		cases("gohak daemyun") {
			printf("gohak yes \n");
			social_point += 0.3;
			health_point -= 3;
			return;
		}
		cases("sabal") {
			printf("sabal yes \n");
			social_point += 0.3;
			health_point -= 3;
			return;
		}
		cases("ungti") {
			printf("ungti yes \n");
			social_point += 2;
			health_point -= 1;
			return;
		}
		cases("hapung") {
			printf("hapung yes \n");
			social_point += 2;
			health_point -= 2;
			return;
		}
		defaults

	} switchs_end;
	
	
}

void click_no(object_t* o) {

	event_choose = true;
	char compareText[20] = "";
	strcpy(compareText, o->modifier.value.font_value.text);
	o->modifier.value.font_value.text = "";

	switchs(compareText) {
		cases("gaechong") {
			printf("gaechong no \n");
			social_point -= 3;
			return;
		}
		cases("shinip daemyun") {
			printf("shinip no \n");
			social_point -= 1;
			return;
		}
		cases("gohak daemyun") {
			printf("gohak no \n");
			return;
		}
		cases("sabal") {
			printf("sabal no \n");
			social_point += 0.5;
			return;
		}
		cases("ungti") {
			printf("ungti no \n");
			social_point -= 1;
			return;
		}
		cases("hapung") {
			printf("hapung no \n");
			social_point -= 2;
			return;
		}
		defaults

	} switchs_end;


}