// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Enemies/EnemyCharacter/EnemyCharacter.h"
#include "FlyingEnemy.generated.h"

UCLASS()
class PRUEBADISEMBODIED_API AFlyingEnemy : public AEnemyCharacter
{
	GENERATED_BODY()
	
	public:
		// Sets default values for this character's properties
		AFlyingEnemy();

	protected:
		// Called when the game starts or when spawned
		virtual void BeginPlay() override;

	public:
		// Called every frame
		virtual void Tick(float DeltaTime) override;

	public:
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flying Enemy")
			int32 HidePointsID;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flying Enemy")
			int32 HidePointsToGoBeforeNextAttack;
};
