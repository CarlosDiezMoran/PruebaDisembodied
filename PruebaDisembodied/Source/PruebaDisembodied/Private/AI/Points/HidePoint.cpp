// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/Points/HidePoint.h"
#include "Runtime/Engine/Classes/Components/TextRenderComponent.h"
#include "Runtime/Engine/Classes/Components/BillboardComponent.h"
#include "DebugLibrary.h"

AHidePoint::AHidePoint() : Super() 
{
	DISEMLOG();

	Id = -1;

	TextRender = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRender"));
	TextRender->SetupAttachment(RootComponent);
	TextRender->SetRelativeLocation(FVector(0.f, 0.f, 33.f));
	TextRender->SetTextRenderColor(FColor(255, 0, 69, 255));
	TextRender->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	TextRender->bHiddenInGame = true;
	SetActorHiddenInGame(true);
}

void AHidePoint::OnConstruction(const FTransform & Transform)
{
	DISEMLOG();

	TextRender->SetText(FText::FromString(FString("HidePoint - ID: ") + FString::FromInt(Id)));
}


