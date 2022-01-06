// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacterBase.h"
#include "MyPlayerState.h"

// Sets default values
AMyCharacterBase::AMyCharacterBase()
	: bAbilitiesInitialized(false)
	, bIsAttacking(false)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

UAbilitySystemComponent* AMyCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent.Get();
}

void AMyCharacterBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (AttributeSet.IsValid() && bAbilitiesInitialized)
	{
		float SP = DeltaSeconds * 10 + AttributeSet->GetSP();
		if (SP > AttributeSet->GetMaxSP())
			SP = AttributeSet->GetMaxSP();
		else if (SP < 0)
			SP = 0.0f;
		AttributeSet->SetSP(SP);
	}
}

void AMyCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (HasAuthority())
	{
		int i = 0;
	}
	else
	{
		int j = 0;
	}

	// Bind player input to the AbilitySystemComponent. Also called in OnRep_PlayerState because of a potential race condition.
	//BindASCInput();
}

//
void AMyCharacterBase::PossessedBy(AController * NewController)
{
	Super::PossessedBy(NewController);

	if (HasAuthority())
	{
		int i = 0;
	}
	else
	{
		int i = 0;
	}

	AMyPlayerState* PS = GetPlayerState<AMyPlayerState>();
	if (PS)
	{
		AbilitySystemComponent = Cast<UMyAbilitySystemComponent>(PS->GetAbilitySystemComponent());
		// AI won't have PlayerControllers so we can init again here just to be sure. No harm in initing twice for heroes that have PlayerControllers.
		PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, this);

		AttributeSet = Cast<UMyAttributeSet>(PS->GetAttributeSet());

		AddStartupGameplayAbilities();
	}
}

void AMyCharacterBase::UnPossessed()
{
}

void AMyCharacterBase::AddStartupGameplayAbilities()
{
	if (!HasAuthority() || !AbilitySystemComponent.IsValid() || AbilitySystemComponent->getAbilitiesHaveGiven())
		return;

	for (TSubclassOf<UMyGameplayAbilityBase>& StartupAbility : GameplayAbilities)
	{
		AbilitySystemComponent->GiveAbility(
			FGameplayAbilitySpec(StartupAbility, 1, INDEX_NONE, this));
	}

	AbilitySystemComponent->setAbilitiesHaveGiven(true);
}

void AMyCharacterBase::RemoveStartupGameplayAbilities()
{
}

void AMyCharacterBase::HandleHealthChanged(float DeltaValue)
{
	if (AbilitySystemComponent.IsValid() && AbilitySystemComponent->getAbilitiesHaveGiven())
	{
		if (!HasAuthority())
		{
			int i = 0;
		}
		OnDamaged(DeltaValue);
	}
	else
	{
		int j = 0;
	}
}

// Client only
void AMyCharacterBase::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	if (HasAuthority())
	{
		int i = 0;
	}
	else
	{
		int i = 0;
	}

	AMyPlayerState* PS = GetPlayerState<AMyPlayerState>();
	if (PS)
	{
		AbilitySystemComponent = Cast<UMyAbilitySystemComponent>(PS->GetAbilitySystemComponent());
		// AI won't have PlayerControllers so we can init again here just to be sure. No harm in initing twice for heroes that have PlayerControllers.
		PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, this);

		AttributeSet = Cast<UMyAttributeSet>(PS->GetAttributeSet());

		// Bind player input to the AbilitySystemComponent. Also called in OnRep_PlayerState because of a potential race condition.
		//BindASCInput();
	}
}

void AMyCharacterBase::HandleSPChanged(float DeltaValue)
{
	if (bAbilitiesInitialized && AttributeSet.IsValid())
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
	if (AttributeSet.IsValid())
	{
		AttributeSet->SetHealth(HP);
	}
}

void AMyCharacterBase::GetActiveAbilitiesWithTags(FGameplayTagContainer AbilityTags, TArray<UMyGameplayAbilityBase*>& ActiveAbilities)
{
	if (AbilitySystemComponent.IsValid())
	{
		AbilitySystemComponent->GetActiveAbilitiesWithTags(AbilityTags, ActiveAbilities);
	}
}

void AMyCharacterBase::SetHP(float Health)
{
	if (AttributeSet.IsValid())
		AttributeSet->SetHealth(Health);
}

void AMyCharacterBase::SetMP(float Mana)
{
	if (AttributeSet.IsValid())
		AttributeSet->SetMana(Mana);
}

void AMyCharacterBase::SetSP(float Stamina)
{
	if (AttributeSet.IsValid())
		AttributeSet->SetSP(Stamina);
}

void AMyCharacterBase::BindASCInput()
{
	if (!ASCInputBound && AbilitySystemComponent.IsValid() && IsValid(InputComponent))
	{
		AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, FGameplayAbilityInputBinds(FString("ConfirmTarget"),
			FString("CancelTarget"), FString("EGDAbilityInputID"), static_cast<int32>(EGDAbilityInputID::Confirm), static_cast<int32>(EGDAbilityInputID::Cancel)));
		ASCInputBound = true;
	}
}
