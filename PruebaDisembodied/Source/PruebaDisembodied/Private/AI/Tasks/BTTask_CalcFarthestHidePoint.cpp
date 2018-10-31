// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_CalcFarthestHidePoint.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "AI/BBData/HidePointsContainer.h"
#include "AI/Points/HidePoint.h"
#include "DebugLibrary.h"

UBTTask_CalcFarthestHidePoint::UBTTask_CalcFarthestHidePoint()
{
	DISEMLOG();
	NodeName = "CalculateFarthestHidePoint";
}

EBTNodeResult::Type UBTTask_CalcFarthestHidePoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	DISEMLOG();

	Super::ExecuteTask(OwnerComp, NodeMemory);

	bool bOK = true;

	UBlackboardComponent* BBComponent = OwnerComp.GetBlackboardComponent();
	AController* Controller = Cast<AController>(OwnerComp.GetOwner());

	if (Controller->IsValidLowLevel() && !Controller->IsPendingKill()) 
	{
		APawn* Pawn = Controller->GetPawn();

		if (Pawn->IsValidLowLevel() && !Pawn->IsPendingKill()) 
		{
			AHidePoint* FarthestHidePoint = nullptr;
			FVector PawnLocation = Pawn->GetActorLocation();
			float FarthestDistance = 0.0f;

			UObject* BBBObject = BBComponent->GetValueAsObject(BBKeyHidePoints.SelectedKeyName);

			if (BBBObject->IsValidLowLevel() && !BBBObject->IsPendingKill())
			{
				UHidePointsContainer* HidePointsCont = Cast<UHidePointsContainer>(BBBObject);

				//Find farthest HidePoint
				for (AHidePoint* HidePoint : HidePointsCont->HidePoints)
				{
					float Distance = FVector::Dist(PawnLocation, HidePoint->GetActorLocation());

					if (Distance > FarthestDistance) 
					{
						FarthestDistance = Distance;
						FarthestHidePoint = HidePoint;
					}
				}

				BBComponent->SetValueAsObject(BBKeyFarthestHidePoint.SelectedKeyName, FarthestHidePoint);
			}
			else 
			{
				DISEMLOG("Error. HidePointsContainer is NULL");
				bOK = false;
			}
		}
		else
		{
			DISEMLOG("Error. Pawn is NULL");
			bOK = false;
		}
	}
	else 
	{
		DISEMLOG("Error. Controller is NULL");
		bOK = false;
	}

	return (bOK) ? EBTNodeResult::Succeeded : EBTNodeResult::InProgress;
}
