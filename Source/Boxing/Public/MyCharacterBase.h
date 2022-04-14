// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "../Ability/MyGameplayAbilityBase.h"
#include "GameplayAbilitySpec.h"
#include "MyCharacterBase.generated.h"

UCLASS()
class BOXING_API AMyCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacterBase();

	// Implement IAbilitySystemInterface
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	/** Update the character. (Running, health etc). */
	virtual void Tick(float DeltaSeconds) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void UnPossessed() override;

	/** Apply the startup gameplay abilities and effects */
	void AddStartupGameplayAbilities();

	/** Attempts to remove any startup gameplay abilities */
	void RemoveStartupGameplayAbilities();

	void HandleHealthChanged(float newHealth);

	virtual void OnRep_PlayerState();

	

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
		void OnHealthChanged(float newHealth);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = custom)
		void OnDamaged(float DeltaValue);

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

	UFUNCTION(BlueprintImplementableEvent, Category = custom)
		void OnClientInit();

	UFUNCTION(BlueprintCallable, Category = "GAS|Attributes")
		float GetHealth();

	UFUNCTION(BlueprintCallable, Category = "GAS|Attributes")
		float GetMaxHealth();

	UFUNCTION(BlueprintCallable, Category = custom)
		bool isAlive();

	UFUNCTION(BlueprintCallable, Category = custom)
		void playHurt();

	UFUNCTION(BlueprintCallable, Category = custom)
		void Die();

	UFUNCTION(BlueprintCallable, Category = custom)
		void playDie();

	UFUNCTION(BlueprintCallable, Category = custom)
		bool isDie();

	UFUNCTION(BlueprintCallable, Category = custom)
		void FinishDying();

	UFUNCTION(BlueprintCallable, Server, Reliable, Category = custom)
		void preMeleeAttack(bool isFist);

	UFUNCTION(NetMulticast, Reliable, Category = custom)
		void doMeleeAttack(bool isFist);

	UFUNCTION(BlueprintImplementableEvent, Category = custom)
			void doMeleeAttackServer(bool isFist);
	
	UFUNCTION(BlueprintImplementableEvent, Category = custom)
		void doMeleeAttackClient(bool isFist);

protected:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = custom)
		void InitBoxCollision();

	UFUNCTION(BlueprintImplementableEvent, Category = custom)
		void CreateHUD();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Abilities)
	TWeakObjectPtr<class UMyAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities)
	TWeakObjectPtr<class UMyAttributeSet> AttributeSet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities)
		FGameplayTag CurrentGameplayTag;

	/** Abilities to grant to this character on creation. These will be activated by tag or event and are not bound to specific inputs */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities)
		TArray<TSubclassOf<UMyGameplayAbilityBase>> GameplayAbilities;

	/** If true we have initialized our abilities */
	UPROPERTY(BlueprintReadOnly)
		bool bAbilitiesInitialized;

	/** Abilities to grant to this character on creation. These will be activated by tag or event and are not bound to specific inputs */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = custom)
		bool bIsAttacking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = custom)
		TArray<AMyCharacterBase*> CollisionTargetArray;

	// Death Animation
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GAS|Animation")
		UAnimMontage* DeathMontage;

	// Hurt Animation
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GAS|Animation")
		UAnimMontage* HurtMontage;
/**
* Setters for Attributes. Only use these in special cases like Respawning, otherwise use a GE to change Attributes.
* These change the Attribute's Base Value.
*/

	virtual void SetHP(float Health);
	virtual void SetMP(float Mana);
	virtual void SetSP(float Stamina);


	void BindASCInput();

private:
	const int32 defaultLevel = 1;
	bool ASCInputBound = false;

	bool isDead;
};
