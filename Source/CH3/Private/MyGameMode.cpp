#include "MyGameMode.h"
#include "PlayerCharacter.h"
#include "MyPlayerController.h"

AMyGameMode::AMyGameMode()
{
	DefaultPawnClass = APlayerCharacter::StaticClass();
	PlayerControllerClass = AMyPlayerController::StaticClass();
}