#include "RotatingObject.h"

ARotatingObject::ARotatingObject()
{
 
 SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
 SetRootComponent(SceneRoot);

 StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
 StaticMeshComp->SetupAttachment(SceneRoot);//씬루트 밑에 붙이기

 static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset //static 뜻 = 매번 새로 만들지 않고 한 번 만들어서 유지
 (TEXT("/Script/Engine.StaticMesh'/Game/StylizedKitchen/Meshes/SM_Book_01.SM_Book_01'"));
 if (MeshAsset.Succeeded())
 {
	 StaticMeshComp->SetStaticMesh(MeshAsset.Object);
 }

 static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Engine/VREditor/UI/ArrowMaterial.ArrowMaterial"));
 if (MaterialAsset.Succeeded())
 {
	 StaticMeshComp->SetMaterial(0, MaterialAsset.Object);//머티리얼 여러개 넣을 수 있어서 인덱스 붙는거임
 }

PrimaryActorTick.bCanEverTick = true;

RotationSpeed = 90.0f;
}

void ARotatingObject::BeginPlay()
{
	Super::BeginPlay();
	
	SetActorLocation(FVector(300.0f, 200.0f, 100.0f));
	SetActorRotation(FRotator(0.0f, 45.0f, 0.0f));
	SetActorScale3D(FVector(2.0f));
}

void ARotatingObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!FMath::IsNearlyZero(RotationSpeed))
	{
		AddActorLocalRotation(FRotator(0.0f, RotationSpeed * DeltaTime, 0.0f));
	}
}

