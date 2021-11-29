// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAttributeSet.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"
#include "MyCharacterBase.h"

UMyAttributeSet::UMyAttributeSet()
	: Health(100.0f)
	, MaxHealth(100.0f)
	, Mana(100.0f)
	, MaxMana(100.0f)
	, SP(100.0f)
	, MaxSP(100.0f)
	, AttackPower(1.0f)
	, DefensePower(1.0f)
	, MoveSpeed(1.0f)
	, Damage(0.0f)
{
}

void UMyAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData & Data)
{
	Super::PostGameplayEffectExecute(Data);

	// Compute the delta between old and new, if it is available
	float DeltaValue = 0;
	if (Data.EvaluatedData.ModifierOp == EGameplayModOp::Type::Additive)
	{
		DeltaValue = Data.EvaluatedData.Magnitude;
	}

	AMyCharacterBase* TargetCharacter = nullptr;
	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		TargetCharacter = Cast<AMyCharacterBase>(Data.Target.AbilityActorInfo->AvatarActor.Get());
	}

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		// Handle other health changes such as from healing or direct modifiers
		// First clamp it
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
		
		if (TargetCharacter)
		{
			// Call for all health changes
			TargetCharacter->HandleHealthChanged(DeltaValue);
		}
	}
	else if (Data.EvaluatedData.Attribute == GetSPAttribute())
	{
		SetSP(FMath::Clamp(GetSP(), 0.0f, GetMaxSP()));

		if (TargetCharacter)
		{
			TargetCharacter->HandleSPChanged(DeltaValue);
		}
	}
	else if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
		SetDamage(0.0f);
		DeltaValue = 0 - DeltaValue;
		if (TargetCharacter)
		{
			TargetCharacter->HandleHealthChanged(DeltaValue);
		}
	}
}
