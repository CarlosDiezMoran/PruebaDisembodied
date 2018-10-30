// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "YorickController.generated.h"

class APruebaDisembodiedCharacter;
class UEventsManager;

UENUM(BlueprintType)
enum class EYorickState : uint8 {				
	DISABLED,				
	STANDARD,				
};


UCLASS()
class PRUEBADISEMBODIED_API AYorickController : public APlayerController
{
	GENERATED_BODY()
	
	public:

		AYorickController();
		virtual void BeginPlayingState() override;
		virtual void Tick(float DeltaSeconds) override;

		UFUNCTION(BlueprintCallable)
			void SetState(EYorickState State);

		UFUNCTION(BlueprintCallable, BlueprintPure)
			EYorickState GetCurrentState();

		//********************** Movement ***************************//

		UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BindingFunction")
			void MoveForward(float Value);
		virtual void MoveForward_Implementation(float Value);

		UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BindingFunction")
			void MoveRight(float Value);
		virtual void MoveRight_Implementation(float Value);

		//*********************************************************//

		//********************** Camera ***************************//

		//Turn (RAxis-X)

		UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BindingFunction")
			void TurnAtRate(float Value);
		virtual void TurnAtRate_Implementation(float Value);

		UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BindingFunction")
			void Turn(float Value);
		virtual void Turn_Implementation(float Value);

		//LookUp (RAxis-Y)

		UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BindingFunction")
			void LookUp(float Value);
		virtual void LookUp_Implementation(float Value);
		UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BindingFunction")
			void LookUpAtRate(float Value);
		virtual void LookUpAtRate_Implementation(float Value);

		//*********************************************************//

		//********************** Pickups ***************************//

		UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BindingFunction")
			void LeftHand();
		virtual void LeftHand_Implementation();
		UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BindingFunction")
			void RightHand();
		virtual void RightHand_Implementation();

		UFUNCTION(BlueprintCallable, Category = "ObjectDetection")
			void AddDetectedObject(APickup* DetectedObject);
		UFUNCTION(BlueprintCallable, Category = "ObjectDetection")
			void RemoveDetectedObject(APickup* DetectedObject);

		//**********************************************************//

	private:

		UFUNCTION()
			void SetDisabledState();

		UFUNCTION()
			void SetStandardState();

	public:

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
			APruebaDisembodiedCharacter* YorickCharacter;

	private:

		EYorickState CurrentState;
		UEventsManager* EventsManager;

	
};
