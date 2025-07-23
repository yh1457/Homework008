// Fill out your copyright notice in the Description page of Project Settings.


#include "Coin.h"

#include "SpartaCharacter.h"
#include "GameFramework/RotatingMovementComponent.h"

ACoin::ACoin()
{
	RotatingMovement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovement"));
	
}

void ACoin::OnPickup(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                     int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnPickup(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	if (ASpartaCharacter* SpartaCharacter = Cast<ASpartaCharacter>(OtherActor))
	{
		SpartaCharacter->IncreaseScore(PointValue);
		Destroy();
	}
}
