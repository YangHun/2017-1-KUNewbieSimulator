#pragma once
#include"lectureInfo.h"
#include<libxml\parser.h>
#include"stringSwitch.h"
#pragma comment(lib, "Ws2_32.lib")

int atoiCustom(char* key, int isDistance) {
	int k = (isDistance == 0) ? (int)strlen(key) : (int)strlen(key) - 3;
	int sum = 0;
	for (int i = 0; i < k; i++) {
		sum *= 10;
		sum += (key[i] - '0');
	}
	return sum;
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
				timeListPtr tempNode = (timeListPtr)malloc(sizeof(timeList));
				tempNode->timeblock.dayofWeek = whatDayFunc(hangul);
				tempNode->timeblock.period = startTime;
				tempNode->timeblock.interval = endTime - startTime + 1;
				tempNode->next = nullNode->next;
				nullNode->next = tempNode;
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

void registerEvaluation(char* key, int evaluationArray[]) {
	unsigned char hangul[12];
	unsigned char soojja[6];
	int hangulMode = 1;
	int i = 0;
	int j = 0;
	int whatEval;
	int howMuch;
	for (int k = 0; k < EVALUATION_SIZE; k++) {
		evaluationArray[k] = 0;
	}
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
				soojja[j] = '\0';
				j = 0;
				hangulMode = 1;
				whatEval = getEvalMessage(hangul);
				howMuch = atoiCustom(soojja, 0);
				evaluationArray[whatEval] = howMuch;

			}
			else { // just number
				soojja[j] = key[i];
				j++;
			}
		}
		i++;
	}
}

void registerTuition(char* key, int tuitionArray[]) {
	unsigned char hangul[9];
	int hangulMode = 1;
	int i = 0;
	int j = 0;
	int whatTuition;
	for (int k = 0; k < TUITION_SIZE; k++) {
		tuitionArray[k] = 0;
	}
	while (key[i] != '\0') {
		if (key[i] != ' ') {
			hangul[j] = key[i];
			j++;
		}
		else {
			hangul[j] = '\0';
			whatTuition = getTuitionMessage(hangul);
			tuitionArray[whatTuition] = 1;
			j = 0;
		}
		i++;
	}
	hangul[j] = '\0';
	whatTuition = getTuitionMessage(hangul);
	tuitionArray[whatTuition] = 1;
	j = 0;
}

void xmlParse(lectureInfo lectureTable[]) {
	xmlDocPtr doc;
	xmlNodePtr cur;
	xmlNodePtr savePoint1;
	xmlNodePtr savePoint2;
	xmlChar* key;
	unsigned char* nameString;
	int i;
	int keyLength = 0;

	doc = xmlParseFile("Resources\\xml\\dummy-beta.xml");
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
	cur = cur->children;
	i = 0;
	while (cur != NULL) { //cur : text major text core -> ...
		savePoint1 = cur;
		if (!strcmp(cur->name, "major") || !strcmp(cur->name, "selective") || !strcmp(cur->name, "core")) {

			lectureTable[i].classify = getClassifyMessage(cur->name);
			cur = cur->children;
			while (cur != NULL) { //cur : text code text class ...
				savePoint2 = cur;
				nameString = cur->name;
				if (getElementMessage(nameString) != XML_MESSAGE_DEFAULT) {
					cur = cur->children;
					key = xmlNodeListGetString(doc, cur, 1);
					keyLength = (int)strlen(key);
					switch (getElementMessage(nameString)) {
					case CODE:
						strcpy_s(lectureTable[i].identifyNumber, sizeof(lectureTable[i].identifyNumber), key);
						break;
					case NAME:
						strcpy_s(lectureTable[i].name, sizeof(lectureTable[i].name), key);
						break;
					case CREDIT:
						lectureTable[i].credit = atoiCustom(key, 0);
						break;
					case TIME:
						strcpy_s(lectureTable[i].timeString, sizeof(lectureTable[i].timeString), key);
						lectureTable[i].lectureTime = registerTimeList(key);
						break;
					case ROOM:
						lectureTable[i].room = getRoomMessage(key);
						break;
					case DISTANCE:
						lectureTable[i].distance = atoiCustom(key, 1);
						break;
					case KLUE:
						lectureTable[i].klueRating = getKlueMessage(key);
						break;
					case ATTENDANCE:
						lectureTable[i].Att = getAttMessage(key);
						break;
					case EVAL:
						strcpy_s(lectureTable[i].evalString, sizeof(lectureTable[i].evalString), key);
						registerEvaluation(key, lectureTable[i].evaluationArray);
						break;
					case TUITION:
						strcpy_s(lectureTable[i].tuitionString, sizeof(lectureTable[i].tuitionString), key);
						registerTuition(key, lectureTable[i].tuitionArray);
						break;
					case XML_MESSAGE_DEFAULT:
						break;
					default:
						break;
					}
					xmlFree(key);
				}
				cur = savePoint2;
				cur = cur->next;
			}
			i++;
		}
		cur = savePoint1;
		cur = cur->next;
	}
	for (int i = 0; i < LECTURETABLE_SIZE; i++) {
		printf("%s \n", lectureTable[i].identifyNumber);
		switch (lectureTable[i].classify)
		{
		case CORE:
			printf("%s \n", u8"�ٽɱ���");
			break;
		case MAJOR:
			printf("%s \n", u8"���ʱ���");
			break;
		case SELECTIVE:
			printf("%s \n", u8"���ñ���");
			break;
		default:
			break;
		}
		printf("%s \n", lectureTable[i].name);
		printf("%d \n", lectureTable[i].credit);
		printf("%s \n", lectureTable[i].timeString);
		for (timeListPtr j = lectureTable[i].lectureTime->next; j != NULL; j = j->next) {
			switch (j->timeblock.dayofWeek)
			{
			case MON:
				printf("%s", u8"��");
				break;
			case TUE:
				printf("%s", u8"ȭ");
				break;
			case WED:
				printf("%s", u8"��");
				break;
			case THU:
				printf("%s", u8"��");
				break;
			case FRI:
				printf("%s", u8"��");
				break;
			case SAT:
				printf("%s", u8"��");
				break;
			case SUN:
				printf("%s", u8"��");
				break;
			default:
				break;
			}
			printf("%d ", j->timeblock.period);
		}
		printf("\n");
		switch (lectureTable[i].room)
		{
		case EDUCATE:
			printf("%s \n", u8"������");
			break;
		case REFINEMENT:
			printf("%s \n", u8"�����");
			break;
		case INFORMATICS:
			printf("%s \n", u8"�����");
			break;
		case SCI_LIBRARY:
			printf("%s \n", u8"������");
			break;
		case SCIENCE_HALL:
			printf("%s \n", u8"���а�");
			break;
		case NEW_LAW_HALL:
			printf("%s \n", u8"���а��Ű�");
			break;
		case LP_HALL:
			printf("%s \n", u8"L-P��");
			break;
		case WEST_HALL:
			printf("%s \n", u8"����");
			break;
		case POLITIC:
			printf("%s \n", u8"�����");
			break;
		default:
			break;
		}
		printf("%d%s \n", lectureTable[i].distance, u8"��");
		switch (lectureTable[i].klueRating)
		{
		case KLUE_GOOD:
			printf("%s \n", u8"�ܰ�");
			break;
		case KLUE_NORMAL:
			printf("%s \n", u8"����");
			break;
		case KLUE_BAD:
			printf("%s \n", u8"����");
			break;
		default:
			break;
		}
		switch (lectureTable[i].Att)
		{
		case ATT_LOOSE:
			printf("%s \n", u8"����");
			break;
		case ATT_NORMAL:
			printf("%s \n", u8"����");
			break;
		case ATT_TIGHT:
			printf("%s \n", u8"Į����");
			break;
		default:
			break;
		}
		printf("%s \n", lectureTable[i].evalString);
		for (int ii = 0; ii < EVALUATION_SIZE; ii++) {
			if (lectureTable[i].evaluationArray[ii] != 0) {
				switch (ii) {
				case EVAL_MIDDLE_EXAM:
					printf(u8"�߰� ");
					break;
				case EVAL_FINAL_EXAM:
					printf(u8"�⸻ ");
					break;
				case EVAL_ASSIGNMENT:
					printf(u8"�߰� ");
					break;
				case EVAL_PRESENTATION:
					printf(u8"�߰� ");
					break;
				case EVAL_ATTENDANCE:
					printf(u8"�߰� ");
					break;
				case EVAL_UNDETERMINED_1:
					printf(u8"�߰� ");
					break;
				case EVAL_UNDETERMINED_2:
					printf(u8"�߰� ");
					break;
				default:
					break;
				}
				printf("%d \n", lectureTable[i].evaluationArray[ii]);
			}
		}
		printf("%s \n", lectureTable[i].tuitionString);
		for (int ii = 0; ii < TUITION_SIZE; ii++) {
			if (lectureTable[i].tuitionArray[ii] != 0) {
				switch (ii) {
				case TUI_DEBATION:
					printf(u8"��� ");
					break;
				case TUI_PRESENTATION:
					printf(u8"��ǥ ");
					break;
				case TUI_LECTURE:
					printf(u8"���� ");
					break;
				case TUI_QUIZ:
					printf(u8"���� ");
					break;
				case TUI_UNDETERMINED_3:
					printf(u8"��3 ");
					break;
				case TUI_UNDETERMINED_4:
					printf(u8"��4 ");
					break;
				case TUI_DEFAULT:
					break;
				default:
					break;
				}
			}
		}

		printf("\n\n");
	}
	xmlFreeDoc(doc);
	xmlCleanupParser();
}