#pragma once
#include "schedule.h"
#include "lectureInfo.h"

//scene 1
extern float social_point;
extern float health_point;
extern float attendance_rate[6];
extern int grade_point;
//scene 2
extern lectureInfo lectureTable[LECTURE_SIZE];
extern schedule mySchedule;
extern schedule* mySchedulePtr;
//scene 3
extern int lectureindex[6];
//scene 4
extern ALLEGRO_CONFIG *conf_for_event;
extern int lectureindex[6];
//extern void stat_update();