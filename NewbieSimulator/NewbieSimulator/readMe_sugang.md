lectureinfo.h : lecture을 저장하는 lectureInfo 구조체 설명
schedule.h : 현재 플레이에서 시간표 등을 저장하는 schedule 구조체 설명

enum 설명
- messageNumber : analyzer가 검사한 상태를 나타냄. 다시말해서 analyzer의 반환값
- classifyNumber : 선택/전공관련/핵심 교양
- roomNumber : 강의실 위치 설명. 추후 추가할 예정
- ratingNumber : Klue 평에 쓰일 예정
- whatDay : 요일

그 밖에 사항은 어느정도 주석처리 함

lectureInfo의 구조 중 timeList라는 구조체 자료형의 lectureTime
: 이 곳에 시간대를 저장할 예정. Single Linked List 형태이고, 각 노드는 timeBlock이라는, 요일 enum과 int를 담은 구조체를 저장

예시 : 만약 월2 수2 시간대의 강의라면 lectureTime = {NULL} -> {(Mon, 2)} -> {(Wed, 2)} -> {NULL} // 리스트의 헤더는 항상 비워둘 예정이다.

lectureinfo에 다른 부분은 주석처리 되어있음. 궁금한 점은 질문 바람.

schedule 구조체는 timetable이라는, timetableInfo[5][10] 배열과 idNumberList로 이루어져 있다.
idNumberList는 문자열을 저장하는 List의 구조로 이루어져있고, 이 곳에 지금 듣고 있는 강의들의 학술번호를 넣을 예정.
timetableInfo 구조체는 주석으로 설명이 되어있다.

5요일 10교시 시간표임을 감안해서, [5]는 요일을, [10]은 교시를 표현한다.

timetableAnalyzer.c는 함수를 테스트하기 위해서 임의로 만든 소스코드이다.

현재 예시로 올라온 xml파일을 본떠서 lectureTable이라는 배열에 registerLecture라는 함수를 이용해서 저장했다.
프로그램은 mySchedule이라는 변수를 갖고 있고 이를 통해 현재 플레이어의 스케쥴을 저장한다.

while(1)을 통해서 게임에서 일어날 상황을 간이적으로 묘사했다.
우리가 게임을 할 때는 버튼을 눌러서, 그 버튼에 따른 int값을 analyzer에게 보낼 것이다. 그것을 scanf로 대체했다.
analyzeSchedule이라는, analyzer(다시 말해서, 신희성이 짤 함수)는 현재 스케쥴과 인풋을 받아서 앞서말한 messageNumber를 반환한다.

analyzer는 몇가지 경우를 파악해야한다.
1. 학점 초과 - 기존 강의를 지우라고 경고
2. 시간/학술번호 겹침 - 다시 하라고 경고
3. 이미 존재 - 그 강의를 시간표에서 삭제
4. 해당 사항 없음 - 시간표에 강의를 추가

이 외에도 몇가지 사항이 있을 수 있다. 또한 더 효율적인 코드가 생각날 수 있다. 그 경우는 짜는 사람에 재량에 맡겨야한다.
또한 이 코드는 꽤 많이 수정될 것이다. 아직 프로토타이핑만 하고 본 함수를 짜지 않은 것도 많고, 구조도 약간씩 변경할 것이다.
(예시로, 이 문서를 작성하면서 enum은 그냥 따로 헤더 파일 하나 더 만들어서 관리하는게 편하다는 것을 깨달았다.)

그 밖에 이 문서를 읽어도 이해가 안 가는 것이 있다면 질문을 해주세요.
