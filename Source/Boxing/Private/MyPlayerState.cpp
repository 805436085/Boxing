// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerState.h"
#include "MyCharacterBase.h"

AMyPlayerState::AMyPlayerState()
{
	// Create ability system component, and set it to be explicitly replicated
	AbilitySystemComponent = CreateDefaultSubobject<UMyAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);

	// Mixed mode means we only are replicated the GEs to ourself, not the GEs to simulated proxies. If another GDPlayerState (Hero) receives a GE,
	// we won't be told about it by the Server. Attributes, GameplayTags, and GameplayCues will still replicate to us.
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Full);

	// Set PlayerState's NetUpdateFrequency to the same as the Character.
	// Default is very low for PlayerStates and introduces perceived lag in the ability system.
	// 100 is probably way too high for a shipping game, you can adjust to fit your needs.
	NetUpdateFrequency = 100.0f;

	// Create the attribute set, this replicates by default
	AttributeSet = CreateDefaultSubobject<UMyAttributeSet>(TEXT("AttributeSet"));

	
}

UAbilitySystemComponent* AMyPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UMyAttributeSet* AMyPlayerState::GetAttributeSet() const
{
	return AttributeSet;
}

void AMyPlayerState::BeginPlay()
{
	Super::BeginPlay();

	if (AbilitySystemComponent)
	{
		HealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHealthAttribute()).AddUObject(this, &AMyPlayerState::HealthChanged);
	}
}

void AMyPlayerState::HealthChanged(const FOnAttributeChangeData& Data)
{
	float oldValue = Data.OldValue;
	float newValue = Data.NewValue;

	AMyCharacterBase* hero = Cast<AMyCharacterBase>(GetPawn());
	if (hero)
	{
		hero->HandleHealthChanged(newValue);

		if (newValue < oldValue)
		{
			if (!hero->isAlive())
			{
				if (!hero->isDie())
				{
					hero->Die();
				}
			}
			else
			{
				hero->playHurt();
			}
		}
	}
}
