#pragma once
#include "schedule.h"
#include "lectureInfo.h"

//scene 1
extern float social_point;
extern float health_point;
extern int attendance_rate;
extern int grade_point;
//scene 2
extern lectureInfo lectureTable[LECTURE_SIZE];
extern schedule mySchedule;
extern schedule* mySchedulePtr;

//scene 4
//extern void stat_update();