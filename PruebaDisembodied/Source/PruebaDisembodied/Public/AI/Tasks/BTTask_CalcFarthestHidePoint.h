// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_CalcFarthestHidePoint.generated.h"

UCLASS()
class PRUEBADISEMBODIED_API UBTTask_CalcFarthestHidePoint : public UBTTaskNode
{
	GENERATED_BODY()
	
	public:
		UBTTask_CalcFarthestHidePoint();

	private:
		virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	public:
	
		UPROPERTY(EditAnywhere)
			FBlackboardKeySelector BBKeyHidePoints;
		UPROPERTY(EditAnywhere)
			FBlackboardKeySelector BBKeyFarthestHidePoint;
};
