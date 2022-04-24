// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "BoxingGameModeBase.generated.h"

/**
 * 
 */
UCLASS(minimalapi)
class ABoxingGameModeBase : public AGameMode
{
	GENERATED_BODY()
		
public:
	ABoxingGameModeBase();

public:
	virtual void heroDie(AController* Controller);
	virtual void RespawnHero(AController* Controller);

protected:
	TSubclassOf<class AMyCharacterBase> HeroClass;
	
private:
	float RespawnDelay;
};
