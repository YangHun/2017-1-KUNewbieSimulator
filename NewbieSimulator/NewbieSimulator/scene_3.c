#include "engine.h"
#include"schedule.h"

ALLEGRO_CONFIG *conf;
ALLEGRO_FONT *font;
ALLEGRO_TIMER *click_timer;
ALLEGRO_EVENT_QUEUE *click_event;

bool wait = false;	//������ ���ȭ��
bool counting_start = false;	//�ʽð� ����
bool timer_started = false;	//Ÿ�̸� ����
bool game_start = false;	//������û ����
bool pressed[6];

void on_click_startbt();
void pressed1();
void pressed2();
void pressed3();
void pressed4();
void pressed5();
void pressed6();
void result();

int click_timer_set = 0;
int pressed_time[6];

int scene_3_init() {

	//�ش� ���� ���۵� ��, �� �� �� ����Ǵ� �Լ�
	int i;

	printf("Scene 0 start! \n");

	object_t bg = create_object("Resources\\UI\\enroll_2\\background.jpg", 0, 0);
	Background = bg;

	conf = al_load_config_file("Resources\\korean\\enroll_2.ini");

	click_timer = al_create_timer(1.0 / 1000);
	click_event = al_create_event_queue();
	al_register_event_source(click_event, al_get_timer_event_source(click_timer));
	//al_start_timer(click_timer);

	object_t bt[6];	//��û��ư ���
	bt[0] = create_object("Resources\\UI\\enroll_2\\b_apply.png", 741, 225);
	bt[1] = create_object("Resources\\UI\\enroll_2\\b_apply.png", 741, 299);
	bt[2] = create_object("Resources\\UI\\enroll_2\\b_apply.png", 741, 376);
	bt[3] = create_object("Resources\\UI\\enroll_2\\b_apply.png", 741, 451);
	bt[4] = create_object("Resources\\UI\\enroll_2\\b_apply.png", 741, 531);
	bt[5] = create_object("Resources\\UI\\enroll_2\\b_apply.png", 741, 611);
	for (i = 0; i < 6; i++) {
		ui_set_button(&bt[i]);
		Stack.push(&Stack, bt[i]);
		pressed[i] = false;
	}
	ui_set_on_click_listener(&bt[0], pressed1);
	ui_set_on_click_listener(&bt[1], pressed2);
	ui_set_on_click_listener(&bt[2], pressed3);
	ui_set_on_click_listener(&bt[3], pressed4);
	ui_set_on_click_listener(&bt[4], pressed5);
	ui_set_on_click_listener(&bt[5], pressed6);

	//�����̸� ���
	object_t lecture[6];
	for (i = 0; i < 6; i++) {
		lecture[i] = create_object(NULL, 850, 235 + i * 74);
		ui_set_text(&lecture[i], al_map_rgb(0, 0, 0), "Resources\\font\\NanumGothic.ttf", ALLEGRO_ALIGN_LEFT, "something", 36); //�����κ� �ٲ����
		Stack.push(&Stack, lecture[i]);
	}

	object_t navyism = create_object("Resources\\UI\\enroll_2\\navyism_background.png", 0, 0);
	Stack.push(&Stack, navyism);

	return 0;
}


int scene_3_update() {

	//Scene 0�� Main��
	//while�� �ȿ� �ִ� --> �� frame���� �����
	int i;
	printf("Scene 3 act! \n");

	if (!wait) {	//������ ȭ�� ���
		wait = true;
		object_t before = create_object("Resources\\UI\enroll_2\\before_start.png", 0, 0);
		Stack.push(&Stack, before);
		object_t start_bt = create_object("Resources\\UI\\enroll_2\\b_start.png", 500, 500);
		ui_set_button(&start_bt);
		ui_set_on_click_listener(&start_bt, on_click_startbt);
		Stack.push(&Stack, start_bt);
	}

	if (counting_start) {
		if (!timer_started) {	//Ÿ�̸� �۵�
			timer_started = true;
			al_start_timer(click_timer);
		}

		//������ �ʽð� ����
		//

#define GAMESTART_COUNT 10
		if (!game_start && al_get_timer_count(click_timer) - click_timer_set > (GAMESTART_COUNT * 1000)) {	//10�������� ������û ����
			game_start = true;
		}
		else if (game_start) {
			int c = 0;
			for (i = 0; i < 6; i++) {
				if (!pressed[i]) c++;
			}
			if (c == 6)
				result();
		}
	}

	re_draw();

	return 0;
}

void on_click_startbt()
{
	Stack.pull(&Stack);
	Stack.pull(&Stack);
	counting_start = true;
}

void pressed1()
{
	if (!game_start) return; //������û �ȿ������� �ǹ̾���
	pressed[0] = true;
	pressed_time[0] = al_get_timer_count(click_timer);
}

void pressed2()
{
	if (!game_start) return;
	pressed[1] = true;
	pressed_time[1] = al_get_timer_count(click_timer);
}

void pressed3()
{
	if (!game_start) return;
	pressed[2] = true;
	pressed_time[2] = al_get_timer_count(click_timer);
}

void pressed4()
{
	if (!game_start) return;
	pressed[3] = true;
	pressed_time[3] = al_get_timer_count(click_timer);
}

void pressed5()
{
	if (!game_start) return;
	pressed[4] = true;
	pressed_time[4] = al_get_timer_count(click_timer);
}

void pressed6()
{
	if (!game_start) return;
	pressed[5] = true;
	pressed_time[5] = al_get_timer_count(click_timer);
}

void result()
{
}

int scene_3_fin() {

	// �� ������ �ٸ� ������ �Ѿ ��, �� �� ����Ǵ� �Լ�.
	Stack.clear(&Stack);

	printf("counter : %d \n", Stack.counter);

	return 0;
}



