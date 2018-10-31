// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HidePointsContainer.generated.h"

class AHidePoint;

UCLASS()
class PRUEBADISEMBODIED_API UHidePointsContainer : public UObject
{
	GENERATED_BODY()

	public:
		UHidePointsContainer();
	
	public:
		UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
			TArray<AHidePoint*> HidePoints;
};
