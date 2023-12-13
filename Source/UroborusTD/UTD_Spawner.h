// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UTD_Spawner.generated.h"


USTRUCT(BlueprintType)
struct FSpawnEntity
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AActor> EntityClass;
	
};

USTRUCT(BlueprintType)
struct FWaveElement
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FSpawnEntity EntityToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 NumberToSpawn;
};

USTRUCT(BlueprintType)
struct FWave
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FWaveElement> AllWaveElements;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWaveReceived);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSpawnDelayEnded);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWaveSent, const FWave&, SentWave);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWaveEnded);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAllWavesEnded);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEntityPicked, const FSpawnEntity&, PickedEntity);


UCLASS()
class UROBORUSTD_API AUTD_Spawner : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintAssignable)
	FOnWaveReceived OnWaveReceived;
	UPROPERTY(BlueprintAssignable)
	FOnSpawnDelayEnded OnSpawnDelayEnded;
	UPROPERTY(BlueprintAssignable)
	FOnWaveSent OnWaveSent;
	UPROPERTY(BlueprintAssignable)
	FOnWaveEnded OnWaveEnded;
	UPROPERTY(BlueprintAssignable)
	FOnAllWavesEnded OnAllWavesEnded;
	
	
	UPROPERTY(BlueprintAssignable)
	FOnEntityPicked OnEntityPicked;
	UPROPERTY(EditAnywhere)
	TArray<FWave> AllWaves;
	UPROPERTY(EditAnywhere)
	TArray<AActor*> AllSpawnedEntities;
	UPROPERTY(EditAnywhere)
	FVector SpawnLocation;
	UPROPERTY(EditAnywhere)
	float SpawnDelay;
	UPROPERTY(EditAnywhere)
	float WaveDelay;	
	UPROPERTY(EditAnywhere)
	bool CanSpawnWave = true;
	UPROPERTY(EditAnywhere)
	int WaveElementIndex = 0;
	UPROPERTY(EditAnywhere)
	int WaveIndex = 0;
	UPROPERTY(EditAnywhere)
	int ElementCount = 0;
	UPROPERTY(EditAnywhere)
	FTimerHandle TimerHandle_WaveStart;
	UPROPERTY(EditAnywhere)
	FTimerHandle TimerHandle_SendWaveContent;
	UPROPERTY(EditAnywhere)
	FTimerHandle TimerHandle_PickEntity;

	
	UPROPERTY(EditAnywhere)
	FWave CurrentWave;
	UPROPERTY(EditAnywhere)
	bool WaveStarted;
	

	//UPROPERTY(EditAnywhere)
	//UPathComponent* Path;
	

public:
	// Sets default values for this actor's properties
	AUTD_Spawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void Init();

	void StartWaveSystem();

	void SendWaveContent();

	void ReceiveWaveContent(const FWave& NewWave);

	void PickEntityToSpawnFromWaveElement();

	void Spawn(TSubclassOf<AActor> EntityToSpawn);

	void CheckCurrentWaveContent();

	void UpdateWaveIndex(int32& WaveIndexRef);

	void SetCanSpawnWave(bool bValue);

	void StopWaveSystem();

private:
	void Spawn(const FSpawnEntity& EntityToSpawn);
	
	
};
