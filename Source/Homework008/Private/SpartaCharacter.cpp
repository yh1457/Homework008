#include "SpartaCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

ASpartaCharacter::ASpartaCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
}

void ASpartaCharacter::IncreaseScore(int32 Value)
{
	if (Value<0) return;
	Score += Value;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Score : %d"), Score));
}

void ASpartaCharacter::RecoveryHealth(float Amount)
{
	SetCurrentHealth(CurrentHealth + Amount);
}

void ASpartaCharacter::BeginPlay()
{
	Super::BeginPlay();

	// 인풋 맵핑
	if (InputMappingContext)
	{
		APlayerController* PC = Cast<APlayerController>(GetController());
		PC->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>()->AddMappingContext(InputMappingContext,0);
	}
	
}

void ASpartaCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	auto EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (MoveAction)
	{
		EnhancedInput->BindAction(MoveAction,ETriggerEvent::Triggered,this,&ThisClass::Move);
	}

	if (LookAction)
	{
		EnhancedInput->BindAction(LookAction,ETriggerEvent::Triggered,this,&ThisClass::Look);
	}

	if (JumpAction)
	{
		EnhancedInput->BindAction(JumpAction,ETriggerEvent::Started,this,&ACharacter::Jump);
		EnhancedInput->BindAction(JumpAction,ETriggerEvent::Completed,this,&ACharacter::StopJumping);
	}

	if (SprintAction)
	{
		EnhancedInput->BindAction(SprintAction,ETriggerEvent::Started,this,&ThisClass::BeginSprint);
		EnhancedInput->BindAction(SprintAction,ETriggerEvent::Completed,this,&ThisClass::EndSprint);
	}
}

float ASpartaCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	class AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	SetCurrentHealth(CurrentHealth - DamageAmount);
	
	return ActualDamage;
}

void ASpartaCharacter::Move(const FInputActionValue& Value)
{
	FVector2D InputVector = Value.Get<FVector2D>();
	if (InputVector.Size()>1.0f)
	{
		InputVector.Normalize();
	}

	FRotator ControlRotation = GetControlRotation();
	ControlRotation.Pitch = 0.0f;
	ControlRotation.Roll = 0.0f;
	
	FVector ForwardVector = FRotationMatrix(ControlRotation).GetUnitAxis(EAxis::X);
	FVector RightVector = FRotationMatrix(ControlRotation).GetUnitAxis(EAxis::Y);
	FVector MovVector = RightVector*InputVector.X + ForwardVector*InputVector.Y;

	AddMovementInput(MovVector);
	
}

void ASpartaCharacter::Look(const FInputActionValue& Value)
{
	FVector2D InputVector = Value.Get<FVector2D>();
	AddControllerYawInput(InputVector.X);
	AddControllerPitchInput(InputVector.Y);
}

void ASpartaCharacter::BeginSprint(const FInputActionValue& Value)
{
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

void ASpartaCharacter::EndSprint(const FInputActionValue& Value)
{
	GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
}

void ASpartaCharacter::RestartCurrentLevel()
{
	auto CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this);
	UGameplayStatics::OpenLevel(this, FName(CurrentLevelName));
}

void ASpartaCharacter::SetCurrentHealth(float NewValue)
{
	if (NewValue<=0.0f)
	{
		GetWorldTimerManager().SetTimer(RestartTimer,this,&ThisClass::RestartCurrentLevel,RestartDelay,false);
	}
	
	CurrentHealth = FMath::Clamp(NewValue, 0.0f, MaxHealth);
}

