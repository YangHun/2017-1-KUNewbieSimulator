#include "engine.h"


static void scene_1_on_click_button_0();
float brightness, transparency;

#define EVENTCOUNT 7

ALLEGRO_TIMER* timer;
ALLEGRO_EVENT_QUEUE* timer_event_queue;
ALLEGRO_EVENT timer_event;
ALLEGRO_FONT *font;
ALLEGRO_CONFIG *conf;

void invitation();
void first_meeting();
void newbie_before_study();
void newbie_meeting();
void newbie_study();
void newbie_OT();
void scene_1_finish();

int timer_set = 0;
int explain_stat = 0;

int spritex = 640, spritey = 360;

int health_point = 0;
int social_point = 0;
char hpstr[10], spstr[10];

struct event_function {
	void(*func)();
	bool isStarted;
};

typedef struct event_function event_function;
event_function event_func[EVENTCOUNT];

object_t timebar, popup;
object_t character[8];

bool clicked = false;

int event_num = 0;
void clicked_yes();
void clicked_no();

#define HP_TEXT Stack.objs[5]
#define SP_TEXT Stack.objs[6]

int scene_1_init(){

	int i;
	//해당 씬이 시작될 때, 딱 한 번 실행되는 함수
	printf("Scene 1 start!");

	al_clear_to_color(al_map_rgb(204, 225, 152));

	conf = al_load_config_file("Resources\\korean\\tutorial.ini");

	object_t bg = create_object("Resources\\dummy\\background.png", 0, 0);
	Background = bg;

	timer = al_create_timer(1.0 / 1000);
	timer_event_queue = al_create_event_queue();
	al_register_event_source(timer_event_queue, al_get_timer_event_source(timer));

	object_t stat_window = create_object("Resources\\dummy\\stat_window.png", 0, 0);
	Stack.push(&Stack, stat_window);
	timebar = create_object("Resources\\dummy\\timebar.png", 700, 0);
	Stack.push(&Stack, timebar);

	object_t health = create_object(NULL, 60, 150);
	ui_set_text(&health, al_map_rgb(0, 0, 0), "Resources\\font\\NanumGothic.ttf", ALLEGRO_ALIGN_CENTER, al_get_config_value(conf, "korean", "health"), 24);
	Stack.push(&Stack, health);
	object_t sociality = create_object(NULL, 60, 190);
	ui_set_text(&sociality, al_map_rgb(0, 0, 0), "Resources\\font\\NanumGothic.ttf", ALLEGRO_ALIGN_CENTER, al_get_config_value(conf, "korean", "sociality"), 24);
	Stack.push(&Stack, sociality);
	object_t attend = create_object(NULL, 60, 230);
	ui_set_text(&attend, al_map_rgb(0, 0, 0), "Resources\\font\\NanumGothic.ttf", ALLEGRO_ALIGN_CENTER, al_get_config_value(conf, "korean", "attend"), 24);
	Stack.push(&Stack, attend);


	object_t hp = create_object(NULL, 300, 150);
	sprintf(hpstr, "%0.1f", health_point/10.0);
	ui_set_text(&hp, al_map_rgb(0, 0, 255), "Resources\\font\\NanumGothic.ttf", ALLEGRO_ALIGN_CENTER, hpstr, 24);
	Stack.push(&Stack, hp);

	object_t sp = create_object(NULL, 300, 200);
	sprintf(spstr, "%0.1f", social_point/10.0);
	ui_set_text(&sp, al_map_rgb(0, 0, 255), "Resources\\font\\NanumGothic.ttf", ALLEGRO_ALIGN_CENTER, spstr, 24);
	Stack.push(&Stack, sp);



	font = al_load_font("Resources\\font\\NanumGothic.ttf", 36, 0);

	character[0] = create_object("Resources\\Sprites\\tuto_0.png", spritex, spritey);
	character[1] = create_object("Resources\\Sprites\\tuto_1.png", spritex, spritey);
	character[2] = create_object("Resources\\Sprites\\tuto_2.png", spritex, spritey);
	character[3] = create_object("Resources\\Sprites\\tuto_3.png", spritex, spritey);
	character[4] = create_object("Resources\\Sprites\\tuto_4.png", spritex, spritey);
	character[5] = create_object("Resources\\Sprites\\tuto_5.png", spritex, spritey);
	character[6] = create_object("Resources\\Sprites\\tuto_6.png", spritex, spritey);
	character[7] = create_object("Resources\\Sprites\\tuto_7.png", spritex, spritey);
	for (i = 0; i < 8; i++) {
		character[i].enable = false;
		Stack.push(&Stack, character[i]);
	}
#define CHARACTER_START	7
#define CHARACTER_0 Stack.objs[5]
#define CHARACTER_1 Stack.objs[6]
#define CHARACTER_2 Stack.objs[7]
#define CHARACTER_3 Stack.objs[8]
#define CHARACTER_4 Stack.objs[9]
#define CHARACTER_5 Stack.objs[10]
#define CHARACTER_6 Stack.objs[11]
#define CHARACTER_7 Stack.objs[12]


	CHARACTER_0.enable = true;

	//이벤트 함수 모음
	event_func[0].func = invitation;
	event_func[1].func = first_meeting;
	event_func[2].func = newbie_before_study;
	event_func[3].func = newbie_meeting;
	event_func[4].func = newbie_study;
	event_func[5].func = newbie_OT;
	event_func[6].func = scene_1_finish;

	for (i = 0; i < EVENTCOUNT; i++)
		event_func[i].isStarted = false;
	
	return 0;
}

void move_up()
{
	int i;
	for (i = 0; i < 8; i++)
		Stack.objs[CHARACTER_START+i].pos.y -= 3.0;
}

void move_down()
{
	int i;
	for (i = 0; i < 8; i++)
		Stack.objs[CHARACTER_START+i].pos.y += 3.0;
}

void move_left()
{
	int i;
	for (i = 0; i < 8; i++)
		Stack.objs[CHARACTER_START+i].pos.x -= 3.0;
}

void move_right()
{
	int i;
	for (i = 0; i < 8; i++)
		Stack.objs[CHARACTER_START +i].pos.x += 3.0;
}

int scene_1_update() {

	//Scene 1의 Main문
	//while문 안에 있다 --> 매 frame마다 실행됨

	int dir = rand() % 4, img = rand() % 8, i;
	for (i = 0; i < 8; i++) {
		if (img == i) Stack.objs[CHARACTER_START + i].enable = true;
		else Stack.objs[CHARACTER_START + i].enable = false;
	}
	//al_draw_bitmap(al_load_bitmap(path), spritex, spritey, NULL);
	//al_flip_display();
	switch (dir) {
	case 0: move_left(); break;
	case 1: move_up(); break;
	case 2: move_right(); break;
	case 3: move_down(); break;
	}

	//al_clear_to_color(al_map_rgb(204, 225, 152));

	if (!explain_stat) { //stat설명 팝업 띄우기
		explain_stat=1;
		popup = create_object("Resources\\dummy\\popup.png", 310, 130);
		Stack.push(&Stack, popup);
		object_t text1 = create_object(NULL, 370, 150);
		ui_set_text(&text1, al_map_rgb(255, 255, 255), "Resources\\font\\NanumGothic.ttf", ALLEGRO_ALIGN_LEFT, al_get_config_value(conf, "korean", "explain_stat_1"), 36);
		Stack.push(&Stack, text1);
		object_t text2 = create_object(NULL, 370, 190);
		ui_set_text(&text2, al_map_rgb(255, 255, 255), "Resources\\font\\NanumGothic.ttf", ALLEGRO_ALIGN_LEFT, al_get_config_value(conf, "korean", "explain_stat_2"), 36);
		Stack.push(&Stack, text2);
		object_t text3 = create_object(NULL, 370, 230);
		ui_set_text(&text3, al_map_rgb(255, 255, 255), "Resources\\font\\NanumGothic.ttf", ALLEGRO_ALIGN_LEFT, al_get_config_value(conf, "korean", "explain_stat_3"), 36);
		Stack.push(&Stack, text3);
		object_t text4 = create_object(NULL, 370, 270);
		ui_set_text(&text4, al_map_rgb(255, 255, 255), "Resources\\font\\NanumGothic.ttf", ALLEGRO_ALIGN_LEFT, al_get_config_value(conf, "korean", "explain_stat_4"), 36);
		Stack.push(&Stack, text4);
	}

	if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && clicked && explain_stat && !event_func[0].isStarted) {
		int c = Stack.counter;
		clicked = false;
		
		for (int i = 5; i > 0; i--) {
			Stack.objs[c - i].enable = false;
		}
		al_start_timer(timer);
		printf("timer start\n");
	}
	else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && explain_stat) {//아무데나 누르면 팝업 없애기
		clicked = true;
	}


#define EVENT_TIME 1
	if (al_get_timer_count(timer) - timer_set > (EVENT_TIME*1000)) {
		printf("timer : %lld\n", al_get_timer_count(timer));
		timer_set = al_get_timer_count(timer);
		for (event_num = 0; event_num < EVENTCOUNT; event_num++) {
			if (!event_func[event_num].isStarted) {
				event_func[event_num].func();
				printf("%d event start\n", event_num);
				break;
			}
		}
	}

	re_draw();

	return 0;
}


int scene_1_fin() {

	// 이 씬에서 다른 씬으로 넘어갈 때, 한 번 실행되는 함수.
	Stack.clear(&Stack);

	al_destroy_config(conf);
	al_destroy_font(font);
	al_destroy_timer(timer);

	return 0;
}

void scene_1_on_click_button_0() {
	if (brightness != 1){
		brightness = 1;
	}
	else
	{
		brightness = 0.1;
	}
	puts("clicked");
}


//단톡방 초대
void invitation() {
	al_stop_timer(timer);
	printf("stop timer\n");

	printf("invitation\n");
	event_func[0].isStarted = true;
	object_t eback = create_object("Resources\\dummy\\event_background.png", 0,0);
	Stack.push(&Stack, eback);

	object_t messagebox = create_object("Resources\\dummy\\kakaotalk.png", 365, 210);
	Stack.push(&Stack, messagebox);
	object_t yes = create_object("Resources\\dummy\\yes_button.png", 365, 380);
	ui_set_button(&yes);
	ui_set_on_click_listener(&yes, clicked_yes);
	Stack.push(&Stack, yes);
	object_t no = create_object("Resources\\dummy\\no_button.png", 640, 380);
	ui_set_button(&no);
	ui_set_on_click_listener(&no, clicked_no);
	Stack.push(&Stack, no);
	object_t message_0 = create_object(NULL, 470, 245);
	ui_set_text(&message_0, al_map_rgb(255, 255, 255), "Resources\\font\\NanumGothic.ttf", ALLEGRO_ALIGN_LEFT, al_get_config_value(conf, "korean", "message0_0"), 40);
	Stack.push(&Stack, message_0);
	object_t message_1 = create_object(NULL, 470, 295);
	ui_set_text(&message_1, al_map_rgb(255, 255, 255), "Resources\\font\\NanumGothic.ttf", ALLEGRO_ALIGN_LEFT, al_get_config_value(conf, "korean", "message0_1"), 32);
	Stack.push(&Stack, message_1);
	object_t message_2 = create_object(NULL, 470, 335);
	ui_set_text(&message_2, al_map_rgb(255, 255, 255), "Resources\\font\\NanumGothic.ttf", ALLEGRO_ALIGN_LEFT, al_get_config_value(conf, "korean", "message0_2"), 32);
	Stack.push(&Stack, message_2);
}


//미리정모
void first_meeting() { 
	al_stop_timer(timer);
	printf("stop timer\n");

	printf("first_meeting\n");
	event_func[1].isStarted = true;
	object_t messagebox = create_object("Resources\\dummy\\kakaotalk.png", 365, 210);
	Stack.push(&Stack, messagebox);
	object_t yes = create_object("Resources\\dummy\\yes_button.png", 365, 380);
	ui_set_button(&yes);
	ui_set_on_click_listener(&yes, clicked_yes);
	Stack.push(&Stack, yes);
	object_t no = create_object("Resources\\dummy\\no_button.png", 640, 380);
	ui_set_button(&no);
	ui_set_on_click_listener(&no,clicked_no);
	Stack.push(&Stack, no);
	object_t message_0 = create_object(NULL, 470, 245);
	ui_set_text(&message_0, al_map_rgb(255, 255, 255), "Resources\\font\\NanumGothic.ttf", ALLEGRO_ALIGN_LEFT, al_get_config_value(conf, "korean", "message1_0"), 40);
	Stack.push(&Stack, message_0);
	object_t message_1 = create_object(NULL, 470, 295);
	ui_set_text(&message_1, al_map_rgb(255, 255, 255), "Resources\\font\\NanumGothic.ttf", ALLEGRO_ALIGN_LEFT, al_get_config_value(conf, "korean", "message1_1"), 32);
	Stack.push(&Stack, message_1);
	object_t message_2 = create_object(NULL, 470, 335);
	ui_set_text(&message_2, al_map_rgb(255, 255, 255), "Resources\\font\\NanumGothic.ttf", ALLEGRO_ALIGN_LEFT, al_get_config_value(conf, "korean", "message1_2"), 32);
	Stack.push(&Stack, message_2);
} 

//새내기 미리배움터
void newbie_before_study() { 	
	al_stop_timer(timer);
	printf("stop timer\n");

	printf("newbie_before_study\n");
	event_func[2].isStarted = true;
	object_t messagebox = create_object("Resources\\dummy\\kakaotalk.png", 365, 210);
	Stack.push(&Stack, messagebox);
	object_t yes = create_object("Resources\\dummy\\yes_button.png", 365, 380);
	ui_set_button(&yes);
	ui_set_on_click_listener(&yes, clicked_yes);
	Stack.push(&Stack, yes);
	object_t no = create_object("Resources\\dummy\\no_button.png", 640, 380);
	ui_set_button(&no);
	ui_set_on_click_listener(&no, clicked_no);
	Stack.push(&Stack, no);
	object_t message_0 = create_object(NULL, 470, 245);
	ui_set_text(&message_0, al_map_rgb(255, 255, 255), "Resources\\font\\NanumGothic.ttf", ALLEGRO_ALIGN_LEFT, al_get_config_value(conf, "korean", "message2_0"), 40);
	Stack.push(&Stack, message_0);
	object_t message_1 = create_object(NULL, 470, 295);
	ui_set_text(&message_1, al_map_rgb(255, 255, 255), "Resources\\font\\NanumGothic.ttf", ALLEGRO_ALIGN_LEFT, al_get_config_value(conf, "korean", "message2_1"), 32);
	Stack.push(&Stack, message_1);
	object_t message_2 = create_object(NULL, 470, 335);
	ui_set_text(&message_2, al_map_rgb(255, 255, 255), "Resources\\font\\NanumGothic.ttf", ALLEGRO_ALIGN_LEFT, al_get_config_value(conf, "korean", "message2_2"), 32);
	Stack.push(&Stack, message_2);
}

//새내기 정모
void newbie_meeting() { 
	al_stop_timer(timer);
	printf("stop timer\n");

	printf("newbie_meeting\n");
	event_func[3].isStarted = true;
	object_t messagebox = create_object("Resources\\dummy\\kakaotalk.png", 365, 210);
	Stack.push(&Stack, messagebox);
	object_t yes = create_object("Resources\\dummy\\yes_button.png", 365, 380);
	ui_set_button(&yes);
	ui_set_on_click_listener(&yes, clicked_yes);
	Stack.push(&Stack, yes);
	object_t no = create_object("Resources\\dummy\\no_button.png", 640, 380);
	ui_set_button(&no);
	ui_set_on_click_listener(&no, clicked_no);
	Stack.push(&Stack, no);
	object_t message_0 = create_object(NULL, 470, 245);
	ui_set_text(&message_0, al_map_rgb(255, 255, 255), "Resources\\font\\NanumGothic.ttf", ALLEGRO_ALIGN_LEFT, al_get_config_value(conf, "korean", "message3_0"), 40);
	Stack.push(&Stack, message_0);
	object_t message_1 = create_object(NULL, 470, 295);
	ui_set_text(&message_1, al_map_rgb(255, 255, 255), "Resources\\font\\NanumGothic.ttf", ALLEGRO_ALIGN_LEFT, al_get_config_value(conf, "korean", "message3_1"), 32);
	Stack.push(&Stack, message_1);
	object_t message_2 = create_object(NULL, 470, 335);
	ui_set_text(&message_2, al_map_rgb(255, 255, 255), "Resources\\font\\NanumGothic.ttf", ALLEGRO_ALIGN_LEFT, al_get_config_value(conf, "korean", "message3_2"), 32);
	Stack.push(&Stack, message_2);
}

//새내기 배움터
void newbie_study() { 
	al_stop_timer(timer);
	printf("stop timer\n");

	printf("newbie_study\n");
	event_func[4].isStarted = true;
	object_t messagebox = create_object("Resources\\dummy\\kakaotalk.png", 365, 210);
	Stack.push(&Stack, messagebox);
	object_t yes = create_object("Resources\\dummy\\yes_button.png", 365, 380);
	ui_set_button(&yes);
	ui_set_on_click_listener(&yes, clicked_yes);
	Stack.push(&Stack, yes);
	object_t no = create_object("Resources\\dummy\\no_button.png", 640, 380);
	ui_set_button(&no);
	ui_set_on_click_listener(&no, clicked_no);
	Stack.push(&Stack, no);
	object_t message_0 = create_object(NULL, 470, 245);
	ui_set_text(&message_0, al_map_rgb(255, 255, 255), "Resources\\font\\NanumGothic.ttf", ALLEGRO_ALIGN_LEFT, al_get_config_value(conf, "korean", "message4_0"), 40);
	Stack.push(&Stack, message_0);
	object_t message_1 = create_object(NULL, 470, 295);
	ui_set_text(&message_1, al_map_rgb(255, 255, 255), "Resources\\font\\NanumGothic.ttf", ALLEGRO_ALIGN_LEFT, al_get_config_value(conf, "korean", "message4_1"), 32);
	Stack.push(&Stack, message_1);
	object_t message_2 = create_object(NULL, 470, 335);
	ui_set_text(&message_2, al_map_rgb(255, 255, 255), "Resources\\font\\NanumGothic.ttf", ALLEGRO_ALIGN_LEFT, al_get_config_value(conf, "korean", "message4_2"), 32);
	Stack.push(&Stack, message_2);
}

//신입생 OT
void newbie_OT() { 
	al_stop_timer(timer);
	printf("stop timer\n");

	printf("newbie_OT\n");
	event_func[5].isStarted = true;
	object_t messagebox = create_object("Resources\\dummy\\kakaotalk.png", 365, 210);
	Stack.push(&Stack, messagebox);
	object_t yes = create_object("Resources\\dummy\\yes_button.png", 365, 380);
	ui_set_button(&yes);
	ui_set_on_click_listener(&yes, clicked_yes);
	Stack.push(&Stack, yes);
	object_t no = create_object("Resources\\dummy\\no_button.png", 640, 380);
	ui_set_button(&no);
	ui_set_on_click_listener(&no, clicked_no);
	Stack.push(&Stack, no);
	object_t message_0 = create_object(NULL, 470, 245);
	ui_set_text(&message_0, al_map_rgb(255, 255, 255), "Resources\\font\\NanumGothic.ttf", ALLEGRO_ALIGN_LEFT, al_get_config_value(conf, "korean", "message5_0"), 40);
	Stack.push(&Stack, message_0);
	object_t message_1 = create_object(NULL, 470, 295);
	ui_set_text(&message_1, al_map_rgb(255, 255, 255), "Resources\\font\\NanumGothic.ttf", ALLEGRO_ALIGN_LEFT, al_get_config_value(conf, "korean", "message5_1"), 32);
	Stack.push(&Stack, message_1);
	object_t message_2 = create_object(NULL, 470, 335);
	ui_set_text(&message_2, al_map_rgb(255, 255, 255), "Resources\\font\\NanumGothic.ttf", ALLEGRO_ALIGN_LEFT, al_get_config_value(conf, "korean", "message5_2"), 32);
	Stack.push(&Stack, message_2);
}



//마지막 이벤트 후 씬 종료
void scene_1_finish() {
	event_func[6].isStarted = true;
	
	load_scene(Scenes.scenes[2]);
}

void clicked_yes()
{
	switch (event_num)
	{
	case 0:
		social_point += 5;
		Stack.objs[Stack.counter - 7].enable =false;
		break;
	case 1:
		social_point += 1;
		break;
	case 2:
		social_point += 1;
		break;
	case 3:
		social_point += 2;
		break;
	case 4:
		social_point += 2;
		break;
	case 5:
		social_point += 2;
		break;
	default:
		printf("default and event_num : %d\n",event_num);
		exit(0);
		break;
	}

	sprintf(spstr, "%0.1f", social_point/10.0);
	ui_set_text(&SP_TEXT, al_map_rgb(0, 0, 255), "Resources\\font\\NanumGothic.ttf", ALLEGRO_ALIGN_CENTER, spstr, 24);

	al_start_timer(timer);
	int c = Stack.counter;

	for (int i = 6; i > 0; i--) {
		Stack.objs[c - i].enable = false;
	}
}

void clicked_no()
{
	switch (event_num)
	{
	case 0:
		social_point -= 10;
		for (int i = 0; i < EVENTCOUNT - 1; i++)
		{
			event_func[i].isStarted = true;
		}
		Stack.objs[Stack.counter - 7].enable = false;
		break;
	case 1:
		social_point -= 1;
		break;
	case 2:
		social_point -= 1;
		break;
	case 3:
		social_point -= 1;
		break;
	case 4:
		social_point -= 2;
		break;
	case 5:
		social_point -= 2;
		break;
	default:
		printf("default and event_num : %d\n", event_num);
		exit(0);
		break;
	}

	sprintf(spstr, "%0.1f", social_point / 10.0);
	ui_set_text(&SP_TEXT, al_map_rgb(0, 0, 255), "Resources\\font\\NanumGothic.ttf", ALLEGRO_ALIGN_CENTER, spstr, 24);

	al_start_timer(timer);
	int c = Stack.counter;

	for (int i = 6; i > 0; i--) {
		Stack.objs[c - i].enable = false;
	}
}