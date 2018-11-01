// Fill out your copyright notice in the Description page of Project Settings.

#include "../../Public/Pickup/Pickup.h"
#include "Runtime/Engine/Classes/Components/SphereComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "YorickController.h"
#include "DebugLibrary.h"

// Sets default values
APickup::APickup()
{
	DISEMLOG();

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Root
	//PickupRoot = CreateDefaultSubobject<USceneComponent>(TEXT("PickupRoot"));
	//SetRootComponent(PickupRoot);

	//Mesh
	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	PickupMesh->SetSimulatePhysics(true);
	PickupMesh->SetMassOverrideInKg(NAME_None, 100.f, true);
	SetRootComponent(PickupMesh);
	//PickupMesh->SetupAttachment(PickupRoot);

	//Detection
	PickupDetection = CreateDefaultSubobject<USphereComponent>(TEXT("PickupDetection"));
	PickupDetection->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	PickupDetection->bGenerateOverlapEvents = true;
	PickupDetection->SetSphereRadius(200.f);
	//PickupDetection->SetupAttachment(PickupRoot);
	PickupDetection->SetupAttachment(PickupMesh);
	
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	DISEMLOG();

	YorickController = Cast<AYorickController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (!YorickController->IsValidLowLevel() || YorickController->IsPendingKill()) 
	{
		DISEMLOG("Error. YorickController is NULL");
	}

	if (PickupDetection->IsValidLowLevel() && !PickupDetection->IsPendingKill()) 
	{
		PickupDetection->OnComponentBeginOverlap.AddDynamic(this, &APickup::OnDetectionBeginOverlap);
		PickupDetection->OnComponentEndOverlap.AddDynamic(this, &APickup::OnDetectionEndOverlap);
	}
	else 
	{
		DISEMLOG("Error. PickupDetection is NULL");
	}

	Super::BeginPlay();
}

void APickup::OnDetectionBeginOverlap(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	DISEMLOG();

	if (YorickController->IsValidLowLevel() && !YorickController->IsPendingKill()) 
	{
		if (YorickController->GetPawn() == OtherActor) 
		{
			YorickController->AddDetectedObject(this);
		}
	}
}

void APickup::OnDetectionEndOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	DISEMLOG();

	if (YorickController->IsValidLowLevel() && !YorickController->IsPendingKill())
	{
		if (YorickController->GetPawn() == OtherActor)
		{
			YorickController->RemoveDetectedObject(this);
		}
	}
}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

