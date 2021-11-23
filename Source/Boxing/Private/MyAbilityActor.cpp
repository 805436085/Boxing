// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAbilityActor.h"

// Sets default values
AMyAbilityActor::AMyAbilityActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create ability system component, and set it to be explicitly replicated
	AbilitySystemComponent = CreateDefaultSubobject<UMyAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
}

// Called when the game starts or when spawned
void AMyAbilityActor::BeginPlay()
{
	Super::BeginPlay();
	
}

UAbilitySystemComponent * AMyAbilityActor::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

// Called every frame
void AMyAbilityActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

