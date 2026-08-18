#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RotatingObject.generated.h"

UCLASS()
class CH3_API ARotatingObject : public AActor
{
	GENERATED_BODY()
	
public:	
	ARotatingObject();

protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Componnent")
	USceneComponent* SceneRoot;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Componnent")
	UStaticMeshComponent* StaticMeshComp;
	UPROPERTY(EditAnywhere, Category = "Rotation")
	float RotationSpeed;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
