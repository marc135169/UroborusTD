// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "AIController.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UTD_ParentEnemy.generated.h"

class AWaypoint;
UCLASS()
class UROBORUSTD_API AUTD_ParentEnemy : public ACharacter
{
	GENERATED_BODY()	
	UPROPERTY(EditAnywhere)
	int health;
	UPROPERTY(EditAnywhere)
	float moveSpeed;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<AWaypoint> target = nullptr;
	UPROPERTY(EditAnywhere)
	TArray<AWaypoint*> waypoints;

	UPROPERTY(EditAnywhere)
	FAIMoveRequest moveRequest;
	UPROPERTY(EditAnywhere)
	TObjectPtr<AAIController> controllerRef;
	
public:
	// Sets default values for this character's properties
	AUTD_ParentEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void FindAndStoreWaypoints();
	void MoveToFirstWaypoint();
	void Init();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
