// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbilitySystemInterface.h"
#include "Boxing/Ability/MyAbilitySystemComponent.h"
#include "Boxing/Ability/MyAttributeSet.h"
#include "Boxing/Ability/MyGameplayAbilityBase.h"
#include "GameplayAbilitySpec.h"
#include "MyAbilityActor.generated.h"

UCLASS()
class BOXING_API AMyAbilityActor : public AActor, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyAbilityActor();

	// Implement IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const;

	/** The component used to handle ability system interactions */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UMyAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities)
		FGameplayTag CurrentGameplayTag;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
