#pragma once
#define TUITION_SIZE 6
#define EVALUATION_SIZE 7
#define LECTURE_SIZE 59
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
	CORE //핵심교양
} classifyNumber;

typedef enum _roomNumber {
	ROOM_DEFAULT,
	EDUCATE, // 교육관
	REFINEMENT, // 교양관
	INFORMATICS, // 정통관
	SCI_LIBRARY, // 과도관
	SCIENCE_HALL, // 이학관
	HANA_SCIENCE, // 과학관
	NEW_LAW_HALL, // 법학관신관
	OLD_LAW_HALL, // 법학관구관
	LP_HALL, // L-P관
	WEST_HALL, // 서관
	POLITIC, // 정경관
	CREATIVE, // 창의관
	FUSION, // 미래융합관
	BIO_HALL, // 생명관
	GYM_HALL, // 화정체육관
	GLOBAL_HALL // 국제관
} roomNumber;

typedef enum _ratingNumber {
	RATING_DEFAULT,
	RATING_VGOOD,
	RATING_GOOD,
	RATING_NORMAL,
	RATING_BAD,
	RATING_VBAD
} ratingNumber;

typedef enum _whatDay {
	MON = 0,
	TUE,
	WED,
	THU,
	FRI,
	SAT,
	SUN,
	DAY_DEFAULT
} whatDay;

typedef struct _timeBlock {
	enum whatDay dayofWeek; //요일
	int period; //교시
	int interval; //연강
} timeBlock;

typedef struct _timeList {
	timeBlock timeblock;
	struct _timeList* next;
} timeList;

typedef timeList* timeListPtr;

typedef struct _evalNode {
	enum evalEnum standard;
	int weight;
} evalNode;

typedef struct _evalList {
	evalNode evalnode;
	struct _evalList* next;
} evalList;

typedef evalList* evalListPtr;

typedef enum _evalEnum {
	EVAL_MIDDLE_EXAM = 0, // 중간
	EVAL_FINAL_EXAM, // 기말
	EVAL_ASSIGNMENT, // 과제
	EVAL_PRESENTATION, // 발표
	EVAL_ATTENDANCE, // 출석
	EVAL_UNDETERMINED_1, // 미1
	EVAL_UNDETERMINED_2, // 미2
	EVAL_DEFALUT
} evalEnum;

typedef enum _tuition_index {
	TUI_DEBATION = 0, //토론
	TUI_PRESENTATION, // 발표
	TUI_LECTURE, //  강의
	TUI_QUIZ, // 퀴즈
	TUI_UNDETERMINED_3, //미정3
	TUI_UNDETERMINED_4, //미정4
	TUI_DEFAULT
} tuition_index;

typedef enum _attendance {
	ATT_VLOOSE, // 매우 느슨
	ATT_LOOSE, //느슨
	ATT_NORMAL, // 보통
	ATT_TIGHT, // 빡빡함
	ATT_VTIGHT // 매우 빡빡
} AttendanceRate;

typedef struct _lectureInfo {
	int credit; //학점
	char identifyNumber[8]; //학술번호
	char name[75]; // 강의명
	enum classifyNumber classify; // 전공관련/핵심/선택 교양 분류
	enum roomNumber room; // 강의실
	enum Rating klueRating; // klue평가
	enum AttendanceRate Att;
	int distance; // 거리
	timeListPtr lectureTime;
	int evaluationArray[EVALUATION_SIZE];
	int tuitionArray[TUITION_SIZE];
	unsigned char timeString[30];
	unsigned char evalString[100];
	unsigned char tuitionString[30];
} lectureInfo;
