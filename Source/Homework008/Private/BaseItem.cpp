#include "BaseItem.h"

#include "Components/SphereComponent.h"

ABaseItem::ABaseItem()
{
	PrimaryActorTick.bCanEverTick = false;

	ItemCollision = CreateDefaultSubobject<USphereComponent>(TEXT("ItemCollision"));
	SetRootComponent(ItemCollision);
	ItemCollision->SetCollisionProfileName("OverlapAllDynamic");
	
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	ItemMesh->SetupAttachment(ItemCollision);
	ItemMesh->SetCollisionProfileName("NoCollision");
	
}

void ABaseItem::BeginPlay()
{
	Super::BeginPlay();

	// 오버랩시 발생할 함수 바인딩.
	ItemCollision->OnComponentBeginOverlap.AddDynamic(this,&ThisClass::OnPickup);
	
}

void ABaseItem::OnPickup(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Item Picked Up : %s"), *ItemName.ToString()));
}


