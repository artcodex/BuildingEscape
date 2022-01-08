// Copyright Avi Brenner.


#include "OpenDoor.h"
#include "GameFramework\Actor.h"
#include "GameFramework\PlayerController.h"
#include "Engine\World.h"

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
	initialYaw = GetOwner()->GetActorRotation().Yaw;
	targetYaw = initialYaw;
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	//float rotation = 90.f;
	//FRotator rotator = GetOwner()->GetActorRotation();
	//FRotator newRotator = FRotator(rotator.Pitch, rotation, rotator.Yaw);

	//GetOwner()->SetActorRotation(newRotator);
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *GetOwner()->GetActorRotation().ToString());
	//UE_LOG(LogTemp, Warning, TEXT("%f"), GetOwner()->GetActorRotation().Yaw);
	//UE_LOG(LogTemp, Warning, TEXT("%f"), GetOwner()->GetActorRotation().Roll);

	AActor* testActor = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (pressurePlate != nullptr &&
		testActor != nullptr) {
		if (pressurePlate->IsOverlappingActor(testActor)) {
			//UE_LOG(LogTemp, Warning, TEXT("overlapping"));
			targetYaw = initialYaw + openYaw;
			currentSpeed = openSpeed;
		}
		else {
			//UE_LOG(LogTemp, Warning, TEXT("not overlapping"));
			targetYaw = initialYaw;
			currentSpeed = closeSpeed;
		}

		SwingDoor(DeltaTime);
	}

	HandleOpenClose();
}

void UOpenDoor::SwingDoor(float DeltaTime) {
	float currentYaw = GetOwner()->GetActorRotation().Yaw;

	if (FMath::Abs(currentYaw - targetYaw) > 0.001f) {
		float nextYaw = FMath::FInterpTo(currentYaw, targetYaw, DeltaTime, currentSpeed);

		FRotator newRotator = FRotator(0.f, nextYaw, 0.f);
		GetOwner()->SetActorRotation(newRotator);
	}
}
 
void UOpenDoor::HandleOpenClose() {
	UWorld* world = GetWorld();
	APlayerController* playerController = NULL;
	for (FConstPlayerControllerIterator Iterator = world->GetPlayerControllerIterator(); Iterator; ++Iterator) {
		playerController = Iterator->Get();
		break;
	}

	if (playerController->WasInputKeyJustPressed(EKeys::C)) {
		targetYaw -= openYaw;
	}
	else if (playerController->WasInputKeyJustPressed(EKeys::O)) {
		targetYaw += openYaw;
	}
}

