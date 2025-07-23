// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RandomSpawnVolume.generated.h"

class ABaseItem;
class UBoxComponent;

UCLASS()
class HOMEWORK008_API ARandomSpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	ARandomSpawnVolume();

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Components")
	TObjectPtr<UBoxComponent> SpawnBound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	TSubclassOf<ABaseItem> SpawnItem;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	float SpawnDelay = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	int32 StartItemQuantity;

private:
	void SpawnInArea();
	FVector GetRandomLocationInBound() const;

	FTimerHandle SpawnTimer;
};
