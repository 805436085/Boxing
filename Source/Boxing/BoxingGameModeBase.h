// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BoxingGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class BOXING_API ABoxingGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
		
public:
	ABoxingGameModeBase();

public:
	virtual void heroDie(AController* Controller);
	virtual void RespawnHero(AController* Controller);

private:
	float RespawnDelay;
};
