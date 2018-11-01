// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemModifier/BombComponent.h"
#include "Runtime/Engine/Classes/Components/TextRenderComponent.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Runtime/Engine/Classes/Components/SphereComponent.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Yorick/Character/PruebaDisembodiedCharacter.h"
#include "DebugLibrary.h"


// Sets default values for this component's properties
UBombComponent::UBombComponent()
{
	DISEMLOG();

	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	//Bind update timer function
	TimerBombDel.BindUFunction(this, FName("UpdateTimerBomb"));

	//Text Renderer Counter
	TextRender = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRender"));

	ExplosionDetection = CreateDefaultSubobject<USphereComponent>(TEXT("ExplosionDetection"));
	ExplosionDetection->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ExplosionDetection->bGenerateOverlapEvents = true;
	ExplosionDetection->SetSphereRadius(ExplosionRadius);
	
}

// Called when the game starts
void UBombComponent::BeginPlay()
{
	DISEMLOG();

	Super::BeginPlay();

	InitBomb();

	// ...
}

void UBombComponent::BeginDestroy()
{
	DISEMLOG();
	
	UnInitBomb();

	Super::BeginDestroy();
}

void UBombComponent::UpdateTimerBomb()
{
	CurrentTime += TimeBetweenUpdates;

	FNumberFormattingOptions NumberFormatOptions;
	NumberFormatOptions.RoundingMode = ERoundingMode::HalfToEven;
	NumberFormatOptions.MinimumIntegralDigits = 1;
	NumberFormatOptions.MinimumFractionalDigits = 2;
	NumberFormatOptions.MaximumFractionalDigits = 2;

	TextRender->SetText(FText::AsNumber(TimeToExplode - CurrentTime, &NumberFormatOptions));

	if (CurrentTime > TimeToExplode) 
	{
		Explode();
	}
}

// Called every frame
void UBombComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBombComponent::InitBomb(float TimeToExplosion, float CurrentTimeTExplode)
{
	DISEMLOG();
	AActor* Owner = GetOwner();

	if (Owner->IsValidLowLevel() && !Owner->IsPendingKill()) 
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		FRotator ControlRotator = PlayerController->GetControlRotation();
		ControlRotator += FRotator(0.0f, 180.f, 0.f);
		TextRender->AttachToComponent(Owner->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform, NAME_None);
		TextRender->SetRelativeLocation(FVector(0.f, 0.f, 100.f));
		TextRender->SetWorldRotation(ControlRotator);
		TextRender->SetTextRenderColor(FColor(255, 0, 69, 255));
		TextRender->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
		ExplosionDetection->SetSphereRadius(ExplosionRadius);
		ExplosionDetection->ShapeColor = FColor::Blue;
		ExplosionDetection->bHiddenInGame = false;
		ExplosionDetection->AttachToComponent(Owner->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform, NAME_None);
	}

	bHasBeenInitialized = true;

	if (TimeToExplosion >= 0.f)
	{
		TimeToExplode = TimeToExplosion;
	}

	if (CurrentTimeTExplode >= 0.f)
	{
		CurrentTime = CurrentTimeTExplode;
	}
	
	FNumberFormattingOptions NumberFormatOptions;
	NumberFormatOptions.RoundingMode = ERoundingMode::HalfToEven;
	NumberFormatOptions.MinimumIntegralDigits = 1;
	NumberFormatOptions.MinimumFractionalDigits = 2;
	NumberFormatOptions.MaximumFractionalDigits = 2;
	TextRender->SetText(FText::AsNumber(TimeToExplode - CurrentTime, &NumberFormatOptions));

	if (CurrentTime > TimeToExplode)
	{
		Explode();
	}
	else 
	{
		GetWorld()->GetTimerManager().SetTimer(TimerBombHandle, TimerBombDel, TimeBetweenUpdates, true);
	}
}

void UBombComponent::UnInitBomb() 
{
	DISEMLOG();
	/*
	if (bHasBeenInitialized) 
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerBombHandle);
		TextRender->SetText(FString(""));
	}
	*/
}

void UBombComponent::Explode() 
{
	DISEMLOG();

	GetWorld()->GetTimerManager().ClearTimer(TimerBombHandle);

	TextRender->SetText(FText::FromString("Boom!"));

	TArray<AActor*> OverlappingActors;

	ExplosionDetection->GetOverlappingActors(OverlappingActors, APruebaDisembodiedCharacter::StaticClass());

	if (OverlappingActors.Num() > 0) 
	{

		if (OverlappingActors[0]->GetClass()->ImplementsInterface(UDamageable::StaticClass()))
		{
			IDamageable::Execute_OnDamage(OverlappingActors[0], ExplosionDamage, GetOwner());
		}
		
	}

	GetOwner()->Destroy();
}

