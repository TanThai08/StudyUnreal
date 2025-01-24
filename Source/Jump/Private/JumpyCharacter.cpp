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
		PlayerHUD = CreateWidget<UJumpyUI>(JumpyController, widgetSubcllass);
		PlayerHUD->AddToViewport();
		PlayerHUD->SetCoin(0);

		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(JumpyController->GetLocalPlayer());

		if (Subsystem) 
		{
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(IMCJumpy, 0);
		}
	}
}

// Called every frame
void AJumpyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerHUD)
	{
		PlayerHUD->SetHeight(GetActorLocation().Z);
	}
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
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AJumpyCharacter::Look);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AJumpyCharacter::Jump);
	}

}

void AJumpyCharacter::Move(const FInputActionValue& value)
{
	FVector2D RCVValue = value.Get<FVector2D>();
	//UE_LOG(LogTemp, Warning, TEXT("The vector value is: %s"), *RCVValue.ToString());

	FRotator ControlRotation = GetControlRotation();

	FVector ForwardVector = FRotationMatrix(FRotator(0,ControlRotation.Yaw,0)).GetUnitAxis(EAxis::X);
	FVector RightVector = FRotationMatrix(FRotator(0, ControlRotation.Yaw, ControlRotation.Roll)).GetUnitAxis(EAxis::Y);
	
	AddMovementInput(ForwardVector, RCVValue.Y);
	AddMovementInput(RightVector, RCVValue.X);
}

void AJumpyCharacter::Look(const FInputActionValue& value)
{
	FVector2D RCVValue = value.Get<FVector2D>();
	//UE_LOG(LogTemp, Warning, TEXT("The vector value is: %s"), *RCVValue.ToString());

	AddControllerPitchInput(RCVValue.Y);
	AddControllerYawInput(RCVValue.X);
}

void AJumpyCharacter::JumpFunc(const FInputActionValue& value)
{
	Jump();
}


