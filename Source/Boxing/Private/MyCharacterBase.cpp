// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacterBase.h"
#include "GameFramework/PlayerState.h"

// Sets default values
AMyCharacterBase::AMyCharacterBase()
	: bAbilitiesInitialized(false)
	, bIsAttacking(false)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create ability system component, and set it to be explicitly replicated
	AbilitySystemComponent = CreateDefaultSubobject<UMyAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);

	// Create the attribute set, this replicates by default
	AttributeSet = CreateDefaultSubobject<UMyAttributeSet>(TEXT("AttributeSet"));
}

UAbilitySystemComponent * AMyCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}


void AMyCharacterBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (AttributeSet && bAbilitiesInitialized)
	{
		float SP = DeltaSeconds * 10 + AttributeSet->GetSP();
		if (SP > AttributeSet->GetMaxSP())
			SP = AttributeSet->GetMaxSP();
		else if (SP < 0)
			SP = 0.0f;
		AttributeSet->SetSP(SP);
	}
}

//
void AMyCharacterBase::PossessedBy(AController * NewController)
{
	Super::PossessedBy(NewController);

	if (AbilitySystemComponent)
	{
		AddStartupGameplayAbilities();
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}

void AMyCharacterBase::UnPossessed()
{
}

void AMyCharacterBase::AddStartupGameplayAbilities()
{
	check(AbilitySystemComponent);

	if (!bAbilitiesInitialized)
	{
		for (int i = 0; i < GameplayAbilities.Num(); i++)
		{
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(GameplayAbilities[i]/*, 1, INDEX_NONE, this*/));
		}
		bAbilitiesInitialized = true;
	}
}

void AMyCharacterBase::RemoveStartupGameplayAbilities()
{
}

void AMyCharacterBase::HandleHealthChanged(float DeltaValue)
{
	if (bAbilitiesInitialized)
	{
		OnDamaged(DeltaValue);
	}
}

void AMyCharacterBase::OnRep_PlayerState()
{
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}

void AMyCharacterBase::HandleSPChanged(float DeltaValue)
{
	if (bAbilitiesInitialized && AttributeSet)
	{
		float SP = AttributeSet->GetSP() + DeltaValue;
		if (SP > AttributeSet->GetMaxSP())
			SP = AttributeSet->GetMaxSP();
		else if (SP < 0)
			SP = 0.0f;
		AttributeSet->SetSP(SP);
	}
}

void AMyCharacterBase::UpdateHP(float HP)
{
	if (AttributeSet)
	{
		AttributeSet->SetHealth(HP);
	}
}

void AMyCharacterBase::GetActiveAbilitiesWithTags(FGameplayTagContainer AbilityTags, TArray<UMyGameplayAbilityBase*>& ActiveAbilities)
{
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->GetActiveAbilitiesWithTags(AbilityTags, ActiveAbilities);
	}
}
