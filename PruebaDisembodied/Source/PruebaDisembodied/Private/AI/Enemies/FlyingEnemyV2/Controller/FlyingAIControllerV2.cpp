// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/Enemies/FlyingEnemyV2/Controller/FlyingAIControllerV2.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BehaviorTreeComponent.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BehaviorTree.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Yorick/Character/PruebaDisembodiedCharacter.h"
#include "AI/BBData/HidePointsContainer.h"
#include "AI/Points/HidePoint.h"
#include "AI/Enemies/FlyingEnemy/Character/FlyingEnemy.h"
#include "AI/Points/YorickFlyingPoint.h"
#include "DebugLibrary.h"

AFlyingAIControllerV2::AFlyingAIControllerV2() : Super() 
{
	DISEMLOG();

	//BehaviorTree & Blackboard
	BBComponent = CreateDefaultSubobject<UBlackboardComponent>(FName("BBComponent"));
	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(FName("BehaviorTreeComponent"));

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BT(TEXT("BehaviorTree'/Game/AI/Enemies/FlyingEnemyV2/BT/BT_FliyingEnemyV2.BT_FliyingEnemyV2'"));
	if (BT.Succeeded())
	{
		UBehaviorTree* Asset = BT.Object;
		BehaviorTree = Asset;
	}

	//HidePoints
	HidePoints = NewObject<UHidePointsContainer>(UHidePointsContainer::StaticClass());
}


void AFlyingAIControllerV2::BeginPlay()
{
	DISEMLOG();

	Super::BeginPlay();

	/*
		Setting Yorick's ref in BeginPlay function cause Possess is executed before BeginPlay
	*/

	//Check Yorick
	TArray<AActor*> FoundPlayers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APruebaDisembodiedCharacter::StaticClass(), FoundPlayers);
	if (FoundPlayers.Num() > 0)
	{
		APruebaDisembodiedCharacter* Yorick = Cast<APruebaDisembodiedCharacter>(FoundPlayers[0]);
		if (Yorick->IsValidLowLevel() && !Yorick->IsPendingKill())
		{
			//Spawn FlyingPoint in case is not already spawned
			if (!Yorick->YorickFlyinghPoint->IsValidLowLevel() || Yorick->YorickFlyinghPoint->IsPendingKill())
			{
				FActorSpawnParameters SpawnInfo;
				SpawnInfo.Owner = this;
				FVector Location = Yorick->YorickFlyinghPointLocation->GetComponentLocation();
				FRotator Rotation = Yorick->YorickFlyinghPointLocation->GetComponentRotation();
				Yorick->YorickFlyinghPoint = GetWorld()->SpawnActor<AYorickFlyingPoint>(Location, Rotation, SpawnInfo);

				if (Yorick->YorickFlyinghPoint->IsValidLowLevel() && !Yorick->YorickFlyinghPoint->IsPendingKill())
				{
					Yorick->YorickFlyinghPoint->AttachToComponent(Yorick->YorickFlyinghPointLocation, FAttachmentTransformRules::SnapToTargetIncludingScale);

					//Store Yorick in BB
					BBComponent->SetValueAsObject("YoricksFlyingPoint", Cast<APruebaDisembodiedCharacter>(FoundPlayers[0])->YorickFlyinghPoint);
				}
			}
			else
			{
				//Store Yorick in BB
				BBComponent->SetValueAsObject("YoricksFlyingPoint", Cast<APruebaDisembodiedCharacter>(FoundPlayers[0])->YorickFlyinghPoint);
			}
		}
		else
		{
			DISEMLOG("Error. Yorick is NULL");
		}
	}
	
}

void AFlyingAIControllerV2::Possess(APawn * InPawn)
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
