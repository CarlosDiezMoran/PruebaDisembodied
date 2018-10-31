// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/Enemies/FlyingEnemy/Character/FlyingEnemy.h"
#include "Yorick/Character/PruebaDisembodiedCharacter.h"
#include "DebugLibrary.h"

AFlyingEnemy::AFlyingEnemy() : Super() 
{
	DISEMLOG();

	HidePointsID = -1;
	HidePointsToGoBeforeNextAttack = 1;
}

void AFlyingEnemy::BeginPlay()
{
	DISEMLOG();

	Super::BeginPlay();
}

void AFlyingEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
