// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnCoin.h"

// Sets default values
ASpawnCoin::ASpawnCoin()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	//Set up box range
	SpawnBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnBox"));
	RootComponent = SpawnBox;
}

// Called when the game starts or when spawned
void ASpawnCoin::BeginPlay()
{
	Super::BeginPlay();
	
	//First spawn
	if (ShouldSpawn)
	{
		/*if (bSpawn)
		{
			SpawnActor();
		}*/
		SpawnActor();
		ScheduleActorSpawn();
		//EnableSpawn(bSpawn);
	}
}

// Called every frame
void ASpawnCoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	{
		if (bSpawn)
		{
			SpawnActor();
		}
	}
}

void ASpawnCoin::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	//remove all timers associated with object instance
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
}
 
// Called to bind functionality to input
void ASpawnCoin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Response to player input
	InputComponent->BindAction("EnterSpawn", IE_Pressed, this, &ASpawnCoin::startSpawn);
	InputComponent->BindAction("EnterSpawn", IE_Released, this, &ASpawnCoin::stopSpawn);

}

bool ASpawnCoin::SpawnActor()
{
	bool SpawnedActor = false;

	if (ActorClassToBeSpawned)
	{
		//Calculate boundary of box
		FBoxSphereBounds BoxBounds = SpawnBox->CalcBounds(GetActorTransform());

		//Compute random position within box bounds
		FVector SpawnLocation = BoxBounds.Origin;
		//origin += negative initial box extent + twice (positive and negative values of bounds) * box extents * rand value
		//SpawnLocation.X += (- BoxBounds.BoxExtent.X) + 2 * BoxBounds.BoxExtent.X * FMath::Rand();
		//SpawnLocation.Y += (- BoxBounds.BoxExtent.Y) + 2 * BoxBounds.BoxExtent.Y * FMath::Rand();
		//SpawnLocation.Z += (- BoxBounds.BoxExtent.Z) + 2 * BoxBounds.BoxExtent.Z * FMath::Rand();

		//Spawn actor at location
		SpawnedActor = GetWorld()->SpawnActor(ActorClassToBeSpawned, &SpawnLocation) != nullptr;
		
	}

	return SpawnedActor;
}

//void ASpawnCoin::EnableSpawn(bool Enable)
//{
//	ShouldSpawn = Enable;
//	if (Enable)
//	{
//		SpawnActor();
//	}
//}

void ASpawnCoin::SpawnActorSchedule()
{
	SpawnActor();
	if (ShouldSpawn)
	{
		ScheduleActorSpawn();
	}
}

void ASpawnCoin::ScheduleActorSpawn()
{
	//compute time offset to spawn
	float DeltaToNextSpawn = AvgSpawnTime + (-RandomSpawnTimeOffset + 2 * RandomSpawnTimeOffset * FMath::FRand());

	//schedule spawn
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &ASpawnCoin::SpawnActorSchedule, DeltaToNextSpawn, false);
}

void ASpawnCoin::startSpawn()
{
	bSpawn = true;
	UE_LOG(LogTemp, Warning, TEXT("Pressed"));
	SpawnActor();
}

void ASpawnCoin::stopSpawn()
{
	bSpawn = false;
}