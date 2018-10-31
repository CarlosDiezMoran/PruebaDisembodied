// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/Enemies/EnemyCharacter/EnemyCharacter.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Yorick/Character/PruebaDisembodiedCharacter.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "DebugLibrary.h"


// Sets default values
AEnemyCharacter::AEnemyCharacter() : Super()
{
	DISEMLOG();

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	DISEMLOG();

	Super::BeginPlay();

	TArray<AActor*> FoundPlayers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APruebaDisembodiedCharacter::StaticClass(), FoundPlayers);
	if (FoundPlayers.Num() > 0)
	{
		YorickCharacter = Cast<APruebaDisembodiedCharacter>(FoundPlayers[0]);
		if (!YorickCharacter->IsValidLowLevel() || YorickCharacter->IsPendingKill()) 
		{
			DISEMLOG("Error. YorickCharacter is NULL.");
		}
	}
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

