// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "Boxing/Ability/MyAbilitySystemComponent.h"
#include "Boxing/Ability/MyAttributeSet.h"
#include "MyPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class BOXING_API AMyPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AMyPlayerState();

	// Implement IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UMyAttributeSet* GetAttributeSet() const;
	
protected:
	/** The component used to handle ability system interactions */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Abilities)
		UMyAbilitySystemComponent* AbilitySystemComponent;

	/** List of attributes modified by the ability system */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities)
		UMyAttributeSet* AttributeSet;
};
