// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstanceBase.generated.h"

/**
 * 
 */
class AMyCharacterBase;
UCLASS()
class BOXING_API UMyAnimInstanceBase : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UMyAnimInstanceBase();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Native")
		float NativeSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Native")
		float NativeDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Native")
		bool IsDead;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Native")
		AMyCharacterBase* TPCharacter;
};
