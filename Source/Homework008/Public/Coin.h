// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "Coin.generated.h"

class URotatingMovementComponent;

UCLASS()
class HOMEWORK008_API ACoin : public ABaseItem
{
	GENERATED_BODY()

public:
	ACoin();

protected:
	virtual void OnPickup(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<URotatingMovementComponent> RotatingMovement;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")	
	int32 PointValue = 5;
	
};
