// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DebugLibrary.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogDisembodied, All, All);

UENUM(BlueprintType)
enum class ELog : uint8 {
	PRINT_ONLY,
	LOG_ONLY,
	PRINT_AND_LOG
};

#define DISEMREPLACE	FString((__FILE__)).Append("(").Append(FString::FromInt((__LINE__))).Append(")")

#define DISEMREPLACELONG(OriginalString)	(DISEMREPLACE).Append(": ").Append(OriginalString)

#define DISEMLOG_0_ARGS()	UDebugLibrary::Log((DISEMREPLACE), ELog::LOG_ONLY)

#define DISEMLOG_1_ARG(OriginalString)	UDebugLibrary::Log((DISEMREPLACELONG(OriginalString)))

#define DISEMLOG_2_ARGS(OriginalString, Target)	UDebugLibrary::Log((DISEMREPLACELONG(OriginalString)), Target)

#define DISEMLOG_3_ARGS(OriginalString, Target, TimeToPrint)	UDebugLibrary::Log((DISEMREPLACELONG(OriginalString)), Target, TimeToPrint)

#define DISEMLOG_4_ARGS(OriginalString, Target, TimeToPrint, Color)	UDebugLibrary::Log((DISEMREPLACELONG(OriginalString)), Target, TimeToPrint, Color)

#define DISEMCOUNT_N(_0, _1, _2, _3, _4, N, ...) N

#define DISEMCOUNT_M(...) DISEMEXPAND(DISEMCOUNT_N( __VA_ARGS__, DISEMLOG_4_ARGS, DISEMLOG_3_ARGS, DISEMLOG_2_ARGS, DISEMLOG_1_ARG, DISEMLOG_0_ARGS))

#define DISEMLOG(...) DISEMCALL(DISEMCOUNT_M,(, __VA_ARGS__))(__VA_ARGS__);

#define DISEMCALL(X,Y) X Y

#define DISEMEXPAND(...) __VA_ARGS__

UCLASS()
class PRUEBADISEMBODIED_API UDebugLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	public:
		UDebugLibrary();
		UFUNCTION(BlueprintCallable, Category = "Debug")
			static void Log(FString StringToPrint = "", ELog Target = ELog::PRINT_AND_LOG, float TimeToPrint = 3.f, FLinearColor Color = FLinearColor::White);
		UFUNCTION(BlueprintCallable, Category = "Debug")
			static void ActivateLog();
		UFUNCTION(BlueprintCallable, Category = "Debug")
			static void DeactivateLog();
		UFUNCTION(BlueprintCallable, Category = "Debug")
			static bool IsLogActive();
};
