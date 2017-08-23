#include "engine.h"
#include "data.h"



void register_text_UI();
void register_back_button();


int scene_5_init() {

	
	Background = create_object("Resources\\UI\\result\\layout.jpg", 0, 0);
	
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
			ui_set_text(&text_code, al_map_rgb(0, 0, 0), "Resources\\font\\NanumBarunGothic.ttf", ALLEGRO_ALIGN_CENTER, "COSE10102", 24);
			Stack.push(&Stack, text_code);

			object_t text_name = create_object(NULL, 520, 140 + 50 * i);
			ui_set_text(&text_name, al_map_rgb(0, 0, 0), "Resources\\font\\NanumBarunGothic.ttf", ALLEGRO_ALIGN_CENTER, "I wanna sleep", 24);
			Stack.push(&Stack, text_name);

			object_t text_grade = create_object(NULL, 710, 140 + 50 * i);
			ui_set_text(&text_grade, al_map_rgb(0, 0, 0), "Resources\\font\\NanumBarunGothic.ttf", ALLEGRO_ALIGN_CENTER, "A+", 24);
			Stack.push(&Stack, text_grade);

			object_t text_grade_num = create_object(NULL, 800, 140 + 50 * i);
			ui_set_text(&text_grade_num, al_map_rgb(0, 0, 0), "Resources\\font\\NanumBarunGothic.ttf", ALLEGRO_ALIGN_CENTER, "4.5", 24);
			Stack.push(&Stack, text_grade_num);
		}
	}


	// calculate total grade data
	// TODO


	// total grade text
	object_t text_year = create_object(NULL, 80, 605);
	ui_set_text(&text_year, al_map_rgb(0, 0, 0), "Resources\\font\\NanumBarunGothic.ttf", ALLEGRO_ALIGN_CENTER, "2017", 24);
	Stack.push(&Stack, text_year);

	object_t text_hakgi = create_object(NULL, 165, 605);
	ui_set_text(&text_hakgi, al_map_rgb(0, 0, 0), "Resources\\font\\NanumBarunGothic.ttf", ALLEGRO_ALIGN_CENTER, "1", 24);
	Stack.push(&Stack, text_hakgi);

	object_t text_credit_start = create_object(NULL, 290, 605);
	ui_set_text(&text_credit_start, al_map_rgb(0, 0, 0), "Resources\\font\\NanumBarunGothic.ttf", ALLEGRO_ALIGN_CENTER, "19", 24);
	Stack.push(&Stack, text_credit_start);

	object_t text_credit_end = create_object(NULL, 435, 605);
	ui_set_text(&text_credit_end, al_map_rgb(0, 0, 0), "Resources\\font\\NanumBarunGothic.ttf", ALLEGRO_ALIGN_CENTER, "19", 24);
	Stack.push(&Stack, text_credit_end);

	object_t text_grade_num_except_f = create_object(NULL, 590, 605);
	ui_set_text(&text_grade_num_except_f, al_map_rgb(0, 0, 0), "Resources\\font\\NanumBarunGothic.ttf", ALLEGRO_ALIGN_CENTER, "4.5", 24);
	Stack.push(&Stack, text_grade_num_except_f);

	object_t text_grade_num_total = create_object(NULL, 760, 605);
	ui_set_text(&text_grade_num_total, al_map_rgb(0, 0, 0), "Resources\\font\\NanumBarunGothic.ttf", ALLEGRO_ALIGN_CENTER, "4.5", 24);
	Stack.push(&Stack, text_grade_num_total);

	object_t text_sum_credit_start = create_object(NULL, 290, 605 + 50);
	ui_set_text(&text_sum_credit_start, al_map_rgb(0, 0, 0), "Resources\\font\\NanumBarunGothic.ttf", ALLEGRO_ALIGN_CENTER, "19", 24);
	Stack.push(&Stack, text_sum_credit_start);

	object_t text_sum_credit_end = create_object(NULL, 435, 605 + 50);
	ui_set_text(&text_sum_credit_end, al_map_rgb(0, 0, 0), "Resources\\font\\NanumBarunGothic.ttf", ALLEGRO_ALIGN_CENTER, "19", 24);
	Stack.push(&Stack, text_sum_credit_end);

	object_t text_sum_grade_num_except_f = create_object(NULL, 590, 605 + 50);
	ui_set_text(&text_sum_grade_num_except_f, al_map_rgb(0, 0, 0), "Resources\\font\\NanumBarunGothic.ttf", ALLEGRO_ALIGN_CENTER, "4.5", 24);
	Stack.push(&Stack, text_sum_grade_num_except_f);

	object_t text_sum_grade_num_total = create_object(NULL, 760, 605 + 50);
	ui_set_text(&text_sum_grade_num_total, al_map_rgb(0, 0, 0), "Resources\\font\\NanumBarunGothic.ttf", ALLEGRO_ALIGN_CENTER, "4.5", 24);
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
