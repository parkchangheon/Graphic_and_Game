
========Appdelegate.cpp=========

22_03_28

1. Appdelegate는 앱의 기본 정보를 정의하는 클래스 파일이다.
앱이 실행되면 Appdelegate에 정의된 속성에 맞추어 앱이 실행된다.

여기서, 표시 영역 및 창의 크기를 바꾸기 위하여,
몇가지 코드를 추가/삭제하였다. 


//80
designResolutionSize : 
내용이 표시될 화면의 크기를 정의하는 Size클래스의 정적 멤버변수이다.

//81 
createWithRect로 바꿔 앞에서 정의한 너비 및 높이에 해당하는 사각형을 glview에 넘겨 그 사각형에 해당하는
크기의 창을 생성하라고 지시.


//99 
glview의 setDesignResolutionSize() 메서드에 너비, 높이, 정책을 넘겨서 화면 표시 영역과 화면 표시 정책을
설정하는 코드를 추가하였다.
화면 표시 영역은 창 크기와 동일한 너비와 높이로 설정하였고, 표시 정책은 SHOW_ALL로 지정하였다.

표시 정책이란, 다중 해상도 및 가로 세로 비율에 관한 것으로,
SHOW_ALL이란 말 그대로 표시되는 가로, 세로 비율을 유지한채, 확대/축소하여 모든 것을 화면에 보여주라는 정책.
화면비가 다를 경우엔 위아래나 좌우에 빈공간(레터박스)로 채워진다.

다른 정책으로는 EXACT_FIT이나 NO_BORDER가 있다.
EXACT_FIT은 가로 세로 비율을 무시하고 창 크기에 표시 영역을 똑같이 맞춘다.
레터박스는 없지만, 화면이 이상하게 늘어날 수 도 있다.

NO_BORDER는 화면비를 유지하는 점에서 SHOW_ALL과 같지만, 빈공간을 넣는 대신 없는 부분을 자른다.





22_03_29

//45
리소스 참조에 쓰일 구조체 Resource를 정의하였다.

//55
해당 구조체를 활용하여, 작은 사이즈와 큰사이즈 구조체를 정의한다.






============StartScene===========

.h
void menuCloseCallback => selector 콜백

CREATE_FUNC(StartScene) => static create() 함수를 실행한다.



.cpp
sprite를 생성하여 씬에 이미지를 띄운다.
auto back 변수를 생성하여 Sprite::create(""); ==> 이떄 파일은 resource에 넣어줄것

#5-3까지함






