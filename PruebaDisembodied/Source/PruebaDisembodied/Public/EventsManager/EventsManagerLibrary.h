// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EventsManager.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "EventsManagerLibrary.generated.h"

UCLASS()
class PRUEBADISEMBODIED_API UEventsManagerLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	public:
		UEventsManagerLibrary();
		UFUNCTION(BlueprintPure, Category = "Events Manager")
			static UEventsManager* GetEventsManager();
};
