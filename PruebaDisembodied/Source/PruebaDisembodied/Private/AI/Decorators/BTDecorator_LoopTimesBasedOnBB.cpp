// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/Decorators/BTDecorator_LoopTimesBasedOnBB.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BehaviorTreeComponent.h"
#include "Runtime/AIModule/Classes/Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BehaviorTree.h"
#include "DebugLibrary.h"


UBTDecorator_LoopTimesBasedOnBB::UBTDecorator_LoopTimesBasedOnBB() : Super()
{
	DISEMLOG();
	NodeName = "LoopTimesBasedOnBB";
}

void UBTDecorator_LoopTimesBasedOnBB::DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const
{
	DISEMLOG();
	Super::DescribeRuntimeValues(OwnerComp, NodeMemory, Verbosity, Values);
}

void UBTDecorator_LoopTimesBasedOnBB::OnNodeActivation(FBehaviorTreeSearchData & SearchData)
{
	UBlackboardComponent* BBComponent = SearchData.OwnerComp.GetBlackboardComponent();
	NumLoops = BBComponent->GetValueAsInt(BBKeyNumOfLoops.SelectedKeyName);

	Super::OnNodeActivation(SearchData);
}
