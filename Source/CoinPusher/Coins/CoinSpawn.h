// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

#include "CoinSpawn.generated.h"

UCLASS()
class COINPUSHER_API ACoinSpawn : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACoinSpawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	//void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Static mesh to render
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMesh;

	//Spawn an actor of specified class
	//UFUNCTION(BlueprintCallable) bool SpawnActor();

	//UFUNCTION(BlueprintCallable) void EnableSpawn(bool Enable);

	/*void startSpawn();
	void stopSpawn();

	bool bSpawn;*/

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//bool ShouldSpawn = true;

	////Actor class to spawn
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//TSubclassOf<AActor> ActorClassToBeSpawned;

	//UPROPERTY(EditAnywhere) float AvgSpawnTime = 5.0f;

	//UPROPERTY(EditAnywhere) float RandomSpawnTimeOffset = 1.0f;

	//Box size to spawn actors
	/*UPROPERTY(EditDefaultsOnly) UBoxComponent* SpawnBox;

	UFUNCTION() void SpawnActorSchedule();

	void ScheduleActorSpawn();

	FTimerHandle SpawnTimerHandle;*/
};
