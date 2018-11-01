// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "FlyingAIControllerV2.generated.h"

class UBlackboardComponent;
class UBehaviorTreeComponent;
class UHidePointsContainer;

UCLASS()
class PRUEBADISEMBODIED_API AFlyingAIControllerV2 : public AAIController
{
	GENERATED_BODY()
	
	public:

		AFlyingAIControllerV2();
		virtual void BeginPlay() override;
		virtual void Possess(APawn* InPawn) override;

	public:
		UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
			UBlackboardComponent* BBComponent;
		UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
			UBehaviorTreeComponent *BehaviorTreeComp;
		UPROPERTY(VisibleAnywhere)
			UBehaviorTree* BehaviorTree;

	private:
		UPROPERTY()
			UHidePointsContainer* HidePoints;
	
	
};
