// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EquippedObject.generated.h"

class APickup;

UCLASS()
class PRUEBADISEMBODIED_API AEquippedObject : public AActor
{
	GENERATED_BODY()
	
	public:	
		// Sets default values for this actor's properties
		AEquippedObject();

	protected:
		// Called when the game starts or when spawned
		virtual void BeginPlay() override;

	public:	
		// Called every frame
		virtual void Tick(float DeltaTime) override;

	public:

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EquippedObject")
			USceneComponent* EquippedObjectRoot;
		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EquippedObject")
			UStaticMeshComponent* EquippedObjectMesh;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EquippedObject")
			TSubclassOf<APickup> PickupObjectToSpawn;
};
