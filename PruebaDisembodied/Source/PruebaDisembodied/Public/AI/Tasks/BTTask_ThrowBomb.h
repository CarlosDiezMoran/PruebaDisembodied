// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_ThrowBomb.generated.h"

class APickup;

UCLASS()
class PRUEBADISEMBODIED_API UBTTask_ThrowBomb : public UBTTaskNode
{
	GENERATED_BODY()
	
	public:
		UBTTask_ThrowBomb();

	private:
		virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	public:
		UPROPERTY(EditAnywhere)
			TSubclassOf<APickup> BombToSpawn;
};
