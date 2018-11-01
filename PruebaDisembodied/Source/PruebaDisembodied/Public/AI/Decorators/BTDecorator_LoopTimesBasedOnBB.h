// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_Loop.h"
#include "BTDecorator_LoopTimesBasedOnBB.generated.h"


UCLASS()
class PRUEBADISEMBODIED_API UBTDecorator_LoopTimesBasedOnBB : public UBTDecorator_Loop
{
	GENERATED_BODY()

	public:
		UBTDecorator_LoopTimesBasedOnBB();
		virtual void DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const override;
		virtual void OnNodeActivation(FBehaviorTreeSearchData& SearchData) override;
	
	public:

		UPROPERTY(EditAnywhere)
			FBlackboardKeySelector BBKeyNumOfLoops;
};
