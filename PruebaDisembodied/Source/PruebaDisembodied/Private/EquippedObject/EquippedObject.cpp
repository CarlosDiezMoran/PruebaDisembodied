// Fill out your copyright notice in the Description page of Project Settings.

#include "EquippedObject/EquippedObject.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "DebugLibrary.h"


// Sets default values
AEquippedObject::AEquippedObject()
{
	DISEMLOG();

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Root
	EquippedObjectRoot = CreateDefaultSubobject<USceneComponent>(TEXT("EquippedObjectRoot"));
	SetRootComponent(EquippedObjectRoot);

	//Mesh
	EquippedObjectMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EquippedObjectMesh"));
	EquippedObjectMesh->SetupAttachment(EquippedObjectRoot);
	EquippedObjectMesh->SetCollisionProfileName("EquippedObject");
}

// Called when the game starts or when spawned
void AEquippedObject::BeginPlay()
{
	DISEMLOG();

	Super::BeginPlay();
	
}

// Called every frame
void AEquippedObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

