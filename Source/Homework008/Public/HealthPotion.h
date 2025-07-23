// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "HealthPotion.generated.h"

/**
 * 
 */
UCLASS()
class HOMEWORK008_API AHealthPotion : public ABaseItem
{
	GENERATED_BODY()
public:
	AHealthPotion();

protected:
	virtual void OnPickup(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health")
	float RecoveryHealthAmount = 30.0f;
};
