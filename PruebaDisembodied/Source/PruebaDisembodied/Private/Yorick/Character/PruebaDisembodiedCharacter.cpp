// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "PruebaDisembodiedCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "DebugLibrary.h"
#include "Pickup/Pickup.h"
#include "EquipmentComponent.h"

APruebaDisembodiedCharacter::APruebaDisembodiedCharacter()
{
	DISEMLOG();

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	//Equipment
	RightHand = CreateDefaultSubobject<UEquipmentComponent>(TEXT("RightHand"));
	AddOwnedComponent(RightHand);
	LeftHand = CreateDefaultSubobject<UEquipmentComponent>(TEXT("LeftHand"));
	AddOwnedComponent(LeftHand);
}

void APruebaDisembodiedCharacter::AddDetectedObject(APickup * DetectedObject)
{
	DISEMLOG();
	InteractiveObjects.AddUnique(DetectedObject);
	FindClosestObject();
}

void APruebaDisembodiedCharacter::RemoveDetectedObject(APickup * DetectedObject)
{
	DISEMLOG();
	InteractiveObjects.RemoveSingle(DetectedObject);
	FindClosestObject();
}

void APruebaDisembodiedCharacter::FindClosestObject()
{
	DISEMLOG();
	
	FVector YorickLocation = GetActorLocation();

	float CosDetectionAngle = FMath::Cos(DetectionAngle);
	float ClosestDist = 9999999.f;

	for (APickup* InteractiveObject : InteractiveObjects) 
	{
		if (InteractiveObject->IsValidLowLevel() && !InteractiveObject->IsPendingKill()) 
		{
			float DotRes = GetDotProductTo(InteractiveObject);

			//Is inside field of view
			if (DotRes > CosDetectionAngle)
			{
				FVector PickupLocation = InteractiveObject->GetActorLocation();
				float Distance = FVector::Distance(YorickLocation,PickupLocation);

				//Check closest
				if (Distance < ClosestDist) 
				{
					ClosestDist = Distance;
					ClosestInteractiveObject = InteractiveObject;
				}
			}
		}
	}

	if (ClosestDist == 9999999.f) 
	{
		ClosestInteractiveObject = nullptr;
	}
}
