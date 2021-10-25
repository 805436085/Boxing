// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "MyAttributeSet.generated.h"

// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class BOXING_API UMyAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UMyAttributeSet();

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData &Data);
	
public:
	/** Current Health, when 0 we expect owner to die. Capped by MaxHealth */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Health")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, Health)

	/** MaxHealth is its own attribute, since GameplayEffects may modify it */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Health")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, MaxHealth)

	/** Current Mana, used to execute special abilities. Capped by MaxMana */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MP")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, Mana)

	/** MaxMana is its own attribute, since GameplayEffects may modify it */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MP")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, MaxMana)

	/** Current SP, used to execute special abilities. Capped by MaxSP */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SP")
	FGameplayAttributeData SP;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, SP)

	/** MaxSP is its own attribute, since GameplayEffects may modify it */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SP")
	FGameplayAttributeData MaxSP;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, MaxSP)

	/** AttackPower of the attacker is multiplied by the base Damage to reduce health, so 1.0 means no bonus */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Damage")
	FGameplayAttributeData AttackPower;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, AttackPower)

	/** Base Damage is divided by DefensePower to get actual damage done, so 1.0 means no bonus */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Damage")
	FGameplayAttributeData DefensePower;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, DefensePower)

	/** MoveSpeed affects how fast characters can move */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MoveSpeed")
	FGameplayAttributeData MoveSpeed;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, MoveSpeed)

	/** Damage is a 'temporary' attribute used by the DamageExecution to calculate final damage, which then turns into -Health */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Damage")
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, Damage)
};
