// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EventsManager.generated.h"

UCLASS(Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent), Category = "Events Manager")
class PRUEBADISEMBODIED_API UEventsManager : public UObject
{
	GENERATED_BODY()
	
	public:
		UEventsManager();
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
			bool bIsDebugActive;
};
