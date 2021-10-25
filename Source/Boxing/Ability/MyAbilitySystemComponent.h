// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "MyGameplayAbilityBase.h"
#include "MyAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class BOXING_API UMyAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	UMyAbilitySystemComponent();

	void GetActiveAbilitiesWithTags(const FGameplayTagContainer& GameplayTagContainer, TArray<UMyGameplayAbilityBase*>& ActiveAbilities);
};
