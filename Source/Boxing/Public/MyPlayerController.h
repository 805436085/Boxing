// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BOXING_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()


public:
	virtual void OnRep_PlayerState() override;

	UFUNCTION(BlueprintImplementableEvent, Category = custom)
		void init();
	
};
