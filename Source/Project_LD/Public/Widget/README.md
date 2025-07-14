# Widget Manager

이전 부터 고민하였던 위젯을 관리하여 불필요한 오버해드를 줄이고 생성과 삭제를 한 곳에서 관리하고 싶어 제작하게 되었습니다.

# 📋 목차
- [문제 상황](#문제-상황)
- [동작 방식](#동작-방식)
- [사용법](#사용법)
- [결과 예시](#결과-예시)

# 문제 상황
### 불편했던 위젯 사용
위젯 사용에 대해서는 여러가지의 튜토리얼들이 존재하였습니다 <br/>
공식 홈페이지에서는 게임 인스턴스에 몰아 넣는 방법, 게임 모드에 몰아 넣는 방법을 알려주었고 그렇게 사용하였습니다 <br/>

그러던중 과연 여기에 사용하는 것이 옳은것인가 생각하다가 <br/>
PlayerController가 맞지 않을까? 라는 생각에 이곳에 몰아서 넣었던 기억이 있습니다 <br/>
이 방법만 사용하다가 이곳은 입력을 처리하기 위함이지 위젯까지 처리해야 하나 싶어서 다른 방법을 찾고 있던 중 <br/>

HUD가 눈에 들어왔습니다
PlayerController에 접근이 쉽게 가능하며 오직 클라이언트에만 존재하는 곳 <br/>
유저 인터페이스를 사용하기에도 어색함 없이 사용하기에 좋은 곳이라고 생각하여 <br/>
이곳에서 위젯 매니저를 만들어 보기로 생각을 하였습니다 <br/>

# 동작 방식

<img width="917" height="258" alt="image" src="https://github.com/user-attachments/assets/06760796-3895-47a1-b5a1-ffb72f71cf53" />

우선 기본적인 동작 방식은 위젯을 넣는 것 부터 시작합니다 <br/>
다음은 공통적으로 사용될 위젯을 넣은 것이고 <br/>
추가적으로 자식을 늘려 개인적으로 사용될 것을 넣습니다 <br/>
이러면 절약할 수 있지 않을까? 라고 생각하였습니다 <br/>

<img width="496" height="189" alt="image" src="https://github.com/user-attachments/assets/2d244e13-4cb3-4b3e-9537-faf1a8db62ed" />

그렇게 다음과 같은 초기화 방식을 거치게 됩니다 <br/>
위젯을 추가하고 보이지 않게 설정합니다 <br/>
여기에서 저는 BW_(어떤 위젯) <br/>
이라는 고정적인 이름을 사용하게 됩니다 <br/>
그래서 BW_를 삭제하는 작업도 해줍니다 <br/>
이 부분은 아래에서 설명 드리겠습니다 <br/>

<img width="445" height="97" alt="image" src="https://github.com/user-attachments/assets/8da4d0e8-6aec-4d1b-b891-e6c118dceec9" />

이제 본격적으로 위젯을 생성할 것입니다 <br/>
저는 이렇게 이름을 입력하는 방식으로 만들어 보았습니다. (그래서 BW_ 로 통일 하였습니다) <br/>
이를 통해 손쉽게 위젯을 불러오고 Cast하여 사용합니다 <br/>

<img width="366" height="93" alt="image" src="https://github.com/user-attachments/assets/34771cef-bf46-4732-ad6d-615a4df53d69" />

내부적으로 다음과 같이 이름에대한 위치를 찾고 <br/>
해당 위치는 당연히 동일한 위젯일 것 입니다 <br/>
그렇게 불러오면 끝이 납니다 <br/>

<img width="1099" height="324" alt="image" src="https://github.com/user-attachments/assets/d2ae36e9-e44c-485a-af46-462e65b86b84" />

그럼 이제 보여줘야 하는데 이때 UsedWidgets라는 배열이 있고 <br/>
이를 통해 true, false로 값을 알아내서 현재 위젯이 보여지고 있는지에 대한 유무를 알 수 있습니다 <br/>
이를 이용하면 실수로 위젯을 두번 불러온다거나 지우는 일이 없어 오류가 방지 되었습니다 <br/>

 ESlateVisiblity 라던가 IsInViewport를 통해 재검증도 하였습니다 <br/>

# 사용법
Notification위젯을 사용한 방법입니다

<img width="730" height="179" alt="image" src="https://github.com/user-attachments/assets/8fb37c5e-11f9-469a-a543-cdbf0c5ee1cf" />

<img width="1083" height="337" alt="image" src="https://github.com/user-attachments/assets/3d57449e-4775-4679-846f-1944a91b3061" />

# 결과 예시

<img width="304" height="123" alt="image" src="https://github.com/user-attachments/assets/3feecaf3-81a1-4c39-ba49-0633f19563bb" />


