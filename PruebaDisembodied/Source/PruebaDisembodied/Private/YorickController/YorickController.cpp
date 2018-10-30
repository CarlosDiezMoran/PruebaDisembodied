// Fill out your copyright notice in the Description page of Project Settings.

#include "../../Public/YorickController/YorickController.h"
#include "EventsManager/EventsManagerLibrary.h"
#include "Debug/DebugLibrary.h"
#include "PruebaDisembodiedCharacter.h"
#include "Runtime/Engine/Classes/Engine/World.h"

AYorickController::AYorickController() : Super()
{
	DISEMLOG();

	CurrentState = EYorickState::DISABLED;
}

void AYorickController::BeginPlayingState()
{
	DISEMLOG();

	Super::BeginPlayingState();
	YorickCharacter = Cast<APruebaDisembodiedCharacter>(GetPawn());

	if (!YorickCharacter->IsValidLowLevel() || YorickCharacter->IsPendingKill())
	{
		DISEMLOG("Error. YorickOwner is NULL");
	}

	EventsManager = UEventsManagerLibrary::GetEventsManager();

	if (!EventsManager->IsValidLowLevel() || EventsManager->IsPendingKill()) 
	{
		DISEMLOG("Error. EventsManager is NULL");
	}

	SetState(EYorickState::STANDARD);
}

void AYorickController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AYorickController::SetState(EYorickState State)
{
	DISEMLOG();

	InputComponent->AxisBindings.Empty();
	InputComponent->ClearActionBindings();

	switch (State)
	{
		case EYorickState::STANDARD:
			SetStandardState();
			break;
		case EYorickState::DISABLED:
			SetDisabledState();
			break;
		default:
			SetStandardState();
	}
}

EYorickState AYorickController::GetCurrentState()
{
	DISEMLOG();

	return CurrentState;
}

void AYorickController::SetDisabledState()
{
	DISEMLOG();

	CurrentState = EYorickState::DISABLED;
}

void AYorickController::SetStandardState()
{
	DISEMLOG();

	//--------Axis Binding---------------------------------------------------------------------------
	this->InputComponent->BindAxis("Axis_MoveForward", this, &AYorickController::MoveForward);
	this->InputComponent->BindAxis("Axis_MoveRight", this, &AYorickController::MoveRight);
	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	this->InputComponent->BindAxis("Axis_Turn", this, &AYorickController::Turn);
	this->InputComponent->BindAxis("Axis_TurnRate", this, &AYorickController::TurnAtRate);
	this->InputComponent->BindAxis("Axis_LookUp", this, &AYorickController::LookUp);
	this->InputComponent->BindAxis("Axis_LookUpRate", this, &AYorickController::LookUpAtRate);
	//------------------------------------------------------------------------------------------------

	/*

	//--------Action Binding---------------------------------------------------------------------------
	this->InputComponent->BindAction("Action_Use", EInputEvent::IE_Pressed, this, &AKhionController::Interact);
	this->InputComponent->BindAction("Action_Sprint", EInputEvent::IE_Pressed, this, &AKhionController::Sprint);
	*/
}

void AYorickController::MoveForward_Implementation(float Value)
{
	DISEMLOG();

	if (YorickCharacter->IsValidLowLevel() && !YorickCharacter->IsPendingKill() && Value != 0.0f)
	{
		// find out which way is forward
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		YorickCharacter->AddMovementInput(Direction, Value);
	}
}

void AYorickController::MoveRight_Implementation(float Value)
{
	DISEMLOG();

	if (YorickCharacter->IsValidLowLevel() && !YorickCharacter->IsPendingKill() && Value != 0.0f)
	{
		// find out which way is right
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		YorickCharacter->AddMovementInput(Direction, Value);
	}
}

void AYorickController::TurnAtRate_Implementation(float Value)
{
	DISEMLOG();

	if (YorickCharacter->IsValidLowLevel() && !YorickCharacter->IsPendingKill() && Value != 0.0f) 
	{
		// calculate delta for this frame from the rate information
		YorickCharacter->AddControllerYawInput(Value * YorickCharacter->BaseTurnRate * GetWorld()->GetDeltaSeconds());
	}	
}

void AYorickController::Turn_Implementation(float Value)
{
	DISEMLOG();

	if (YorickCharacter->IsValidLowLevel() && !YorickCharacter->IsPendingKill() && Value != 0.0f)
	{
		YorickCharacter->AddControllerYawInput(Value);
	}
}

void AYorickController::LookUp_Implementation(float Value)
{
	DISEMLOG();

	if (YorickCharacter->IsValidLowLevel() && !YorickCharacter->IsPendingKill() && Value != 0.0f) 
	{
		YorickCharacter->AddControllerPitchInput(Value);
	}
}

void AYorickController::LookUpAtRate_Implementation(float Value)
{
	DISEMLOG();

	if (YorickCharacter->IsValidLowLevel() && !YorickCharacter->IsPendingKill() && Value != 0.0f) 
	{
		// calculate delta for this frame from the rate information
		YorickCharacter->AddControllerPitchInput(Value * YorickCharacter->BaseLookUpRate * GetWorld()->GetDeltaSeconds());
	}
}
