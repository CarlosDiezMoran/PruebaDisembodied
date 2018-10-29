// Fill out your copyright notice in the Description page of Project Settings.

#include "../../Public/YorickController/YorickController.h"
#include "EventsManager/EventsManagerLibrary.h"
#include "Debug/DebugLibrary.h"
#include "PruebaDisembodiedCharacter.h"

AYorickController::AYorickController() : Super()
{
	DISEMLOG();

	CurrentState = EYorickState::STANDARD;
}

void AYorickController::BeginPlayingState()
{
	DISEMLOG();

	Super::BeginPlayingState();
	YorickOwner = Cast<APruebaDisembodiedCharacter>(GetPawn());

	if (!YorickOwner->IsValidLowLevel() || YorickOwner->IsPendingKill()) 
	{
		DISEMLOG("Error. YorickOwner is NULL");
	}

	EventsManager = UEventsManagerLibrary::GetEventsManager();

	if (!EventsManager->IsValidLowLevel() || EventsManager->IsPendingKill()) 
	{
		DISEMLOG("Error. EventsManager is NULL");
	}
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

	return EYorickState();
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
	//this->InputComponent->BindAction("Action_Sprint"			, EInputEvent::IE_Released,this, &AKhionController::SprintRelease);
	this->InputComponent->BindAction("Action_WatchBracelet", EInputEvent::IE_Pressed, this, &AKhionController::WatchBracelet);
	this->InputComponent->BindAction("Action_WatchBracelet", EInputEvent::IE_Released, this, &AKhionController::WatchBraceletRelease);
	this->InputComponent->BindAction("Action_Aim", EInputEvent::IE_Pressed, this, &AKhionController::Aim);
	this->InputComponent->BindAction("Action_Aim", EInputEvent::IE_Released, this, &AKhionController::AimRelease);
	this->InputComponent->BindAction("Action_Reload", EInputEvent::IE_Released, this, &AKhionController::EnterQTE);
	this->InputComponent->BindAction("Action_Reload", EInputEvent::IE_Pressed, this, &AKhionController::ShowAmmo);
	this->InputComponent->BindAction("Action_Fire", EInputEvent::IE_Pressed, this, &AKhionController::Melee);
	this->InputComponent->BindAction("Action_ThermalVision", EInputEvent::IE_Pressed, this, &AKhionController::ActivateThermal);
	this->InputComponent->BindAction("Action_Heating", EInputEvent::IE_Pressed, this, &AKhionController::Heating);
	this->InputComponent->BindAction("Action_Flashlight", EInputEvent::IE_Pressed, this, &AKhionController::ToggleFlashlight);
	this->InputComponent->BindAction("Action_Crouch", EInputEvent::IE_Pressed, this, &AKhionController::Crouch);
	this->InputComponent->BindAction("Action_Inventory", EInputEvent::IE_Pressed, this, &AKhionController::OpenMenu);
	this->InputComponent->BindAction("Action_Up", EInputEvent::IE_Released, this, &AKhionController::UnequipObject);
	this->InputComponent->BindAction("Action_Left", EInputEvent::IE_Released, this, &AKhionController::SelectRange);
	this->InputComponent->BindAction("Action_Down", EInputEvent::IE_Released, this, &AKhionController::SelectRegeneration);
	this->InputComponent->BindAction("Action_Right", EInputEvent::IE_Released, this, &AKhionController::SelectDistraction);
	this->InputComponent->BindAction("Action_Look", EInputEvent::IE_Pressed, this, &AKhionController::Looking);
	this->InputComponent->BindAction("Action_Pause", EInputEvent::IE_Pressed, this, &AKhionController::PauseMenu);
	*/
}

void AYorickController::MoveForward_Implementation(float Value)
{
}

void AYorickController::MoveRight_Implementation(float Value)
{
}

void AYorickController::TurnAtRate_Implementation(float Value)
{
}

void AYorickController::Turn_Implementation(float Value)
{
}

void AYorickController::LookUp_Implementation(float Value)
{
}

void AYorickController::LookUpAtRate_Implementation(float Value)
{
}
