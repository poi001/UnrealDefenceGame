# UnrealEngine5.2로 블루프린트와 C++로 만든 좀비 디펜스 게임입니다.

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

위에 블루프린트를 설명하자면 좀비 소환되고 BPGoal이란 액터를 모두 찾아냅니다.
그 후, 첫번쨰 BPGoal로 움직이고 도착했다면 다음 BPGoal로 이동합니다.
참고로 BPGoal은 이 곳이 최종 도착지점인지 확인하는 bool타입의 변수가 있습니다. 그러므로 오류날 일이 없습니다.

추가적으로 AutoPossessAI의 설정을 PlacedInWorldOrSpawned로 설정해야지 소환됐을 때, 위 블루프린트가 작동합니다.

### 타워 소환 (비동기 에셋 로딩)

타워를 소환할 때, 비동기 에셋과 데이터 테이블을 이용하여 Mesh와 Material을 설정합니다.

![image](https://github.com/poi001/UnrealDefenceGame/assets/107660181/cdcc8010-47a8-4f89-b283-c990ce07403e)

해당 프로젝트 파일 경로로 가서 Config폴더에서 새로운 ini파일을 위와 같이 만급니다. 타워의 메시와 머티리얼을 담는 내용입니다.

`[/Script/UnrealDefenceGame.DGSetting]`: UnrealDefenceGame모듈에서 DGSetting파일을 경로를 지정한다 

그 밑에 +연산자를 사용하여 TowerMesh에 스태틱매시의 경로들을 집어 넣습니다.(1단계, 2단계, 3단계)

TowerMaterialInstance에는 타워 타입마다의 머티리얼인스턴스의 경로들을 집어넣습니다.(빨, 노, 초, 파, 검)

![image](https://github.com/poi001/UnrealDefenceGame/assets/107660181/a56257c4-5cb9-4a3a-9e7e-6718ac51628d)

UObject를 상속받은 UDGSetting이라는 클래스를 만든 후, FSoftObjectPath타입의 배열을 만듭니다. (FSoftObjectPath은 경로를 저장하는 타입)

* `UCLASS(config=Setting)`: config은 DefaultSetting.ini로 지정한다는 지정자입니다.
* `UPROPERTY(config)`: UPROPERTY안에 config를 지정했으므로 DefaultSetting.ini파일을 사용한다는 코드입니다.

위 코드들로 인해 TowerMesh와 TowerMaterialInstance에 DefaultSetting.ini에 적혀있는 경로들을 기입합니다.


![image](https://github.com/poi001/UnrealDefenceGame/assets/107660181/7e09818e-dd5d-4257-a7e2-0342ce4f3d89)
![image](https://github.com/poi001/UnrealDefenceGame/assets/107660181/c8e0d848-4c5f-435c-bc44-a51c8b6ffce3)
위의 코드는 비동기 에셋을 활용하여 타워의 메시와 머티리얼을 설정하는 코드입니다.

* `TowerMeshToLoad`: USetting->TowerMesh의 경로를 담는 FSoftObjectPath타입 변수
* `TowerMaterialToLoad`: USetting->TowerMaterialInstance의 경로를 담는 FSoftObjectPath타입 변수
* `DGGameInstance->StreamableManager.RequestAsyncLoad(TowerMeshToLoad,FStreamableDelegate::CreateUObject(this, &ADGTowerActor::OnMeshLoadCompleted))`:
  TowerMeshToLoad가 준비가 됐으면 OnMeshLoadCompleted함수를 실행합니다.
* `DGGameInstance->StreamableManager.RequestAsyncLoad(TowerMaterialToLoad,FStreamableDelegate::CreateUObject(this, &ADGTowerActor::OnMaterialLoadCompleted))`:
  TowerMaterialToLoad가 준비가 됐으면 OnMaterialLoadCompleted함수를 실행합니다.

OnMeshLoadCompleted함수와 OnMaterialLoadCompleted함수는 각각 타워의 메시와 머티리얼을 설정하는 함수입니다.

비동기 에셋으로 인한 장점은 게임에서 발생하는 멈춤 현상이나 차지하는 메모리 양이 훨씬 줄어듭니다.

단점은 메모리에 직접 접근하는 게임플레이 코드가 비동기 로드를 처리하도록 변환해 주는 작업에 시간이 조금 걸린다는 점입니다.

### 타워 공격 범위
![image](https://github.com/poi001/UnrealDefenceGame/assets/107660181/cfec26d9-87b0-4db3-89cb-bcb126220df5)

위 코드는 타워가 Tick함수가 호출될 때마다 감지하도록 짜여져있는 코드입니다.

내용은 적이 타워 탐지 범위 안에 들어와 있을 시(bIsDetected == true), 공격속도 만큼 탄환을 발사하고, 아닐 시에는 계속 탐지합니다.

![image](https://github.com/poi001/UnrealDefenceGame/assets/107660181/4fe94664-3b8b-4615-82e9-9fefffa35cab)

DetectedEnemy() 함수는 적이 탐지되었을 시에 호출되는 함수입니다. DetectingEnemy() 함수는 탐지 중일 때(탐지되지 않았을 시) 호출되는 함수입니다.

DetectingEnemy는 OverlapMultiByChannel를 사용해 적을 탐지합니다. OverlapMultiByChannel의 인자들은 아래와 같습니다.

* `bResult`: 적이 탐지 되었는 지 확인용 bool 변수
* `OverlapResults`: 탐지할 방법을 모아놓은 변수
* `Center`: 감지를 시작할 중앙 위치
* `FQuat::Identity`: 탐색할 도형의 회전
* `ECollisionChannel::ECC_Pawn`: 탐색할 대상의 콜리전 채널
* `FCollisionShape::MakeSphere(512.0f)`: 탐색할 도형의 모양
* `CollisionQueryParam`: 탐색 방법에 대한 설정 값을 모아둔 구조체

그 아래의 코드는 탐지가 되었는지 확인하고 되었으면 탐지된 적들 중, 먼저 탐지된 적을 변수에 넣고 bIsDetected(기본값 false)를 true로 만들고 함수에서 나갑니다.

![image](https://github.com/poi001/UnrealDefenceGame/assets/107660181/4d9a5ab2-d7e9-49f6-ae11-417eb5a1599d)

DetectedEnemy는 DetectingEnemy와 매우 비슷하지만 다른 점이 있습니다. 다른 점은 반복문부터입니다.

탐지된 적을 담은 변수와 이 함수에서 탐지된 적을 비교해서 같은 오브젝트라면 이 함수에서 나갑니다. 아니라면 bIsDetected를 false로 바꿉니다.

이렇게 되면 적을 탐지하고 그 적이 타워 탐지 범위에 벗어 날 때까지 공격을 하다가 벗어나면 다른 적을 탐지하게 됩니다.

### 데이터 테이블(csv)
![image](https://github.com/poi001/UnrealDefenceGame/assets/107660181/2f52b277-d9f5-4b02-836d-12ad5b1cf14a)
![image](https://github.com/poi001/UnrealDefenceGame/assets/107660181/c6c553bd-7853-4c1d-a8cb-a2ceadc166cd)

위에는 적의 데이터를 밑에는 타워의 데이터(타입마다 다름)를 담은 csv파일입니다.

csv파일을 엔진 컨텐츠 브라우저로 옮기면

![image](https://github.com/poi001/UnrealDefenceGame/assets/107660181/f53cb8b7-4892-4f82-a781-6496d040b24e)
![image](https://github.com/poi001/UnrealDefenceGame/assets/107660181/00b2bedf-059c-4e2d-b94c-fb3d3dcd40da)

위와 같이 적용이 됩니다.

이제 C++로 돌아가서 이 데이터 테이블을 적용 시키도록 해보겠습니다.

![image](https://github.com/poi001/UnrealDefenceGame/assets/107660181/4e683cd7-de56-4e7b-b54c-5e2523f8db53)

위에는 GameInstance에서 만든 적 데이터를 담을 구조체

![image](https://github.com/poi001/UnrealDefenceGame/assets/107660181/5996d4c1-2919-4762-be32-892450aa7f30)

위에는 GameInstance에서 만든 타워 데이터를 담을 구조체

![image](https://github.com/poi001/UnrealDefenceGame/assets/107660181/568a5739-0bb6-4be1-9283-7cc741e5efa8)

위에 함수들은 적 구조체와 타워 구조체를 얻어오는 Get함수들

![image](https://github.com/poi001/UnrealDefenceGame/assets/107660181/21d08c77-1b5c-4869-9939-5ccfc6c44fb3)

위에 변수들은 적과 타워(빨, 노, 초, 파, 검)의 데이터를 담을 변수들

![image](https://github.com/poi001/UnrealDefenceGame/assets/107660181/69e9eec2-0a6d-4f73-a636-8aa416e600ba)

아까 적용한 데이터들의 경로들을 변수에 집어넣는 코드

![image](https://github.com/poi001/UnrealDefenceGame/assets/107660181/1721ca64-a629-488f-810e-843a7e607d1e)

적의 데이터 테이블을 얻어오는 함수 정의 부분. FindRow를 사용하여 인자로 넣은 레벨에 해당하는 데이터를 리턴

![image](https://github.com/poi001/UnrealDefenceGame/assets/107660181/723ecf25-a572-4325-bf39-4899a72e2b1c)

타워들의 데이터 테이블을 얻어오는 함수 정의 부분. FindRow를 사용하여 인자로 넣은 레벨에 해당하는 데이터를 리턴.
인자로 받은 타입을 switch문을 통해 구분하고 알맞은 타워 데이터를 반환

위에 과정들을 통해 레벨과 타입에 따라 달라지는 스탯을 알맞게 얻어올 수 있습니다.
