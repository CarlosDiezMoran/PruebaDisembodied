// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/Points/YorickFlyingPoint.h"
#include "Runtime/Engine/Classes/Components/BillboardComponent.h"
#include "Runtime/Engine/Classes/Engine/Texture2D.h"
#include "DebugLibrary.h"

AYorickFlyingPoint::AYorickFlyingPoint() : Super() 
{
	DISEMLOG();

	UBillboardComponent* Sprite = GetSpriteComponent();
	FString ImagePath = "Texture2D'/Game/Art/Textures/T_PaperPlane.T_PaperPlane'";
	Sprite->SetSprite(Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *(ImagePath))));
}

