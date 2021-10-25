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
class BOXING_API AMyCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacterBase();

	/** Update the character. (Running, health etc). */
	virtual void Tick(float DeltaSeconds) override;

	// Implement IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const;

	virtual void PossessedBy(AController* NewController) override;
	virtual void UnPossessed() override;

	/** Apply the startup gameplay abilities and effects */
	void AddStartupGameplayAbilities();

	/** Attempts to remove any startup gameplay abilities */
	void RemoveStartupGameplayAbilities();

	void HandleHealthChanged(float DeltaValue);

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = custom)
		void NotifyBegin_OnMeleeAttack();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = custom)
		void NotifyEnd_OnMeleeAttack();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = custom)
		void NotifyBegin_OnMeleeAttack_LeftHand();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = custom)
		void NotifyEnd_OnMeleeAttack_LeftHand();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = custom)
		void NotifyBegin_OnMeleeAttack_RightHand();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = custom)
		void NotifyEnd_OnMeleeAttack_RightHand();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = custom)
		void OnHealthChanged(float DeltaValue);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = custom)
		void OnSPChanged(float DeltaValue);

	UFUNCTION(BlueprintCallable, Category = custom)
	void HandleSPChanged(float DeltaValue);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = custom)
		void OnMPChanged(float DeltaValue);

	UFUNCTION(BlueprintCallable, Category = custom)
		void UpdateHP(float HP);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = custom)
		void UpdateStatus();

	/** Returns a list of currently active ability instances that match the tags */
	UFUNCTION(BlueprintCallable, Category = custom)
		void GetActiveAbilitiesWithTags(FGameplayTagContainer AbilityTags, TArray<UMyGameplayAbilityBase*>& ActiveAbilities);

protected:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = custom)
		void InitBoxCollision();

protected:
	/** The component used to handle ability system interactions */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UMyAbilitySystemComponent* AbilitySystemComponent;

	/** List of attributes modified by the ability system */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities)
		UMyAttributeSet* AttributeSet;

	/** Abilities to grant to this character on creation. These will be activated by tag or event and are not bound to specific inputs */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities)
		TArray<TSubclassOf<UGameplayAbility>> GameplayAbilities;

	/** If true we have initialized our abilities */
	UPROPERTY(BlueprintReadOnly)
		bool bAbilitiesInitialized;

	/** Abilities to grant to this character on creation. These will be activated by tag or event and are not bound to specific inputs */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = custom)
		bool bIsAttacking;

	/** Abilities to grant to this character on creation. These will be activated by tag or event and are not bound to specific inputs */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = custom)
		bool bIsUsingMelee;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = custom)
		TArray<AMyCharacterBase*> CollisionTargetArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities)
		FGameplayTag CurrentGameplayTag;
};
