// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPotion.h"

#include "SpartaCharacter.h"

AHealthPotion::AHealthPotion()
{
	ItemName = TEXT("Health Potion");
}

void AHealthPotion::OnPickup(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                             UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnPickup(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	if (ASpartaCharacter* SpartaCharacter = Cast<ASpartaCharacter>(OtherActor))
	{
		SpartaCharacter->RecoveryHealth(RecoveryHealthAmount);
		Destroy();
	}
}
