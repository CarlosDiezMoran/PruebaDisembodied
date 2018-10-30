// Fill out your copyright notice in the Description page of Project Settings.

#include "EquipmentComponent.h"
#include "EquippedObject/EquippedObject.h"
#include "Pickup/Pickup.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/GameFramework/Character.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Components/SceneComponent.h"
#include "Debug/DebugLibrary.h"


// Sets default values for this component's properties
UEquipmentComponent::UEquipmentComponent()
{
	DISEMLOG();

	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	EquippedObject = nullptr;
}

// Called when the game starts
void UEquipmentComponent::BeginPlay()
{
	DISEMLOG();

	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UEquipmentComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UEquipmentComponent::AddEquippedObject(TSubclassOf<AEquippedObject> ObjectClass)
{
	DISEMLOG();

	ACharacter* Yorick = Cast<ACharacter>(GetOwner());

	if (Yorick->IsValidLowLevel() && !Yorick->IsPendingKill()) 
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.Owner = Yorick;
		FVector Location(0.0f, 0.0f, 0.0f);
		FRotator Rotation(0.0f, 0.0f, 0.0f);
		EquippedObject = GetWorld()->SpawnActor<AEquippedObject>(ObjectClass, Location, Rotation, SpawnInfo);

		if (EquippedObject->IsValidLowLevel() && !EquippedObject->IsPendingKill()) 
		{
			EquippedObject->AttachToComponent(Yorick->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, SocketOwner);
		}
		else 
		{
			DISEMLOG("Error. EquippedObject is NULL");
		}
		
	}
	else 
	{
		DISEMLOG("Error. Yorick is NULL");
	}
}

void UEquipmentComponent::RemoveEquippedObject()
{
	DISEMLOG();

	if (EquippedObject->IsValidLowLevel() && !EquippedObject->IsPendingKill())
	{
		FActorSpawnParameters SpawnInfo;
		FVector Location = EquippedObject->GetActorLocation();
		FRotator Rotation = EquippedObject->GetActorRotation();
		APickup* Pickup = GetWorld()->SpawnActor<APickup>(EquippedObject->PickupObjectToSpawn, Location, Rotation, SpawnInfo);

		if (Pickup->IsValidLowLevel() && !Pickup->IsPendingKill())
		{
			Pickup->PickupMesh->SetSimulatePhysics(true);
		}
		else 
		{
			DISEMLOG("Error. Pickup is NULL");
		}
			
		EquippedObject->Destroy();
	
	}
	else 
	{
		DISEMLOG("Error. EquippedObject is NULL");
	}
}

void UEquipmentComponent::Interact(APickup* Pickup)
{
	DISEMLOG();

	if (EquippedObject->IsValidLowLevel() && !EquippedObject->IsPendingKill()) 
	{
		RemoveEquippedObject();
	}
	else 
	{
		if (Pickup->IsValidLowLevel() && !Pickup->IsPendingKill()) 
		{
			AddEquippedObject(Pickup->EquippedObjectToSpawn);
			Pickup->Destroy();
		}
	}
}

