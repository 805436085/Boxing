// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAbilitySystemComponent.h"

UMyAbilitySystemComponent::UMyAbilitySystemComponent()
{
	m_bAbilitiesHaveGiven = false;
}

void UMyAbilitySystemComponent::setAbilitiesHaveGiven(bool b)
{
	m_bAbilitiesHaveGiven = b;
}

bool UMyAbilitySystemComponent::getAbilitiesHaveGiven()
{
	return m_bAbilitiesHaveGiven;
}

void UMyAbilitySystemComponent::GetActiveAbilitiesWithTags(const FGameplayTagContainer& GameplayTagContainer, TArray<UMyGameplayAbilityBase*>& ActiveAbilities)
{
	TArray<FGameplayAbilitySpec*> AbilitiesToActivate;
	GetActivatableGameplayAbilitySpecsByAllMatchingTags(GameplayTagContainer, AbilitiesToActivate, false);

	if (AbilitiesToActivate.Num() == 0)
		int j = 0;

	// Iterate the list of all ability specs
	for (FGameplayAbilitySpec* Spec : AbilitiesToActivate)
	{
		// Iterate all instances on this ability spec
		TArray<UGameplayAbility*> AbilityInstances = Spec->GetAbilityInstances();

		for (UGameplayAbility* ActiveAbility : AbilityInstances)
		{
			ActiveAbilities.Add(Cast<UMyGameplayAbilityBase>(ActiveAbility));
		}
	}
}