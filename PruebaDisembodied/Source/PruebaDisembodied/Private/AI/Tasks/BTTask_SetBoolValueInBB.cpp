// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/Tasks/BTTask_SetBoolValueInBB.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "DebugLibrary.h"

UBTTask_SetBoolValueInBB::UBTTask_SetBoolValueInBB()
{
	DISEMLOG();
	NodeName = "SetBoolValueInBB";
}

EBTNodeResult::Type UBTTask_SetBoolValueInBB::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	DISEMLOG();

	Super::ExecuteTask(OwnerComp, NodeMemory);

	OwnerComp.GetBlackboardComponent()->SetValueAsBool(BlackBoardKey.SelectedKeyName, Value);
	return EBTNodeResult::Succeeded;
}