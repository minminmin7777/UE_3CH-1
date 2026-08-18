#include "MyPlayerController.h"
#include "EnhancedInputSubsystems.h"
//로컬 플레이어서브시스템을 통해 맵핑 컨텍스트를 활성화, 비활성화
//ㄴ란? : 플레이중 동적으로 다른 imc를 추가, 제거하여 입력 모드를 전환가능

AMyPlayerController::AMyPlayerController()
	: InputMappingContext(nullptr),
	MoveAction(nullptr),
	LookAction(nullptr),
	JumpAction(nullptr),
	SprintAction(nullptr)

{
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();
	//현재 playercontroller에 연결된 Local Player객체를 가져옴
	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* subsysem =
			LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())//이해안감
		{
			if (InputMappingContext)
			{
				subsysem->AddMappingContext(InputMappingContext, 0);
			}
		}
	}
}