ex) Star 파티클 시스템 만들기 


1. 머터리얼 만들기 => texture을 스타로 골라주고, 전체 블렌드 모드에서 additive 설정후,,
빛의 영향을 받지 않게 하기 위해 => unlit을 사용해준다.

2. 파티클 컬러와 곱해줘서, 그림과 같이 노드네트워크를 연결함.


3. 만들었다면, 파티클 시스템 하나 새로 생성해서, 
아까 만든 파티클을 추가해준다.

4. 이미터에서 required 모듈을 선택후, 스타 적용
5. 이미터의 spawn 클릭하고 스폰 distribution을 60으로 설정.
6. 이미터 빈칸에 location 모듈을 설치해서 범위를 설정하여 스폰 지점을 다양하게 해준다.
7. 이미터의 lifetime에서 min을 0.5, max 를 2.0으로 설정해서 파티클 생존 기간이 0.5~2.0초로 설정
8. 이미터의 initial velocity를 통해서 max값과 min값을 조절해줌
9. 이미터의 initial rotation을 이용해서 빙글빙글 돌면서 올라가게 설정해줌
10. 이미터의 initial size를 통해 min값과 max값을 조정하는데, 이때 y,z는 상관 x 인것이, 평면이 그대로 올라가는 것이라 괜찮다

11. 마무리로 적당히 zoom 해서 섬네일을 클릭하면 해당 파티클 시스템의 이미지가 적용이 된다.

constant => 하나의 값
uniform 범위 지정 가능
curve => 시간에 따라 변화가 가능



번외로, 
spawn의 burst를 통해 => 이떄는 constant 값을 0으로 설정하고 만진다.
burst의 burst 리스트 추가후, count, countlow, time을 설정해주는데 각각
count는 갯수, count low는 최소 갯수, time은 설정한 초 마다~


번외 2
Required에서 Emitter loop를 설정하면 그만큼만 반복하고 종료한다.

그리고 kill on complete를 해주어, 동작이 끝나면 제거하도록 한다.


번외 3 acceration 이미터 추가후, distribution => constant 변경후 z 를 -200으로 변경하면 
아래로 떨어지는 효과를 줄 수 있다.





















