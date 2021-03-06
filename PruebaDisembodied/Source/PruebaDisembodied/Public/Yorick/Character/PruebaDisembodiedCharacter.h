// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/Damageable.h"
#include "PruebaDisembodiedCharacter.generated.h"

class APickup;
class UEquipmentComponent;
class AYorickFlyingPoint;

UCLASS(config=Game)
class APruebaDisembodiedCharacter : public ACharacter, public IDamageable
{
	GENERATED_BODY()

	public:
		APruebaDisembodiedCharacter();
		virtual void BeginPlay() override;

		/** Returns CameraBoom subobject **/
		FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
		/** Returns FollowCamera subobject **/
		FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

		//********************** Pickups ***************************//

		UFUNCTION(BlueprintCallable, Category = "ObjectDetection")
			void AddDetectedObject(APickup* DetectedObject);
		UFUNCTION(BlueprintCallable, Category = "ObjectDetection")
			void RemoveDetectedObject(APickup* DetectedObject);
		UFUNCTION(BlueprintCallable, Category = "ObjectDetection")
			void FindClosestObject();

		//**********************************************************//

		//********************** Equipment ***************************//

		UFUNCTION(BlueprintCallable, Category = "Equipment")
			void LeftHand();
		UFUNCTION(BlueprintCallable, Category = "Equipment")
			void RightHand();

		//**********************************************************//

		//********************** IDamageable ***********************//

		UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "IDamageable")
			void OnDamage(float Damage, AActor* ActorInstigator);
		virtual void OnDamage_Implementation(float Damage, AActor* ActorInstigator);

		//**********************************************************//
		
	public:
		
		/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
			float BaseTurnRate;

		/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
			float BaseLookUpRate;

		/** Camera boom positioning the camera behind the character */
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
			class USpringArmComponent* CameraBoom;

		/** Follow camera */
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
			class UCameraComponent* FollowCamera;

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
			float DetectionAngle = 90.f;

		//********************** Equipment ***************************//

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
			UEquipmentComponent* RightHandComponent;
		UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
			UEquipmentComponent* LeftHandComponent;

		//************************************************************//

		//********************** AI Points ***************************//

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
			AYorickFlyingPoint* YorickFlyinghPoint;
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
			USceneComponent* YorickFlyinghPointLocation;

		//************************************************************//

	private:

		UPROPERTY()
			TArray<APickup*> InteractiveObjects;
		UPROPERTY()
			APickup* ClosestInteractiveObject;
};

