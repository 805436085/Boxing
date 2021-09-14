// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "MyGameplayAbilityBase.generated.h"

/**
 * 
 */
UCLASS()
class BOXING_API UMyGameplayAbilityBase : public UGameplayAbility
{
	GENERATED_BODY()

public:
	/** Actually activate ability, do not call this directly */
	//virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData);
	
};
