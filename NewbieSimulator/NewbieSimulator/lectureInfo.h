#pragma once
typedef enum _messageNumber {
	MESSAGE_DEFAULT,
	NO_OVERLAP,
	TIME_OVERLAP,
	ALREADY_EXIST,
	EXCEED_POINT
} messageNumber;

typedef enum _classifyNumber {
	CLASSIFY_DEFAULT,
	SELECTIVE,//���ñ���
	MAJOR, //�������ñ���
	NUCLEAR //�ٽɱ���
} classifyNumber;

typedef enum _roomNumber {
	ROOM_DEFAULT,
	EDUCATE, // ������
	REFINEMENT // �����
} roomNumber;

typedef enum _ratingNumber {
	RATING_DEFAULT,
	GOOD,
	NORMAL,
	BAD
} ratingNumber;

typedef enum _whatDay {
	DAY_DEFAULT,
	MON = 0,
	TUE,
	WED,
	THU,
	FRI
} whatDay;

typedef struct _timeBlock {
	enum whatDay dayofWeek; //����
	int period; //����
} timeBlock;

typedef struct _timeList {
	timeBlock timeblock;
	struct _timeList* next;
} timeList;

typedef timeList* timeListPtr;

typedef struct _lectureInfo {
	int classNumber; // �й�
	int credit; //����
	char* identifyNumber; //�м���ȣ
	char* name; // ���Ǹ�
	enum classifyNumber classify; // ��������/�ٽ�/���� ���� �з�
	enum roomNumber room; // ���ǽ�
	enum Rating klueRating; // klue��
	timeListPtr lectureTime;
} lectureInfo;