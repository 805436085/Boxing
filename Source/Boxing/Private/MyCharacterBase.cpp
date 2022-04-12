// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacterBase.h"
#include "MyPlayerState.h"
#include "Boxing/BoxingGameModeBase.h"
#include "Engine.h"

// Sets default values
AMyCharacterBase::AMyCharacterBase()
	: bAbilitiesInitialized(false)
	, bIsAttacking(false)
	, isDead(false)
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
		AttributeSet->SetHealth(AttributeSet->GetMaxHealth());
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
		FString str = StartupAbility->GetName();
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, str);
		AbilitySystemComponent->GiveAbility(
			FGameplayAbilitySpec(StartupAbility, 1, INDEX_NONE, this));
	}

	AbilitySystemComponent->setAbilitiesHaveGiven(true);
}

void AMyCharacterBase::RemoveStartupGameplayAbilities()
{
	if (!HasAuthority() || !AbilitySystemComponent.IsValid() || !AbilitySystemComponent->getAbilitiesHaveGiven())
		return;

	TArray<FGameplayAbilitySpecHandle> AbilityToRemove;
	for (const FGameplayAbilitySpec& spec : AbilitySystemComponent->GetActivatableAbilities())
	{
		if ((spec.SourceObject == this) && GameplayAbilities.Contains(spec.Ability->GetClass()))
		{
			AbilityToRemove.Add(spec.Handle);
		}
	}

	for (const FGameplayAbilitySpecHandle& handle : AbilityToRemove)
	{
		AbilitySystemComponent->ClearAbility(handle);
	}

	AbilitySystemComponent->setAbilitiesHaveGiven(false);
}

void AMyCharacterBase::HandleHealthChanged(float newHealth)
{
	if (AbilitySystemComponent.IsValid())
	{
		if (!HasAuthority())
		{
			int i = 0;
		}
		else
		{
			int i = 0;
		}
		OnHealthChanged(newHealth);
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
		AttributeSet->SetHealth(AttributeSet->GetMaxHealth());
	}

	OnClientInit();
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
	if (HasAuthority())
	{
		int i = 0;
	}
	else
	{
		int i = 0;
	}

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

float AMyCharacterBase::GetHealth()
{
	if (AttributeSet.IsValid())
	{
		return AttributeSet->GetHealth();
	}

	return 0.0f;
}

float AMyCharacterBase::GetMaxHealth()
{
	if (AttributeSet.IsValid())
	{
		return AttributeSet->GetMaxHealth();
	}

	return 0.0f;
}

bool AMyCharacterBase::isAlive()
{
	if (AttributeSet.IsValid() && AttributeSet->GetHealth() > 0)
	{
			return true;
	}

	return false;
}

void AMyCharacterBase::playHurt()
{
	PlayAnimMontage(HurtMontage);
}

void AMyCharacterBase::Die()
{
	isDead = true;
	RemoveStartupGameplayAbilities();
	playDie();
}

void AMyCharacterBase::playDie()
{
	PlayAnimMontage(DeathMontage);
}

bool AMyCharacterBase::isDie()
{
	return isDead;
}

void AMyCharacterBase::FinishDying()
{
	if (GetLocalRole() == ROLE_Authority)
	{
		ABoxingGameModeBase* GM = Cast<ABoxingGameModeBase>(GetWorld()->GetAuthGameMode());
		ABoxingGameModeBase* GM2 = dynamic_cast<ABoxingGameModeBase*>(GetWorld()->GetAuthGameMode());
		if (GM2)
		{
			int i = 0;
		}
		
		if (GM)
		{
			GM->heroDie(GetController());
		}
	}

	Destroy();
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
