// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypointC.h"
#include "PatrolComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "Classes/AIController.h"
#include "GameFramework/Actor.h"


EBTNodeResult::Type UChooseNextWaypointC::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto AIOwner = OwnerComp.GetAIOwner();
	auto ControlledCharacter = AIOwner->GetPawn();
	if (!ControlledCharacter) { UE_LOG(LogTemp, Warning, TEXT("Invalid character")); return EBTNodeResult::Failed; }

	auto PatrolComp = ControlledCharacter->FindComponentByClass<UPatrolComponent>();
	if (!PatrolComp) { UE_LOG(LogTemp, Warning, TEXT("Patrol comp null")); return EBTNodeResult::Failed; }

	auto PatrolPoints = PatrolComp->PatrolPoints_CPP; 
	if (PatrolPoints.Num() == 0) { UE_LOG(LogTemp, Warning, TEXT("Patrol points empty")); return EBTNodeResult::Failed; }

	auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);

	BlackboardComp->SetValueAsObject(WayPointKey.SelectedKeyName, PatrolPoints[Index]);

	auto NextIndex = ++Index % PatrolPoints.Num();

	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);

	UE_LOG(LogTemp, Warning, TEXT("C++ TASK LOL :%i"), NextIndex);
	return EBTNodeResult::Succeeded;
}
