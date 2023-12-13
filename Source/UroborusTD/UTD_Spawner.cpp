// Fill out your copyright notice in the Description page of Project Settings.


#include "UTD_Spawner.h"
#include "TimerManager.h"
#include "GameFramework/Actor.h"


// Sets default values
AUTD_Spawner::AUTD_Spawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AUTD_Spawner::BeginPlay()
{
	Super::BeginPlay();
	Init();
}
	

// Called every frame
void AUTD_Spawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUTD_Spawner::Init()
{
	SpawnLocation = GetActorLocation();
	if (AllWaves.Num() < 1) return;

	OnWaveSent.AddDynamic(this, &AUTD_Spawner::ReceiveWaveContent);
	OnWaveEnded.AddDynamic(this, &AUTD_Spawner::StartWaveSystem);
	OnAllWavesEnded.AddDynamic(this, &AUTD_Spawner::StopWaveSystem);
	OnEntityPicked.AddDynamic(this, &AUTD_Spawner::Spawn);

	GetWorldTimerManager().SetTimer(TimerHandle_WaveStart, this, &AUTD_Spawner::StartWaveSystem, WaveDelay, false);
}

void AUTD_Spawner::StartWaveSystem()
{
    if (!CanSpawnWave) return;
    UE_LOG(LogTemp, Warning, TEXT("Start Wave System"));
    WaveElementIndex = 0;
    ElementCount = 0;
    GetWorldTimerManager().SetTimer(TimerHandle_SendWaveContent, this, &AUTD_Spawner::SendWaveContent, WaveDelay, false);
}

void AUTD_Spawner::SendWaveContent()
{
    UE_LOG(LogTemp, Warning, TEXT("Send Wave"));
    OnWaveSent.Broadcast(AllWaves[WaveIndex]);
}

void AUTD_Spawner::ReceiveWaveContent(const FWave& NewWave)
{
    CurrentWave = NewWave;
    UE_LOG(LogTemp, Warning, TEXT("Receive Wave"));
    GetWorldTimerManager().SetTimer(TimerHandle_PickEntity, this, &AUTD_Spawner::PickEntityToSpawnFromWaveElement, SpawnDelay, true);
    OnWaveReceived.Broadcast();
}

void AUTD_Spawner::PickEntityToSpawnFromWaveElement()
{
    if (CurrentWave.AllWaveElements.Num() < 1 || WaveElementIndex > CurrentWave.AllWaveElements.Num() - 1)
    {
        GetWorldTimerManager().ClearTimer(TimerHandle_PickEntity);
        return;
    }

    OnSpawnDelayEnded.Broadcast();

    const FWaveElement& Element = CurrentWave.AllWaveElements[WaveElementIndex];
    if (Element.EntityToSpawn.EntityClass == nullptr) return;

    OnEntityPicked.Broadcast(Element.EntityToSpawn);
    ElementCount++;

    if (ElementCount >= Element.NumberToSpawn)
    {
        WaveElementIndex++;
        ElementCount = 0;
    }
}

void AUTD_Spawner::Spawn(const FSpawnEntity& EntityToSpawn)
{
    if (EntityToSpawn.EntityClass == nullptr) return;

    AActor* Spawned = GetWorld()->SpawnActor<AActor>(EntityToSpawn.EntityClass, SpawnLocation, FRotator::ZeroRotator);
    if (Spawned == nullptr) return;

    AllSpawnedEntities.Add(Spawned);
    WaveStarted = true;
}

void AUTD_Spawner::CheckCurrentWaveContent()
{
    if (AllSpawnedEntities.Num() > 0 || !WaveStarted) return;

    AllSpawnedEntities.Empty();
    UpdateWaveIndex(WaveIndex);

    OnWaveEnded.Broadcast();
    WaveStarted = false;
}

void AUTD_Spawner::UpdateWaveIndex(int32& WaveIndexRef)
{
    UE_LOG(LogTemp, Warning, TEXT("Update Wave Index"));
    if (WaveIndexRef + 1 >= AllWaves.Num())
    {
        OnAllWavesEnded.Broadcast();
    }

    WaveIndexRef++;
}

void AUTD_Spawner::SetCanSpawnWave(bool bValue)
{
    CanSpawnWave = bValue;
}

void AUTD_Spawner::StopWaveSystem()
{
    UE_LOG(LogTemp, Warning, TEXT("Stop Wave System"));
    SetCanSpawnWave(false);
    GetWorldTimerManager().ClearTimer(TimerHandle_SendWaveContent);
}


