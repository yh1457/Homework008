
#include "Bomb.h"

#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

ABomb::ABomb()
{
	ItemName = "Bomb";
	
	ExplosionBound = CreateDefaultSubobject<USphereComponent>(TEXT("ExplosionBound"));
	ExplosionBound->SetupAttachment(RootComponent);
}

void ABomb::OnPickup(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnPickup(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	if (!bExploded)
	{
		GetWorldTimerManager().SetTimer(ExplosionTimer,this,&ThisClass::Explosion,ExplosionDelay,false);
		bExploded = true;
	}
}

void ABomb::Explosion()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Explosion!")));
	TArray<AActor*> OverlappingActors;
	ExplosionBound->GetOverlappingActors(OverlappingActors);
	for (auto Actor : OverlappingActors)
	{
		UGameplayStatics::ApplyDamage(Actor,ExplosionDamage,nullptr,this,UDamageType::StaticClass());
		if (ACharacter* Character = Cast<ACharacter>(Actor))
		{
			Character->LaunchCharacter(ExplosionLaunchVector,true,true);
		}
		Destroy();
	}
}
