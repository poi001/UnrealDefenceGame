# UnrealEngine5로 블루프린트와 C++로 만든 좀비 디펜스 게임입니다.

## 유튜브 링크 ( 이미지를 누르면 유튜브로 넘어갑니다 )

[![Video Label](http://img.youtube.com/vi/VhCWoKUkexA/0.jpg)](https://youtu.be/VhCWoKUkexA)

## 주요 코드

### 카메라 이동

카메라를 담당한 액터를 생성합니다. 그 후, 밑에 함수를 선언하고 정의합니다. 밑에 함수는 마우스 커서가 게임 모서리에 위치해 있을 시, 그 방향으로 카메라가 이동하는 코드입니다.
```
FVector ADGCameraPawn::GetCameraPanningDirection()
{
	float MousePosX = 0.0f;
	float MousePosY = 0.0f;
	float CamDitectionX = 0.0f;
	float CamDitectionY = 0.0f;

	DGPlayerController->GetViewportSize(ScreenSizeX, ScreenSizeY);
	DGPlayerController->GetMousePosition(MousePosX, MousePosY);

	if (MousePosX <= Margine)					//Left
	{
		CamDitectionY = -1.0f;
	}
	if (MousePosY <= Margine)					//Down
	{
		CamDitectionX = 1.0f;
	}
	if (MousePosX >= ScreenSizeX - Margine)		//Right
	{
		CamDitectionY = 1.0f;
	}
	if (MousePosY >= ScreenSizeY - Margine)		//Up
	{
		CamDitectionX = -1.0f;
	}

	return FVector(CamDitectionX, CamDitectionY, 0.0f);
}
```
* `MousePosX`: 화면에서 현재 마우스 커서의 X좌표의 위치를 담는 변수
* `MousePosY`: 화면에서 현재 마우스 커서의 Y좌표의 위치를 담는 변수
* `CamDitectionX`: 카메라의 X좌표 이동 값. (-1이면 왼쪽으로 이동, 1이면 오른쪽, 0이면 이동 안 함)
* `CamDitectionY`: 카메라의 Y좌표 이동 값. (-1이면 위쪽으로 이동, 1이면 아래쪽, 0이면 이동 안 함) (윈도우 좌표계를 사용해서 Y좌표는 위, 아래가 반대이다)
* `Margine`: 마우스 커서를 탐지할 모서리의 크기량을 담은 변수
* `GetViewportSize(ScreenSizeX, ScreenSizeY)`: 화면 크기를 각각 ScreenSizeX, ScreenSizeY에 담는 코드
* `GetMousePosition(MousePosX, MousePosY)`: 마우스의 위치를 담는 코드

위 처럼 화면이 움직이는 방향을 FVector타입으로 반환합니다.


```
void ADGCameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (DGPlayerController->bIsGameMode)
	{
		AddActorWorldOffset(GetCameraPanningDirection() * CamSpeed);
	}
}
```
위 코드는 Tick(매 프레임마다 업데이트)함수의 내용입니다.

* `DGPlayerController->bIsGameMode`: 현재 InputMode가 UI가 아니라 Game모드일 때만 실행
* `AddActorWorldOffset`: 카메라의 이동을 위한 함수
* `GetCameraPanningDirection()`: 위에 설명한 함수
* `CamSpeed`: 카메라 이동속도


### 적 이동
![image](https://github.com/poi001/UnrealDefenceGame/assets/107660181/94d95c8d-e088-442b-937b-2e7fd229f757)

블루프린트로 비교적 쉽게 구현할 수 있었기 때문에 블루프린트로 구현하였습니다.

* `BeginPlay`: 적이 구동이 시작하면 호출되는 노드
* `GetAllActorsOfClass`: 현재 존재하는 액터들 중 지정한 액터를 반환하는 노드(배열을 반환함)
* `Lenth`: 배열의 번호를 담을 변수
* `AIMoveTo`: 지정한 액터를 지정한 목표까지 이동시키는 노드

위에 블루프린트를 설명하자면 좀비 소환되고 BPGoal이란 액터를 모두 찾아낸다.
그 후, 첫번쨰 BPGoal로 움직이고 도착했다면 다음 BPGoal로 이동한다.
참고로 BPGoal은 이 곳이 최종 도착지점인지 확인하는 bool타입의 변수가 있다. 그러므로 오류날 일이 없다.

추가적으로 AutoPossessAI의 설정을 PlacedInWorldOrSpawned로 설정해야지 소환됐을 때, 위 블루프린트가 작동한다.

### 타워 소환 (비동기 에셋 로딩)

타워를 소환할 때, 비동기 에셋과 데이터 테이블을 이용하여 Mesh와 Material을 설정한다.

![image](https://github.com/poi001/UnrealDefenceGame/assets/107660181/cdcc8010-47a8-4f89-b283-c990ce07403e)

해당 프로젝트 파일 경로로 가서 Config폴더에서 새로운 ini파일을 위와 같이 만든다. 타워의 메시와 머티리얼을 담는 내용이다.

`[/Script/UnrealDefenceGame.DGSetting]`: UnrealDefenceGame모듈에서 DGSetting파일을 경로를 지정한다 

그 밑에 +연산자를 사용하여 TowerMesh에 스태틱매시의 경로들을 집어 넣는다.(1단계, 2단계, 3단계)

TowerMaterialInstance에는 타워 타입마다의 머티리얼인스턴스의 경로들을 집어넣는다.(빨, 노, 초, 파, 검)

![image](https://github.com/poi001/UnrealDefenceGame/assets/107660181/a56257c4-5cb9-4a3a-9e7e-6718ac51628d)

UObject를 상속받은 UDGSetting이라는 클래스를 만든 후, FSoftObjectPath타입의 배열을 만든다. (FSoftObjectPath은 경로를 저장하는 타입)

* `UCLASS(config=Setting)`: config은 DefaultSetting.ini로 지정한다는 지정자이다.
* `UPROPERTY(config)`: UPROPERTY안에 config를 지정했으므로 DefaultSetting.ini파일을 사용한다는 코드이다.

위 코드들로 인해 TowerMesh와 TowerMaterialInstance에 DefaultSetting.ini에 적혀있는 경로들을 기입한다.



### 타워 공격 범위


### 데이터 테이블
