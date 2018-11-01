// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BombComponent.generated.h"

class UTextRenderComponent;
class USphereComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PRUEBADISEMBODIED_API UBombComponent : public UActorComponent
{
	GENERATED_BODY()

	public:	
		// Sets default values for this component's properties
		UBombComponent();

		// Called every frame
		virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		UFUNCTION(BlueprintCallable, Category = "BombComponent")
			void InitBomb(float TimeToExplosion = -1.f, float CurrentTimeToExplode = -1.f);
		UFUNCTION(BlueprintCallable, Category = "BombComponent")
			void UnInitBomb();
		UFUNCTION(BlueprintCallable, Category = "BombComponent")
			void Explode();

	protected:
		// Called when the game starts
		virtual void BeginPlay() override;
		virtual void BeginDestroy() override;

	private:	
		UFUNCTION()
			void UpdateTimerBomb();

	public:
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BombComponent")
			float TimeToExplode;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BombComponent")
			float CurrentTime;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BombComponent")
			UTextRenderComponent *TextRender;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BombComponent")
			USphereComponent* ExplosionDetection;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BombComponent")
			float ExplosionDamage;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BombComponent")
			float ExplosionRadius;

	private:
		FTimerDelegate TimerBombDel;
		FTimerHandle TimerBombHandle;
		float TimeBetweenUpdates = 0.01f;
		bool bHasBeenInitialized = false;
};
