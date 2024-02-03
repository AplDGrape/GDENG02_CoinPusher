// Fill out your copyright notice in the Description page of Project Settings.


#include "CoinSpawn.h"

// Sets default values
ACoinSpawn::ACoinSpawn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Setup
	SpawnBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnBox"));
	RootComponent = SpawnBox;
}

// Called when the game starts or when spawned
void ACoinSpawn::BeginPlay()
{
	Super::BeginPlay();

	//respond to when to spawn
	//InputComponent->BindAction("EnterSpawn", IE_Pressed, this, &ACoinSpawn::startSpawn);
	//InputComponent->BindAction("EnterSpawn", IE_Released, this, &ACoinSpawn::stopSpawn);

	//Spawn first
	if (ShouldSpawn)
	{
		ScheduleActorSpawn();
		////Function to key pressed
		//if (bSpawn)
		//{
		//	true;
		//}
		//else
		//{
		//	false;
		//}
	}
}

void ACoinSpawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	//remove all timers associated with object instance
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
}

bool ACoinSpawn::SpawnActor() 
{
	bool SpawnedActor = false;

	if (ActorClassToBeSpawned)
	{
		//Calculate boundary of box
		FBoxSphereBounds BoxBounds = SpawnBox->CalcBounds(GetActorTransform());

		//Compute random position within box bounds
		FVector SpawnLocation = BoxBounds.Origin;
		//origin += negative initial box extent + twice (positive and negative values of bounds) * box extents * rand value
		SpawnLocation.X += -BoxBounds.BoxExtent.X + 2 * BoxBounds.BoxExtent.X * FMath::Rand();
		SpawnLocation.Y += -BoxBounds.BoxExtent.Y + 2 * BoxBounds.BoxExtent.Y * FMath::Rand();
		SpawnLocation.Z += -BoxBounds.BoxExtent.Z + 2 * BoxBounds.BoxExtent.Z * FMath::Rand();

		//Spawn actor at location
		SpawnedActor = GetWorld()->SpawnActor(ActorClassToBeSpawned, &SpawnLocation) != nullptr;
	}

	return SpawnedActor;
}

void ACoinSpawn::SpawnActorSchedule()
{
	SpawnActor();
	if (ShouldSpawn)
	{
		ScheduleActorSpawn();
	}
}

void ACoinSpawn::ScheduleActorSpawn()
{
	//compute time offset to spawn
	float DeltaToNextSpawn = AvgSpawnTime + (-RandomSpawnTimeOffset + 2 * RandomSpawnTimeOffset * FMath::FRand());

	//schedule spawn
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &ACoinSpawn::SpawnActorSchedule, DeltaToNextSpawn, false);
}

void ACoinSpawn::startSpawn()
{
	bSpawn = true;
}

void ACoinSpawn::stopSpawn()
{
	bSpawn = false;
}

//void ACoinSpawn::EnableSpawn(bool Enable)
//{
//	ShouldSpawn = Enable;
//
//	if (Enable)
//	{
//		SpawnActor();
//	}
//}

//void ACoinSpawn::SetupPlayerInputComponent()
//{
//	Super::SetupPlayerInputComponent(PlayerInputComponent);
//}

