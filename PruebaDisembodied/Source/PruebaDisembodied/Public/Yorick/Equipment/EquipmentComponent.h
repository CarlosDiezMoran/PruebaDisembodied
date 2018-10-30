// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EquipmentComponent.generated.h"

class AEquippedObject;

UENUM(BlueprintType)
enum class EEquipmentType : uint8 {
	LEFT_HAND,
	RIGHT_HAND,
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PRUEBADISEMBODIED_API UEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

	public:	
		// Sets default values for this component's properties
		UEquipmentComponent();

	protected:
		// Called when the game starts
		virtual void BeginPlay() override;

	public:	
		// Called every frame
		virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
		UFUNCTION(BlueprintCallable)
			void AddEquippedObject(AEquippedObject* Object);
		UFUNCTION(BlueprintCallable)
			void RemoveEquippedObject();

	public:

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EquipmentComponent")
			FName SocketOwner;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EquipmentComponent")
			AEquippedObject* EquippedObject;
		
};
