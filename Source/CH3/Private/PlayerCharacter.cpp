#include "PlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "MyPlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	Capsule->SetSimulatePhysics(false);// 물리엔진 끔
	Capsule->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics); // 충돌 감지를 켜줌
	Capsule->SetCollisionProfileName(TEXT("Pawn")); // "나는 Pawn이다" 라는 충돌 규칙 세트 적용
	SetRootComponent(Capsule);
	
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMesh->SetSimulatePhysics(false);
	SkeletalMesh->SetupAttachment(Capsule);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(Capsule);
	SpringArm->TargetArmLength = 200.f;//
	SpringArm->bUsePawnControlRotation = false;//
	SpringArm->bDoCollisionTest = false; // 카메라 시점 변화 완전히 없앰

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (AMyPlayerController* PlayerController = Cast<AMyPlayerController>(GetController()))
		{
			if (PlayerController->MoveAction)
			{
				EnhancedInput->BindAction(//액션을 바인딩(연결)한다는 의미
					PlayerController->MoveAction,// IA를 가져옴 키 입력 감지
					ETriggerEvent::Triggered,//키가 눌려서 이벤트가 발생했을때 계속 발생
					this,
					&APlayerCharacter::Move
				);
			}

			if (PlayerController->JumpAction)
			{
				EnhancedInput->BindAction(
					PlayerController->JumpAction,
					ETriggerEvent::Triggered,
					this,
					&APlayerCharacter::StartJump
				);

				EnhancedInput->BindAction(
					PlayerController->JumpAction,
					ETriggerEvent::Completed,//키 누르는거 끝났을때
					this,
					&APlayerCharacter::StopJump
				);
			}

			if (PlayerController->LookAction)
			{
				EnhancedInput->BindAction(
					PlayerController->LookAction,
					ETriggerEvent::Triggered,
					this,
					&APlayerCharacter::Look
				);
			}

			if (PlayerController->SprintAction)
			{
				EnhancedInput->BindAction(
					PlayerController->SprintAction,
					ETriggerEvent::Triggered,
					this,
					&APlayerCharacter::StartSprint
				);

				EnhancedInput->BindAction(
					PlayerController->SprintAction,
					ETriggerEvent::Completed,
					this,
					&APlayerCharacter::StopSprint
				);
			}
		}
	}
}		

void APlayerCharacter::Move(const FInputActionValue& value)
{
	const FVector2D MoveInput = value.Get<FVector2D>();
	const float DeltaTime = GetWorld()->GetDeltaSeconds();
	float CurrentSpeed = MoveSpeed * (bIsSprinting ? SprintMultiplier : 1.f);//3항 연산자. 조건? 참 : 거짓일때

	FVector LocalOffset = FVector(MoveInput.X, MoveInput.Y, 0.f) * CurrentSpeed * DeltaTime;
	AddActorLocalOffset(LocalOffset, true);

}
void APlayerCharacter::StartJump(const FInputActionValue& value)
{
}
void APlayerCharacter::StopJump(const FInputActionValue& value)
{
}
void APlayerCharacter::Look(const FInputActionValue& value)
{
	const FVector2D LookInput = value.Get<FVector2D>();
	const float DeltaTime = GetWorld()->GetDeltaSeconds();

	float YawDelta = LookInput.X * RotationSpeed * DeltaTime;
	float PitchDelta = LookInput.Y * RotationSpeed * DeltaTime;

	AddActorLocalRotation(FRotator(0.f, YawDelta, 0.f));

	SpringArm->AddLocalRotation(FRotator(PitchDelta, 0.f, 0.f));
}
void APlayerCharacter::StartSprint(const FInputActionValue& value)
{
	bIsSprinting = true;
}
void APlayerCharacter::StopSprint(const FInputActionValue& value)
{
	bIsSprinting = false;
}