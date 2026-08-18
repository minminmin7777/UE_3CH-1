#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingObject.generated.h"

UCLASS()
class CH3_API AMovingObject : public AActor
{
	GENERATED_BODY()
	
public:	
	AMovingObject();

protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Componnent")
	USceneComponent* SceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Componnent")
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	UStaticMesh* DefaultMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	UMaterialInterface* DefaultMaterial;


	//왔다갔다 움직임
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MoveSpeed;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MoveDistance;//이동거리

	float StartX;//시작 위치
	float Direction;//방향
	

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
