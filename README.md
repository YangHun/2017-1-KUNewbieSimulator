# KUNewbieSimulator

2017-1 NDM project : NewbieSimulator

## 저장소 관리

### user 설정

커미터 이름(`user.name`)은 `git.kucatdog.net`의 로그인 ID와 같도록 한다. Git Bash나 SourceTree에 의해 커미터 이름이 시스템 사용자 이름으로 설정되어 있다면 `git config --local user.name`을 이용해 저장소에 커미터 이름을 설정해 줄 수 있다.

### core 설정

줄 바꿈 문자 자동 변환(`core.autocrlf`)은 끈다(`false`). 이 기능에 관해서는 Git Book 2nd Edition Section 8.1을 참조하라.

## 빌드

### 빌드 환경

MSBuild, VC++ v140 도구 집합, Windows 8.1 SDK를 이용해 빌드하며, 다음 환경을 통해 가능하다.

* Visual Studio Community 2015 - Visual C++ 언어 포함
* Visual Studio Community 2017 - C++ 데스크톱 개발 환경 포함
    * 이 경우 Windows 8.1 SDK, VC++ v140 도구 집합, NuGet 패키지 관리자를 추가 선택 설치해야 빌드 환경 구성이 완료된다.
    * VS 2017을 사용하는 경우 솔루션을 열 때 Windows 10 SDK (10.0.14393.0 또는 그 이상), VC++ v141 (또는 그 이상) 도구 집합으로 업그레이드하라는 메시지를 보게 된다. 이 때 업그레이드를 하지 않기 위해서는 위 도구들을 설치해야 한다.
* MSBuild 명령어를 이용해 콘솔에서 빌드하기. 다음 소프트웨어들을 설치해야 한다.
    * [Microsoft Build Tools 2015](https://www.microsoft.com/en-us/download/details.aspx?id=48159), [Visual C++ 2015 Build Tools](http://landinghub.visualstudio.com/visual-cpp-build-tools)
    * [Visual Studio 2017용 Build Tools](https://go.microsoft.com/fwlink/?linkid=840931)로는 빌드할 수 없다.

### 패키지 의존성

NuGet 패키지 관리자가 패키지 의존성에 따라 자동으로 다음 패키지들을 복원(restore)한다.

* Allegro 5.2.2.1
* AllegroDeps 1.5.0.1

### 프로젝트 구성

NewbieSimulator.vcxproj, NewbieSimulatorEngine.vcxproj 프로젝트 속성 페이지에서 Allegro 5의 Add-on을 개별적으로 활성화시킬 수 있다.

Add-on을 활성화/비활성화시킬 때에는 모든 구성 (Debug/Release), 모든 플랫폼 (Win32/x64) 으로 지정하고 설정을 변경하도록 한다.

현재 활성화되어 있는 Add-on은 다음과 같다.

* Image
* Audio
* Dialog
* Primitive

NewbieSimulator.vcxproj 프로젝트는 NewbieSimulatorEngine.vcxproj 프로젝트에 다음과 같이 의존한다.

1. 빌드 순서. NewbieSimulator 이전에 NewbieSimulatorEngine이 빌드하도록 하였다.
2. 포함 경로. NewbieSimulator의 포함 경로로 NewbieSimulatorEngine의 소스 폴더를 지정하였다.
3. 링크 파일. NewbieSimulator의 빌드에 NewbieSimulatorEngine.lib이 함께 링크된다.

### 콘솔창이 잠시 나타났다가 사라질 때에 해결법

1. (프로젝트)/packages/libxml2-vc140-static-32_64.2.9.4/build/native/libxml2-vc140-static-32_64.targets 파일을 연다.
2. 9번째 줄에 있는 libxml2.lib;%(AdditionalDependencies) 를 %(AdditionalDependencies);libxml2.lib 로 수정한다.
3. 저장한 후 리빌드를 실행한다.
4. 만약에 안되면 nuget에서 libxml2를 지운 후 기존 libxml2가 32_64였다면 64를, 64였다면 32_64를 설치한다.