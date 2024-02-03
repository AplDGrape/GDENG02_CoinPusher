// Fill out your copyright notice in the Description page of Project Settings.


#include "THEMovingObj.h"

#include "Components/BoxComponent.h"
#include "Components/InterpToMovementComponent.h"

// Sets default values
ATHEMovingObj::ATHEMovingObj()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	RootComponent = BoxCollider;

	//Create static mesh
	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMesh"));
	MyMesh->SetupAttachment(RootComponent);

	MovementComponent = CreateDefaultSubobject<UInterpToMovementComponent>(TEXT("MovementComponent"));

	//Setting up default parameters
	MovementComponent->Duration = 5.0f;
	//Seep for blocking collision during movement
	MovementComponent->bSweep = true;
	//Movement Back and forth
	MovementComponent->BehaviourType = EInterpToBehaviourType::PingPong;
}

// Called when the game starts or when spawned
void ATHEMovingObj::BeginPlay()
{
	Super::BeginPlay();
	
	//Setting up control points for movement
	MovementComponent->ControlPoints.Add(FInterpControlPoint(FVector(0.f, 0.f, 0.f), true));
	//Go through path one at a time until nowhere to go to
	for (int i = 0; i < ThePath.Num(); i++)
	{
		MovementComponent->ControlPoints.Add(FInterpControlPoint(ThePath[i], true));
	}
	//Run the path
	MovementComponent->FinaliseControlPoints();
}

// Called every frame
void ATHEMovingObj::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//FVector Location = GetActorLocation();
	//Location += GetActorForwardVector() * Speed * DeltaTime;
	//SetActorLocation(Location);
}

