// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_SetBoolValueInBB.generated.h"

/**
 * 
 */
UCLASS()
class PRUEBADISEMBODIED_API UBTTask_SetBoolValueInBB : public UBTTaskNode
{
	GENERATED_BODY()
	
	public:
		UBTTask_SetBoolValueInBB();

	private:
		virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	public:
		UPROPERTY(EditAnywhere)
			bool Value;
		UPROPERTY(EditAnywhere)
			FBlackboardKeySelector BlackBoardKey;
};
