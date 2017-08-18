#pragma once
#include "schedule.h"
#include "lectureInfo.h"
#define MAX_CREDIT 19

void init_mySchedule(schedule* mySchedulePtr);
void printSchedule(schedule mySchedule);
void addLectureToSchedule(lectureInfo lectureTable[], schedule* mySchedulePtr, int index);
void deleteLectureFromSchedule(lectureInfo lectureTable[], schedule* mySchedulePtr, int index);
int analyzeSchedule(lectureInfo lectureTable[], schedule mySchedule, int index);
