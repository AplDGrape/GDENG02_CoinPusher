// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "THEMovingObj.generated.h"

UCLASS()
class COINPUSHER_API ATHEMovingObj : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATHEMovingObj();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pathing", meta = (ExposeOnSpawn = "true", 
		MakeEditWidget = "true"))
	TArray<FVector> ThePath;

private:
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MoveActor")
	//class USceneComponent* RootScene;


	UPROPERTY(EditDefaultsOnly, Category = "Components")
	class UBoxComponent* BoxCollider;
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	class UStaticMeshComponent* MyMesh;

	//deals specifically for movement
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	class UInterpToMovementComponent* MovementComponent;

	//float RunningTime;

	//UPROPERTY(EditAnywhere, Category = "MoveActor") float Speed;

};
