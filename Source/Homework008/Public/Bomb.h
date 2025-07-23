#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "Bomb.generated.h"

UCLASS()
class HOMEWORK008_API ABomb : public ABaseItem
{
	GENERATED_BODY()
public:
	ABomb();

protected:
	virtual void OnPickup(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USphereComponent> ExplosionBound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Explosion")
	float ExplosionDelay = 3.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Explosion")
	float ExplosionDamage = 30.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Explosion")
	FVector ExplosionLaunchVector = FVector(0.0f, 0.0f, 1000.0f);

private:
	UFUNCTION()
	void Explosion();

	FTimerHandle ExplosionTimer;
	bool bExploded = false;
};
