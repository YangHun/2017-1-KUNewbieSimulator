#pragma once
#include"lectureInfo.h"
typedef enum _isEmpty {
	ISEMPTY_DEFAULT, //�ʱⰪ.
	EMPTY, // �� �ð��뿡 ���ǰ� ����
	NONEMPTY // ����
} isEmpty;

typedef struct _strList {
	char* str;
	struct _strList* next;
} strList;

typedef strList* strListPtr;

typedef struct _timetableInfo {
	char* name; // ���Ǹ�
	enum roomNumber room; // ���ǽ�
	enum isEmpty isEmptyBit; // ������� �Ⱥ������ Ȯ��
} timetableInfo;

typedef struct _schedule {
	int gradePoint;
	strListPtr idNumberList;
	timetableInfo timeTable[5][10]; //5���� 10����
} schedule;