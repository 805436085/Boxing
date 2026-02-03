// Fill out your copyright notice in the Description page of Project Settings.

#include "BTService_DetectEnemy.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

UBTService_DetectEnemy::UBTService_DetectEnemy()
{
	NodeName = "Detect Enemy";
	
	// Set default interval for detection (every 0.5 seconds)
	Interval = 0.5f;
	RandomDeviation = 0.1f;
	
	// Set default detection range
	DetectionRange = 1000.0f;
	
	// Set default enemy tag
	EnemyTag = FName("Enemy");
}

void UBTService_DetectEnemy::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)
	{
		return;
	}

	APawn* OwnerPawn = AIController->GetPawn();
	if (!OwnerPawn)
	{
		return;
	}

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp)
	{
		return;
	}

	// Get all actors of type Character in the world
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACharacter::StaticClass(), FoundActors);

	AActor* ClosestEnemy = nullptr;
	float ClosestDistance = DetectionRange;

	FVector OwnerLocation = OwnerPawn->GetActorLocation();

	// Find the closest enemy within detection range
	for (AActor* Actor : FoundActors)
	{
		// Skip self
		if (Actor == OwnerPawn)
		{
			continue;
		}

		// Check if actor has the enemy tag
		if (!Actor->ActorHasTag(EnemyTag))
		{
			continue;
		}

		// Calculate distance to potential enemy
		float Distance = FVector::Dist(OwnerLocation, Actor->GetActorLocation());

		// Check if this enemy is closer than the current closest
		if (Distance < ClosestDistance)
		{
			ClosestDistance = Distance;
			ClosestEnemy = Actor;
		}
	}

	// Update the blackboard with the detected enemy (or nullptr if no enemy found)
	BlackboardComp->SetValueAsObject(EnemyActorKey.SelectedKeyName, ClosestEnemy);

	// Optional: Draw debug sphere to visualize detection range in editor
	#if WITH_EDITOR
	if (GEngine && GEngine->bEnableOnScreenDebugMessages)
	{
		DrawDebugSphere(GetWorld(), OwnerLocation, DetectionRange, 16, 
			ClosestEnemy ? FColor::Red : FColor::Green, false, Interval);
	}
	#endif
}
