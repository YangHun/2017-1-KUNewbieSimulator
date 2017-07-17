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
	SELECTIVE,//선택교양
	MAJOR, //전공관련교양
	NUCLEAR //핵심교양
} classifyNumber;

typedef enum _roomNumber {
	ROOM_DEFAULT,
	EDUCATE, // 교육관
	REFINEMENT // 교양관
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
	enum whatDay dayofWeek; //요일
	int period; //교시
} timeBlock;

typedef struct _timeList {
	timeBlock timeblock;
	struct _timeList* next;
} timeList;

typedef timeList* timeListPtr;

typedef struct _lectureInfo {
	int classNumber; // 분반
	int credit; //학점
	char* identifyNumber; //학술번호
	char* name; // 강의명
	enum classifyNumber classify; // 전공관련/핵심/선택 교양 분류
	enum roomNumber room; // 강의실
	enum Rating klueRating; // klue평가
	timeListPtr lectureTime;
} lectureInfo;