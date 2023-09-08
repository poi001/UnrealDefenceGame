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

위 처럼 화면이 움직이는 방향을 FVector타입으로 반환한다.


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
위 코드는 Tick(매 프레임마다 업데이트)함수의 내용이다.

* `DGPlayerController->bIsGameMode`: 현재 InputMode가 UI가 아니라 Game모드일 때만 실행된다
* `AddActorWorldOffset`: 카메라의 이동을 위한 함수
* `GetCameraPanningDirection()`: 위에 설명한 함수
* `CamSpeed`: 카메라 이동속도

### 카메라 이동
