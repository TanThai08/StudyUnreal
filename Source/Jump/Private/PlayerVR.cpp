// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerVR.h"

// Sets default values
APlayerVR::APlayerVR()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // Tạo camera VR
    VRCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("VRCamera"));
    VRCamera->SetupAttachment(RootComponent);

    // Tạo tay trái
    LeftController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("LeftController"));
    LeftController->SetupAttachment(RootComponent);
    LeftController->SetTrackingSource(EControllerHand::Left);

    // Tạo tay phải
    RightController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("RightController"));
    RightController->SetupAttachment(RootComponent);
    RightController->SetTrackingSource(EControllerHand::Right);
}

// Called when the game starts or when spawned
void APlayerVR::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayerVR::MoveForward(float Value)
{
    AddMovementInput(GetActorForwardVector(), Value);
}

void APlayerVR::MoveRight(float Value)
{
    AddMovementInput(GetActorRightVector(), Value);
}

void APlayerVR::StartTeleport()
{
}

void APlayerVR::FinishTeleport()
{
}

// Called every frame
void APlayerVR::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerVR::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &APlayerVR::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &APlayerVR::MoveRight);
}

