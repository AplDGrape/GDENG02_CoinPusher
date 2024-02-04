// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "Components/BoxComponent.h"

#include "SpawnCoin.generated.h"

UCLASS()
class COINPUSHER_API ASpawnCoin : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASpawnCoin();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Spawn an actor of specified class
	UFUNCTION(BlueprintCallable) bool SpawnActor();

	//UFUNCTION(BlueprintCallable) void EnableSpawn(bool Enable);

	void startSpawn();
	void stopSpawn();

	bool bSpawn;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool ShouldSpawn = true;

	//Actor class to spawn
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ActorClassToBeSpawned;

	UPROPERTY(EditAnywhere) float AvgSpawnTime = 5.0f;

	UPROPERTY(EditAnywhere) float RandomSpawnTimeOffset = 1.0f;

private:
	//Box size to spawn actor
	UPROPERTY(EditDefaultsOnly) UBoxComponent* SpawnBox;

	UFUNCTION() void SpawnActorSchedule();

	void ScheduleActorSpawn();
	FTimerHandle SpawnTimerHandle;
};
