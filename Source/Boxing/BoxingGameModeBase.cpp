// Copyright Epic Games, Inc. All Rights Reserved.


#include "BoxingGameModeBase.h"
#include "MyPlayerController.h"
#include "MyCharacterBase.h"
#include "GameFramework/SpectatorPawn.h"
#include "TimerManager.h"
#include "Engine/World.h"

ABoxingGameModeBase::ABoxingGameModeBase()
{
	RespawnDelay = 5.0f;
	HeroClass = StaticLoadClass(UObject::StaticClass(), nullptr, TEXT("/Game/Boxing/Blueprints/Player/BP_PlayerCharacter.BP_PlayerCharacter_C"));
}


void ABoxingGameModeBase::heroDie(AController* Controller)
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	ASpectatorPawn* SpectatorPawn = GetWorld()->SpawnActor<ASpectatorPawn>(SpectatorClass, Controller->GetPawn()->GetActorTransform(), SpawnParameters);

	Controller->UnPossess();
	Controller->Possess((APawn*)SpectatorPawn);

	FTimerHandle RespawnTimerHandle;
	FTimerDelegate RespawnDelegate;

	RespawnDelegate = FTimerDelegate::CreateUObject(this, &ABoxingGameModeBase::RespawnHero, Controller);
	GetWorldTimerManager().SetTimer(RespawnTimerHandle, RespawnDelegate, RespawnDelay, false);

	// AMyPlayerController* PC = Cast<AMyPlayerController>(Controller);
	// if (PC)
	// {
	// 	PC->SetRespawnCountdown(RespawnDelay);
	// }
}

void ABoxingGameModeBase::RespawnHero(AController* Controller)
{
	if (Controller->IsPlayerController())
	{
		// Respawn player hero
		AActor* PlayerStart = FindPlayerStart(Controller);

		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		AMyCharacterBase* Hero = GetWorld()->SpawnActor<AMyCharacterBase>(HeroClass, PlayerStart->GetActorLocation(), PlayerStart->GetActorRotation(), SpawnParameters);

		APawn* OldSpectatorPawn = Controller->GetPawn();
		Controller->UnPossess();
		OldSpectatorPawn->Destroy();
		Controller->Possess(Hero);
	}
	else
	{
		// Respawn AI hero
		// FActorSpawnParameters SpawnParameters;
		// SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		//
		// AMyCharacterBase* Hero = GetWorld()->SpawnActor<AMyCharacterBase>(HeroClass, EnemySpawnPoint->GetActorTransform(), SpawnParameters);
		//
		// APawn* OldSpectatorPawn = Controller->GetPawn();
		// Controller->UnPossess();
		// OldSpectatorPawn->Destroy();
		// Controller->Possess(Hero);
	}
}