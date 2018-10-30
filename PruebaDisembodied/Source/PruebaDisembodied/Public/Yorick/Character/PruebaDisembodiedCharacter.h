// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PruebaDisembodiedCharacter.generated.h"

UCLASS(config=Game)
class APruebaDisembodiedCharacter : public ACharacter
{
	GENERATED_BODY()

	public:
		APruebaDisembodiedCharacter();

		/** Returns CameraBoom subobject **/
		FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
		/** Returns FollowCamera subobject **/
		FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
		
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
};

