// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpyCharacter.h"
#include "EnhancedInputSubsystems.h"

// Sets default values
AJumpyCharacter::AJumpyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create Spring Arm and Set parent
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("MySpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());

	//Create Camera and Set parent
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("MyCamera"));
	Camera->AttachToComponent(SpringArm,FAttachmentTransformRules::KeepRelativeTransform);

	//Setup SpringArm
	SpringArm->TargetArmLength = 500;
	SpringArm->SocketOffset = FVector(0, 0, 120);
	SpringArm->bUsePawnControlRotation = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false; 
	bUseControllerRotationYaw = false;

	//Setup CharacterMovement
	GetCharacterMovement()->MaxWalkSpeed = 500;
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

// Called when the game starts or when spawned
void AJumpyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	//Set Input
	APlayerController* JumpyController = Cast<APlayerController>(GetController());

	if (JumpyController)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(JumpyController->GetLocalPlayer());

		if (Subsystem) 
		{
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(IMCJumpy, 0);
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Hello World"));
}

// Called every frame
void AJumpyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AJumpyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Movement
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if(EnhancedInputComponent) 
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AJumpyCharacter::Move);
	}

}

void AJumpyCharacter::Move(const FInputActionValue& value)
{
	//UE_LOG(LogTemp, Warning, TEXT("Input Move"));
	FVector2D RCVValue = value.Get<FVector2D>();
	UE_LOG(LogTemp, Warning, TEXT("The vector value is: %s"), *RCVValue.ToString());
}


