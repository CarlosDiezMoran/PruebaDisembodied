// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "FlyingAIDetourController.generated.h"

class UBlackboardComponent;
class UBehaviorTreeComponent;
class UCrowdFollowingComponent;
class UHidePointsContainer;

UCLASS()
class PRUEBADISEMBODIED_API AFlyingAIDetourController : public AAIController
{
	GENERATED_BODY()
	
	public:

		AFlyingAIDetourController(const FObjectInitializer& ObjectInitializer);
		virtual void BeginPlay() override;
		virtual void Possess(APawn* InPawn) override;

	public:
		UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
			UBlackboardComponent* BBComponent;
		UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
			UBehaviorTreeComponent *BehaviorTreeComp;
		UPROPERTY(VisibleAnywhere)
			UBehaviorTree* BehaviorTree;
		UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
			UCrowdFollowingComponent* Pathfol;

	private:
		UPROPERTY()
			UHidePointsContainer* HidePoints;
	
};
