// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class PRUEBADISEMBODIED_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

	public:
		// Sets default values for this character's properties
		AEnemyCharacter();

	protected:
		// Called when the game starts or when spawned
		virtual void BeginPlay() override;

	public:	
		// Called every frame
		virtual void Tick(float DeltaTime) override;

	public:

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy")
			class APruebaDisembodiedCharacter* YorickCharacter;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
			float ChaseVelocity = 300.f;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
			float RunAwayVelocity = 400.f;
};
