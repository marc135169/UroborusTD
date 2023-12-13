// Fill out your copyright notice in the Description page of Project Settings.


#include "UTD_ParentEnemy.h"
#include "Waypoint.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"
#include "Navigation/PathFollowingComponent.h"

// Sets default values
AUTD_ParentEnemy::AUTD_ParentEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUTD_ParentEnemy::BeginPlay()
{
	Super::BeginPlay();
	Init();
}


// Called every frame
void AUTD_ParentEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveToFirstWaypoint();
}

// Called to bind functionality to input
void AUTD_ParentEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AUTD_ParentEnemy::Init()
{
	controllerRef = Cast<AAIController>(GetController());
	FindAndStoreWaypoints();
}

void AUTD_ParentEnemy::FindAndStoreWaypoints()
{
	TArray<AActor*> _foundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWaypoint::StaticClass(), _foundActors);

	for (AActor* Actor : _foundActors)
	{
		AWaypoint* _itemFound = Cast<AWaypoint>(Actor);
		if(_itemFound)
		{
			waypoints.Add(_itemFound);
		}
	}	
}

void AUTD_ParentEnemy::MoveToFirstWaypoint()
{
	target = waypoints[0];
	FVector _dest = target->GetActorLocation();
	
	moveRequest.SetGoalActor(target);
	controllerRef->MoveTo(moveRequest);
}

