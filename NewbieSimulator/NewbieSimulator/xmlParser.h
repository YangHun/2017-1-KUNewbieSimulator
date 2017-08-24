#pragma once
#include"lectureInfo.h"
#include<libxml\parser.h>
#include"stringSwitch.h"
#pragma comment(lib, "Ws2_32.lib")
int atoiCustom(char* key, int isDistance);
timeListPtr registerTimeList(char* key);
void registerEvaluation(char* key, int evaluationArray[]);
void registerTuition(char* key, int tuitionArray[]);
void xmlParse(lectureInfo lectureTable[]);