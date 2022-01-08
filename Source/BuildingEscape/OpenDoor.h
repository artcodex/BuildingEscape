// Copyright Avi Brenner.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:
	float targetYaw = 0.f;
	float initialYaw = 0.0f;

	UPROPERTY(EditAnywhere)
		float openYaw = 90.f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* pressurePlate;

	UPROPERTY(EditAnywhere)
	AActor* PlayerActor;

	UPROPERTY(EditAnywhere)
	float openSpeed = 2.f;

	UPROPERTY(EditAnywhere)
	float closeSpeed = 2.f;

	float currentSpeed = openSpeed;
private: 
	void HandleOpenClose();
	void SwingDoor(float DeltaTime);
};
