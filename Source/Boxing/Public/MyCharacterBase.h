// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Boxing/Ability/MyAbilitySystemComponent.h"
#include "Boxing/Ability/MyAttributeSet.h"
#include "Boxing/Ability/MyGameplayAbilityBase.h"
#include "GameplayAbilitySpec.h"
#include "MyCharacterBase.generated.h"

UCLASS()
class BOXING_API AMyCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacterBase();

	// Implement IAbilitySystemInterface
	virtual UMyAbilitySystemComponent* GetAbilitySystemComponent() const;

	virtual void PossessedBy(AController* NewController) override;
	virtual void UnPossessed() override;

	/** Apply the startup gameplay abilities and effects */
	void AddStartupGameplayAbilities();

	/** Attempts to remove any startup gameplay abilities */
	void RemoveStartupGameplayAbilities();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = custom)
		void OnMeleeAttackNotify(const FGameplayTag& Tag);

protected:
	/** The component used to handle ability system interactions */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UMyAbilitySystemComponent* AbilitySystemComponent;

	/** List of attributes modified by the ability system */
	UPROPERTY()
		UMyAttributeSet* AttributeSet;

	/** Abilities to grant to this character on creation. These will be activated by tag or event and are not bound to specific inputs */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities)
		TArray<TSubclassOf<UGameplayAbility>> GameplayAbilities;

	/** If true we have initialized our abilities */
	UPROPERTY()
		bool bAbilitiesInitialized;

	/** Abilities to grant to this character on creation. These will be activated by tag or event and are not bound to specific inputs */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = custom)
		bool bIsAttacking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities)
		FGameplayTag CurrentGameplayTag;

	UFUNCTION(BlueprintCallable)
		void GiveAbility();
};
