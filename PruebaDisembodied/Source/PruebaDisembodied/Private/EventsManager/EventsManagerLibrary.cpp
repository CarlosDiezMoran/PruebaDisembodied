// Fill out your copyright notice in the Description page of Project Settings.

#include "EventsManagerLibrary.h"
#include "Debug/DebugLibrary.h"
#include "Engine.h"


UEventsManagerLibrary::UEventsManagerLibrary() : Super() 
{
	DISEMLOG();
}

UEventsManager * UEventsManagerLibrary::GetEventsManager()
{
	DISEMLOG();

	UEventsManager* DataInstance = nullptr;
	if (GEngine)
	{
		DataInstance = Cast<UEventsManager>(GEngine->GameSingleton);
		if (!DataInstance)
		{
			DataInstance = nullptr;
		}
		else if (!DataInstance->IsValidLowLevel())
		{
			DataInstance = nullptr;
		}
	}

	return DataInstance;
}
