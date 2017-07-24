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
	CORE //�ٽɱ���
} classifyNumber;

typedef enum _roomNumber {
	ROOM_DEFAULT,
	EDUCATE, // ������
	REFINEMENT, // �����
	INFORMATICS, // �����
	SCI_LIBRARY, // ������
	SCIENCE_HALL, // ���а�
	NEW_LAW_HALL, // ���а��Ű�
	LP_HALL, // L-P��
	WEST_HALL, // ����
	POLITIC // �����

} roomNumber;

typedef enum _ratingNumber {
	RATING_DEFAULT,
	GOOD,
	NORMAL,
	BAD
} ratingNumber;

typedef enum _whatDay {
	MON,
	TUE,
	WED,
	THU,
	FRI,
	SAT,
	SUN,
	DAY_DEFAULT
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
	unsigned char identifyNumber[8]; //�м���ȣ
	unsigned char name[75]; // ���Ǹ�
	enum classifyNumber classify; // ��������/�ٽ�/���� ���� �з�
	enum roomNumber room; // ���ǽ�
	enum Rating klueRating; // klue��
	int distance; // �Ÿ�
	timeListPtr lectureTime;
	unsigned char timeString[30];
} lectureInfo;
