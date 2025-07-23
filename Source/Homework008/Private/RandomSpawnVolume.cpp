// Fill out your copyright notice in the Description page of Project Settings.


#include "RandomSpawnVolume.h"

#include "BaseItem.h"
#include "Components/BoxComponent.h"

ARandomSpawnVolume::ARandomSpawnVolume()
{
	PrimaryActorTick.bCanEverTick = true;

	SpawnBound = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnBound"));
	SetRootComponent(SpawnBound);
}

void ARandomSpawnVolume::BeginPlay()
{
	Super::BeginPlay();

	if (!SpawnItem) return;

	for (int32 i=0;i<StartItemQuantity;i++)
	{
		SpawnInArea();
	}
	
	GetWorldTimerManager().SetTimer(SpawnTimer,this,&ThisClass::SpawnInArea,SpawnDelay,false);
}

void ARandomSpawnVolume::SpawnInArea()
{
	GetWorld()->SpawnActor<AActor>(SpawnItem,GetRandomLocationInBound(),FRotator::ZeroRotator);
}

FVector ARandomSpawnVolume::GetRandomLocationInBound() const
{
	FVector CenterLocation = GetActorLocation();
	FVector RandomOffset = FVector(
		FMath::RandRange(-SpawnBound->GetScaledBoxExtent().X, SpawnBound->GetScaledBoxExtent().X),
		FMath::RandRange(-SpawnBound->GetScaledBoxExtent().Y, SpawnBound->GetScaledBoxExtent().Y),
		FMath::RandRange(-SpawnBound->GetScaledBoxExtent().Z, SpawnBound->GetScaledBoxExtent().Z)
	);
	
	return CenterLocation + RandomOffset;
}
