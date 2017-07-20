#pragma once
#include"lectureInfo.h"
#include<libxml\parser.h>
#include"stringAdvance.h"
#pragma comment(lib, "Ws2_32.lib")
typedef enum _XMLelementMessage {
	XML_MESSAGE_DEFAULT,
	CODE,
	CLASS,
	TYPE,
	NAME,
	CREDIT,
	TIME,
	ROOM,
	DISTANCE,
	KLUE
} XMLelementMessage;

int getClassifyMessage(char* name) {
	switchs(name) {
		cases("major")
			return MAJOR;
		cases("selective")
			return SELECTIVE;
		cases("core")
			return CORE;
		defaults
			return CLASSIFY_DEFAULT;

	} switchs_end;
	return 0;
}
int atoiCustom(char* key, int isDistance) {
	int k = (isDistance == 0) ? (int)strlen(key) : (int)strlen(key) - 3;
	int sum = 0;
	for (int i = 0; i < k; i++) {
		sum *= 10;
		sum += (key[i] - '0');
	}
	return sum;
}
int getKlueMessage(char* name) {
	switchs(name) {
		cases(u8"지뢰")
			return BAD;
		cases(u8"꿀강")
			return GOOD;
		defaults
			return NORMAL;
	} switchs_end;
	return 0;
}
int getRoomMessage(char* name) {
	switchs(name) {
		cases(u8"교육관")
			return EDUCATE;
		cases(u8"교양관")
			return REFINEMENT;
		cases(u8"정통관")
			return INFORMATICS;
		cases(u8"과도관")
			return SCI_LIBRARY;
		cases(u8"이학관")
			return SCIENCE_HALL;
		cases(u8"법학관신관")
			return NEW_LAW_HALL;
		cases(u8"L-P관")
			return LP_HALL;
		cases(u8"서관")
			return WEST_HALL;
		cases(u8"정경관")
			return POLITIC;
		defaults
			return ROOM_DEFAULT;
	} switchs_end;
	return 0;
}
int getElementMessage(char* name) {
	switchs(name) {
		cases("code")
			return CODE;
		cases("class")
			return CLASS;
		cases("type")
			return TYPE;
		cases("name")
			return NAME;
		cases("credit")
			return CREDIT;
		cases("time")
			return TIME;
		cases("room")
			return ROOM;
		cases("distance")
			return DISTANCE;
		cases("klue")
			return KLUE;
		defaults
			return XML_MESSAGE_DEFAULT;
	} switchs_end;
	return 0;
}
int whatDayFunc(char hangul[]) {
	switchs(hangul) {
		cases(u8"월")
			return MON;
		cases(u8"화")
			return TUE;
		cases(u8"수")
			return WED;
		cases(u8"목")
			return THU;
		cases(u8"금")
			return FRI;
		cases(u8"토")
			return SAT;
		cases(u8"일")
			return SUN;
		defaults
			return DAY_DEFAULT;

	} switchs_end;
	return 0;
}
timeListPtr registerTimeList(char* key) {
	unsigned char hangul[5];
	int hangulMode = 1;
	int startTime = 0;
	int endTime = 0;
	int timePhase = 0;
	timeListPtr nullNode = (timeListPtr)malloc(sizeof(timeList));
	nullNode->next = NULL;
	int i = 0;
	int j = 0;
	while (key[i] != '\0') {
		if (hangulMode == 1) {
			if (key[i] == '(') {
				hangul[j] = '\0';
				j = 0;
				hangulMode = 0;
			}
			else if (key[i] != ' ') {
				hangul[j] = key[i];
				j++;
			}
		}
		else {
			if (key[i] == ')') {
				if (timePhase == 0 || timePhase == 2) {
					endTime = startTime;
				}
				for (int q = startTime; q <= endTime; q++) {
					timeListPtr tempNode = (timeListPtr)malloc(sizeof(timeList));
					tempNode->timeblock.dayofWeek = whatDayFunc(hangul);
					tempNode->timeblock.period = q;
					tempNode->next = nullNode->next;
					nullNode->next = tempNode;
				}
				startTime = 0;
				endTime = 0;
				timePhase = 0;
				hangulMode = 1;
			}
			else if (key[i] == '-') {
				timePhase = 1;
			}
			else { // just number
				if (timePhase == 0) {
					startTime = key[i] - '0';
					if (key[i + 1] - '0' >= 0 && key[i + 1] - '0' <= 9) {
						timePhase = 2;
					}
				}
				else if (timePhase == 1) {
					endTime = key[i] - '0';
					if (key[i + 1] - '0' >= 0 && key[i + 1] - '0' <= 9) {
						timePhase = 3;
					}
				}
				else if (timePhase == 2) {
					startTime *= 10;
					startTime += key[i] - '0';
				}
				else if (timePhase == 3) {
					endTime *= 10;
					endTime += key[i] - '0';
				}
			}
		}
		i++;
	}
	return nullNode;
}
/*
void xmlParse(lectureInfo lectureTable[]) {
	xmlDocPtr doc;
	xmlNodePtr cur;
	
	xmlNodePtr savePoint1;
	xmlNodePtr savePoint2;
	xmlChar* key;
	unsigned char* nameString;
	int atoiCustomStore;
	int i;
	int keyLength = 0;
	doc = xmlParseFile("Resources\\xml\\dummy-data.xml");
	if (doc == NULL) {
		printf("Document not parsed successfully. \n");
		return;
	}

	cur = xmlDocGetRootElement(doc);

	if (cur == NULL) {
		printf("empty document\n");
		xmlFreeDoc(doc);
		return;
	}

	if (strcmp(cur->name, "root")) {
		printf("document of the wrong type, root node != root \n");
		xmlFreeDoc(doc);
		return;
	}
}*/