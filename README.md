# KUNewbieSimulator

2017-1 NDM project : NewbieSimulator

## 저장소 관리 매뉴얼

### user 설정

커미터 이름(`user.name`)은 `git.kucatdog.net`의 로그인 ID와 같도록 한다. Git Bash나 SourceTree에 의해 커미터 이름이 시스템 사용자 이름으로 설정되어 있다면 `git config --local user.name`을 이용해 저장소에 커미터 이름을 설정해 줄 수 있다.

### core 설정

줄 바꿈 문자 자동 변환(`core.autocrlf`)은 끈다(`false`). 이 기능에 관해서는 Git Book 2nd Edition Section 8.1을 참조하라.

## 빌드 매뉴얼

### 빌드 환경

다음과 같은 환경에서 빌드가 가능하다.

* Windows 8.1, Visual Studio Community 2015 표준 C++ 개발 환경
* Windows 10, Visual Studio Community 2017 C++ 데스크톱 개발 환경
    * 이 경우 Windows 8.1 SDK, VC++ v140 도구 집합, NuGet 패키지 관리자를 추가 선택 설치해야 빌드 환경 구성이 완료된다.

### 패키지 의존성

NuGet 패키지 관리자가 패키지 의존성에 따라 자동으로 다음 패키지들을 복원(restore)한다.

* Allegro 5.2.2.1
* AllegroDeps 1.5.0.1

### 프로젝트 구성

NewbieSimulator.vcxproj 프로젝트 속성 페이지에서 Allegro 5의 Add-on을 개별적으로 활성화시킬 수 있다.

Add-on을 활성화/비활성화시킬 때에는 모든 구성 (Debug/Release), 모든 플랫폼 (Win32/x64) 으로 지정하고 설정을 변경하도록 한다.

현재 활성화되어 있는 Add-on은 다음과 같다.

* Image
* Audio
* Dialog
* Primitive
