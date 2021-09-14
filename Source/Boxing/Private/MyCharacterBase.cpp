// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacterBase.h"

// Sets default values
AMyCharacterBase::AMyCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create ability system component, and set it to be explicitly replicated
	AbilitySystemComponent = CreateDefaultSubobject<UMyAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	//AbilitySystemComponent->SetIsReplicated(true);

	// Create the attribute set, this replicates by default
	AttributeSet = CreateDefaultSubobject<UMyAttributeSet>(TEXT("AttributeSet"));

	bAbilitiesInitialized = false;
}

UMyAbilitySystemComponent * AMyCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AMyCharacterBase::PossessedBy(AController * NewController)
{
	Super::PossessedBy(NewController);

	/*if (AbilitySystemComponent)
	{
		AddStartupGameplayAbilities();
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}*/
}

void AMyCharacterBase::UnPossessed()
{
}

void AMyCharacterBase::GiveAbility()
{
	if (AbilitySystemComponent)
	{
		AddStartupGameplayAbilities();
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
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
