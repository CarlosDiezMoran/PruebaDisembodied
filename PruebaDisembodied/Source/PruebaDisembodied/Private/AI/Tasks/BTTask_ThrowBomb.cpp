// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_ThrowBomb.h"
#include "Pickup.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/GameFramework/Character.h"
#include "Runtime/Engine/Classes/Components/CapsuleComponent.h"
#include "DebugLibrary.h"

UBTTask_ThrowBomb::UBTTask_ThrowBomb() 
{
	DISEMLOG();

	NodeName = "ThrowBomb";
}

EBTNodeResult::Type UBTTask_ThrowBomb::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	DISEMLOG();

	Super::ExecuteTask(OwnerComp, NodeMemory);

	AController* Controller = Cast<AController>(OwnerComp.GetOwner());

	if (Controller->IsValidLowLevel() && !Controller->IsPendingKill()) 
	{
		APawn* Pawn = Controller->GetPawn();

		if (Pawn->IsValidLowLevel() && !Pawn->IsPendingKill())
		{

			ACharacter* ControlledCharacter = Cast<ACharacter>(Pawn);
			
			float Offset = ControlledCharacter->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();

			FActorSpawnParameters SpawnInfo;
			FVector Location = ControlledCharacter->GetActorLocation();
			Location.Z = Location.Z - Offset;
			FRotator Rotation(0.0f, 0.0f, 0.0f);
			GetWorld()->SpawnActor<APickup>(BombToSpawn, Location, Rotation, SpawnInfo);
		
		}
		else 
		{
			DISEMLOG("Error. Controller is NULL");
		}
	}
	else 
	{
		DISEMLOG("Error. Controller is NULL");
	}

	return EBTNodeResult::Succeeded;
}
