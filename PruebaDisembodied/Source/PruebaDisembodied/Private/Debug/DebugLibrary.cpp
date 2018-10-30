// Fill out your copyright notice in the Description page of Project Settings.

#include "DebugLibrary.h"
#include "Engine.h"
#include "EventsManager/EventsManager.h"

DEFINE_LOG_CATEGORY(LogDisembodied);

UDebugLibrary::UDebugLibrary() : Super()
{

}

void UDebugLibrary::Log(FString StringToPrint, ELog Target, float TimeToPrint, FLinearColor Color)
{
	FString RealStringToPrint;
	FString StringToDiscard;

	if (StringToPrint.Split("\\", &StringToDiscard, &RealStringToPrint, ESearchCase::IgnoreCase, ESearchDir::FromEnd))
	{
		StringToPrint = RealStringToPrint;
	}

	RealStringToPrint = FFrame::GetScriptCallstack();

	if (!RealStringToPrint.Contains("[Empty]"))
	{
		RealStringToPrint.RemoveFromEnd("\n");
		StringToPrint.Append(" -");
		StringToPrint.Append(RealStringToPrint);
	}

#if !UE_BUILD_SHIPPING

	if (Target != ELog::LOG_ONLY)
	{
		if (GEngine)
		{
			UEventsManager* DataInstance = Cast<UEventsManager>(GEngine->GameSingleton);
			if (DataInstance)
			{
				if (DataInstance->bIsDebugActive)
				{
					GEngine->AddOnScreenDebugMessage(-1, TimeToPrint, Color.ToFColor(false), TEXT("" + StringToPrint));
				}
			}
		}
	}

#endif

	if (Target != ELog::PRINT_ONLY)
	{
		if (TimeToPrint > 1.f)
		{
			UE_LOG(LogDisembodied, Display, TEXT("%s"), *StringToPrint);
		}
	}
}

void UDebugLibrary::ActivateLog()
{
#if !UE_BUILD_SHIPPING

	UEventsManager* DataInstance = Cast<UEventsManager>(GEngine->GameSingleton);

	if (DataInstance)
	{
		DataInstance->bIsDebugActive = true;
	}

#endif
}

void UDebugLibrary::DeactivateLog()
{
#if !UE_BUILD_SHIPPING

	UEventsManager* DataInstance = Cast<UEventsManager>(GEngine->GameSingleton);
	if (DataInstance)
	{
		DataInstance->bIsDebugActive = false;
	}

#endif
}

bool UDebugLibrary::IsLogActive()
{
	bool bIsLogActive = false;

#if !UE_BUILD_SHIPPING

	UEventsManager* DataInstance = Cast<UEventsManager>(GEngine->GameSingleton);

	if (DataInstance)
	{
		bIsLogActive = DataInstance->bIsDebugActive;
	}

#endif

	return bIsLogActive;
}
