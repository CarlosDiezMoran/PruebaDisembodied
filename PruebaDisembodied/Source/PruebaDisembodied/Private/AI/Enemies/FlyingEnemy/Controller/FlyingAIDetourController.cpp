// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/Enemies/FlyingEnemy/Controller/FlyingAIDetourController.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BehaviorTreeComponent.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BehaviorTree.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "AI/BBData/HidePointsContainer.h"
#include "AI/Enemies/FlyingEnemy/Character/FlyingEnemy.h"
#include "Yorick/Character/PruebaDisembodiedCharacter.h"
#include "AI/Points/HidePoint.h"

#include "DebugLibrary.h"

AFlyingAIDetourController::AFlyingAIDetourController(const FObjectInitializer& ObjectInitializer)
	: Super(/*ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent"))*/) 
{
	DISEMLOG();

	/*
	//CrowdFollowingComponent
	Pathfol = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent());

	if (Pathfol->IsValidLowLevel() && !Pathfol->IsPendingKill())
	{
		Pathfol->SetCrowdSeparationWeight(90.f, true);
		Pathfol->SetCrowdSeparation(true);
		Pathfol->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::High);
	}
	else 
	{
		DISEMLOG("Error. Pathfol is NULL.");
	}
	*/
	//BehaviorTree & Blackboard
	BBComponent = CreateDefaultSubobject<UBlackboardComponent>(FName("BBComponent"));
	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(FName("BehaviorTreeComponent"));

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BT(TEXT("BehaviorTree'/Game/AI/Enemies/FlyingEnemy/BT/BT_FlyingEnemy.BT_FlyingEnemy'"));
	if (BT.Succeeded())
	{
		UBehaviorTree* Asset = BT.Object;
		BehaviorTree = Asset;
	}

	//HidePoints
	HidePoints = NewObject<UHidePointsContainer>(UHidePointsContainer::StaticClass());
}

void AFlyingAIDetourController::BeginPlay()
{
	DISEMLOG();

	Super::BeginPlay();

	TArray<AActor*> FoundPlayers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APruebaDisembodiedCharacter::StaticClass(), FoundPlayers);
	if (FoundPlayers.Num() > 0)
	{
		BBComponent->SetValueAsObject("Yorick", Cast<APruebaDisembodiedCharacter>(FoundPlayers[0]));
	}
}

void AFlyingAIDetourController::Possess(APawn * InPawn)
{
	DISEMLOG();

	Super::Possess(InPawn);

	AFlyingEnemy* ControlledEnemy = Cast<AFlyingEnemy>(InPawn);

	//Checks
	bool bDoPosess = true;

	if (!ControlledEnemy->IsValidLowLevel() || ControlledEnemy->IsPendingKill())
	{
		DISEMLOG("Error. Pawn is NULL. ");
		bDoPosess = false;
	}

	if (bDoPosess) 
	{
		if (!BBComponent->IsValidLowLevel() || BBComponent->IsPendingKill())
		{
			DISEMLOG("Error. BBComponent is NULL in " + ControlledEnemy->GetName());
			bDoPosess = false;
		}

		if (!BehaviorTree->IsValidLowLevel() || BehaviorTree->IsPendingKill())
		{
			DISEMLOG("Error. BehaviorTree is NULL in " + ControlledEnemy->GetName());
			bDoPosess = false;
		}

		if (!HidePoints->IsValidLowLevel() || HidePoints->IsPendingKill())
		{
			DISEMLOG("Error. HidePoints are NULL in " + ControlledEnemy->GetName());
			bDoPosess = false;
		}

		if (bDoPosess) 
		{
			//Initialize the Blackboard 
			bool bBBRes = BBComponent->InitializeBlackboard(*BehaviorTree->BlackboardAsset);

			if (bBBRes)
			{
				//Get HidePoints
				TArray<AActor*> FoundActors;
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), AHidePoint::StaticClass(), FoundActors);
				for (AActor* Actor : FoundActors)
				{
					AHidePoint* HidePoint = Cast<AHidePoint>(Actor);

					if (ControlledEnemy->HidePointsID == HidePoint->Id) 
					{
						HidePoints->HidePoints.AddUnique(HidePoint);
					}
				}

				//Check HidePoints
				if (HidePoints->HidePoints.Num() > 0) 
				{
					// Deafult Values

					// Store HidePoints in BB
					BBComponent->SetValueAsObject("HidePoints", HidePoints);

					//Check Yorick
					if (!ControlledEnemy->YorickCharacter->IsValidLowLevel() || ControlledEnemy->YorickCharacter->IsPendingKill()) 
					{
						TArray<AActor*> FoundPlayers;
						UGameplayStatics::GetAllActorsOfClass(GetWorld(), APruebaDisembodiedCharacter::StaticClass(), FoundPlayers);
						if (FoundPlayers.Num() > 0)
						{
							ControlledEnemy->YorickCharacter = Cast<APruebaDisembodiedCharacter>(FoundPlayers[0]);
							if (!ControlledEnemy->YorickCharacter->IsValidLowLevel() || ControlledEnemy->YorickCharacter->IsPendingKill())
							{
								DISEMLOG("Error. YorickCharacter is NULL.");
								bDoPosess = false;
							}
						}
					}
						
					//Store Yorick in BB
					BBComponent->SetValueAsObject("Yorick", ControlledEnemy->YorickCharacter);

					//Store HidePointsToGoBeforeNextAttack in BB
					if (bDoPosess) 
					{
						BBComponent->SetValueAsInt("HidePointsToGoBeforeNextAttack", ControlledEnemy->HidePointsToGoBeforeNextAttack);
					}
					
					//Store HidePointsToGoBeforeNextAttack in BB
					BBComponent->SetValueAsBool("IsPursuingYorick", true);		
				}
				else 
				{
					DISEMLOG("Error. HidePoints is empty in " + ControlledEnemy->GetName());
					bDoPosess = false;
				}
			}
			else 
			{
				DISEMLOG("Error. BBComponent couldn't be initialized in " + ControlledEnemy->GetName());
				bDoPosess = false;
			}
		}
		else 
		{
			DISEMLOG("Error. Possess couldn't be done in " + ControlledEnemy->GetName());
		}
	}
	else 
	{
		DISEMLOG("Error. Possess couldn't be done");
	}




	// Run Behavior tree
	if (bDoPosess)
	{
		BehaviorTreeComp->StartTree(*BehaviorTree);
	}
}
