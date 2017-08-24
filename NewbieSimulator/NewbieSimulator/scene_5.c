#include "engine.h"
#include "data.h"
#include "xmlParser.h"
void register_text_UI();
void register_back_button();

int scene_5_init() {

	
	Background = create_object("Resources\\UI\\result\\layout.jpg", 0, 0);
	
	//for test
	xmlParse(lectureTable);

	register_text_UI();
	register_back_button();

	

	return 0;
}

void register_text_UI() {


	// initialization for test
	// must be removed
	for (int i = 0; i < 5; i++) {
		lectureindex[i] = i;
	}

	// calculate grade 
	// TODO
	float grade_num[6];
	char string_grade_num[6][20];
	char string_grade[6][10];
	char string_lecture_code[6][11];
	char string_lecture_name[6][40];
	
	for (int i = 0; i < 6; i++) {

		//todo : calculate each grade of lecture with attendance rate
		grade_num[i] = 4.5 - 0.5 * i;
	}

	for (int i = 0; i < 6; i++) {
		sprintf(string_grade_num[i], "%.1f", grade_num[i]);
	}

	for (int i = 0; i < 6; i++) {

		float n = grade_num[i];

		if (n == 4.5) {
			sprintf(string_grade[i], "A+");
		}
		else if (n == 4.0) {
			sprintf(string_grade[i], "A");
		}
		else if (n == 3.5) {
			sprintf(string_grade[i], "B+");
		}
		else if (n == 3.0) {
			sprintf(string_grade[i], "B");
		}
		else if (n == 2.5) {
			sprintf(string_grade[i], "C+");
		}
		else if (n == 2.0) {
			sprintf(string_grade[i], "C");
		}
		else if (n == 1.5) {
			sprintf(string_grade[i], "D+");
		}
		else if (n == 1.0) {
			sprintf(string_grade[i], "D");
		}
		else if (n == 0.0) {
			sprintf(string_grade[i], "F");
		}

	}

	for (int i = 0; i < 6; i++) {

		//todo : set lecture code
		
		//for test
		sprintf(string_lecture_code[i], "%s-0%d", lectureTable[i].identifyNumber, 0); // actually lectureindex[i]
	}

	for (int i = 0; i < 6; i++) {

		//todo : set lecture name

		//for test
		sprintf(string_lecture_name[i], "%s - %c", lectureTable[i].name, (i+97));
	}

	// grade text
	for (int i = 0; i < 6; i++) {
		if (lectureindex[i] != -1) {
			object_t text_year = create_object(NULL, 80, 140 + 50 * i);
			ui_set_text(&text_year, al_map_rgb(0, 0, 0), "Resources\\font\\NanumBarunGothic.ttf", ALLEGRO_ALIGN_CENTER, "2017", 24);
			Stack.push(&Stack, text_year);

			object_t text_hakgi = create_object(NULL, 165, 140 + 50 * i);
			ui_set_text(&text_hakgi, al_map_rgb(0, 0, 0), "Resources\\font\\NanumBarunGothic.ttf", ALLEGRO_ALIGN_CENTER, "1", 24);
			Stack.push(&Stack, text_hakgi);

			object_t text_code = create_object(NULL, 285, 140 + 50 * i);
			ui_set_text(&text_code, al_map_rgb(0, 0, 0), "Resources\\font\\NanumBarunGothic.ttf", ALLEGRO_ALIGN_CENTER, string_lecture_code[i], 24);
			Stack.push(&Stack, text_code);

			object_t text_name = create_object(NULL, 520, 140 + 50 * i);
			ui_set_text(&text_name, al_map_rgb(0, 0, 0), "Resources\\font\\NanumBarunGothic.ttf", ALLEGRO_ALIGN_CENTER, string_lecture_name[i], 24);
			Stack.push(&Stack, text_name);

			object_t text_grade = create_object(NULL, 710, 140 + 50 * i);
			ui_set_text(&text_grade, al_map_rgb(0, 0, 0), "Resources\\font\\NanumBarunGothic.ttf", ALLEGRO_ALIGN_CENTER, string_grade[i], 24);
			Stack.push(&Stack, text_grade);

			object_t text_grade_num = create_object(NULL, 800, 140 + 50 * i);
			ui_set_text(&text_grade_num, al_map_rgb(0, 0, 0), "Resources\\font\\NanumBarunGothic.ttf", ALLEGRO_ALIGN_CENTER, string_grade_num[i], 24);
			Stack.push(&Stack, text_grade_num);
		}
	}


	// calculate total grade data
	// TODO
	int credit_start = 16;
	int credit_end = 19;
	float grade_num_except_f = 4.5;
	float grade_num_total = 3.5;
	
	char string_credit_start[20] = "";
	sprintf(string_credit_start, "%d", credit_start);
	char string_credit_end[20] = "";
	sprintf(string_credit_end, "%d", credit_end);
	char string_grade_num_except_f[20] = "";
	sprintf(string_grade_num_except_f, "%.1f", grade_num_except_f);
	char string_grade_num_total[20] = "";
	sprintf(string_grade_num_total, "%.1f", grade_num_total);

	// total grade text
	object_t text_year = create_object(NULL, 80, 605);
	ui_set_text(&text_year, al_map_rgb(0, 0, 0), "Resources\\font\\NanumBarunGothic.ttf", ALLEGRO_ALIGN_CENTER, "2017", 24);
	Stack.push(&Stack, text_year);

	object_t text_hakgi = create_object(NULL, 165, 605);
	ui_set_text(&text_hakgi, al_map_rgb(0, 0, 0), "Resources\\font\\NanumBarunGothic.ttf", ALLEGRO_ALIGN_CENTER, "1", 24);
	Stack.push(&Stack, text_hakgi);

	object_t text_credit_start = create_object(NULL, 290, 605);
	ui_set_text(&text_credit_start, al_map_rgb(0, 0, 0), "Resources\\font\\NanumBarunGothic.ttf", ALLEGRO_ALIGN_CENTER, string_credit_start, 24);
	Stack.push(&Stack, text_credit_start);

	object_t text_credit_end = create_object(NULL, 435, 605);
	ui_set_text(&text_credit_end, al_map_rgb(0, 0, 0), "Resources\\font\\NanumBarunGothic.ttf", ALLEGRO_ALIGN_CENTER, string_credit_end, 24);
	Stack.push(&Stack, text_credit_end);

	object_t text_grade_num_except_f = create_object(NULL, 590, 605);
	ui_set_text(&text_grade_num_except_f, al_map_rgb(0, 0, 0), "Resources\\font\\NanumBarunGothic.ttf", ALLEGRO_ALIGN_CENTER, string_grade_num_except_f, 24);
	Stack.push(&Stack, text_grade_num_except_f);

	object_t text_grade_num_total = create_object(NULL, 760, 605);
	ui_set_text(&text_grade_num_total, al_map_rgb(0, 0, 0), "Resources\\font\\NanumBarunGothic.ttf", ALLEGRO_ALIGN_CENTER, string_grade_num_total, 24);
	Stack.push(&Stack, text_grade_num_total);

	object_t text_sum_credit_start = create_object(NULL, 290, 605 + 50);
	ui_set_text(&text_sum_credit_start, al_map_rgb(0, 0, 0), "Resources\\font\\NanumBarunGothic.ttf", ALLEGRO_ALIGN_CENTER, string_credit_start, 24);
	Stack.push(&Stack, text_sum_credit_start);

	object_t text_sum_credit_end = create_object(NULL, 435, 605 + 50);
	ui_set_text(&text_sum_credit_end, al_map_rgb(0, 0, 0), "Resources\\font\\NanumBarunGothic.ttf", ALLEGRO_ALIGN_CENTER, string_credit_end, 24);
	Stack.push(&Stack, text_sum_credit_end);

	object_t text_sum_grade_num_except_f = create_object(NULL, 590, 605 + 50);
	ui_set_text(&text_sum_grade_num_except_f, al_map_rgb(0, 0, 0), "Resources\\font\\NanumBarunGothic.ttf", ALLEGRO_ALIGN_CENTER, string_grade_num_except_f, 24);
	Stack.push(&Stack, text_sum_grade_num_except_f);

	object_t text_sum_grade_num_total = create_object(NULL, 760, 605 + 50);
	ui_set_text(&text_sum_grade_num_total, al_map_rgb(0, 0, 0), "Resources\\font\\NanumBarunGothic.ttf", ALLEGRO_ALIGN_CENTER, string_grade_num_total, 24);
	Stack.push(&Stack, text_sum_grade_num_total);

}

void on_click_listener_back() {
	load_scene(Scenes.scenes[0]);
}

void register_back_button() {
	object_t back = create_object("Resources\\UI\\result\\back.png", 1160, 600);
	ui_set_button(&back);
	ui_set_on_click_listener(&back, on_click_listener_back);
	Stack.push(&Stack, back);
}

int scene_5_update() {
	return 0;
}

int scene_5_fin() {
	Stack.clear(&Stack);
	return 0;
}
