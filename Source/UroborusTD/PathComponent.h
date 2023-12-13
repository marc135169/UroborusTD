// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PathComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UROBORUSTD_API UPathComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPathComponent();
	
	UFUNCTION(BlueprintCallable)
	TArray<FVector> GetPathPoints() const;

	UFUNCTION(BlueprintCallable)
	void SetPathPoints(const TArray<FVector>& NewPathPoints);
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Path")
	TArray<FVector> PathPoints;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
