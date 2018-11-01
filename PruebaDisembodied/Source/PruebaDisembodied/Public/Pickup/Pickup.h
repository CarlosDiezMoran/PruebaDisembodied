// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

class USphereComponent;
class AYorickController;
class AEquippedObject;

UCLASS()
class PRUEBADISEMBODIED_API APickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
		virtual void OnDetectionBeginOverlap(class UPrimitiveComponent* HitComp = nullptr, class AActor* OtherActor = nullptr, class UPrimitiveComponent* OtherComp = nullptr, int32 OtherBodyIndex = 0, bool bFromSweep = false, const FHitResult & SweepResult = FHitResult());
	UFUNCTION()
		virtual void OnDetectionEndOverlap(class UPrimitiveComponent* OverlappedComp = nullptr, class AActor* OtherActor = nullptr, class UPrimitiveComponent* OtherComp = nullptr, int32 OtherBodyIndex = 0);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* PickupMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Pickup")
		USphereComponent* PickupDetection;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
		TSubclassOf<AEquippedObject> EquippedObjectToSpawn;

protected:

	AYorickController* YorickController;

	
	
};
