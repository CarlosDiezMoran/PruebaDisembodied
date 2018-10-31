// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "HidePoint.generated.h"

class UTextRenderComponent;

UCLASS()
class PRUEBADISEMBODIED_API AHidePoint : public ATargetPoint
{
	GENERATED_BODY()
	
	public:
		AHidePoint();
		virtual void OnConstruction(const FTransform& Transform) override;

	public:
		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HidePoint")
			UTextRenderComponent *TextRender;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HidePoint")
			int32 Id;
};
