// Copyright Avi Brenner.


#include "OpenDoor.h"
#include "GameFramework\Actor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	// ...
	float rotation = 90.f;
	FRotator rotator = GetOwner()->GetActorRotation();
	FRotator newRotator = FRotator(rotator.Pitch, rotation, rotator.Yaw);

	GetOwner()->SetActorRotation(newRotator);
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

