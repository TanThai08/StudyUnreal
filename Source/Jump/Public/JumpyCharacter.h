// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "JumpyCharacter.generated.h"

UCLASS()
class JUMP_API AJumpyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AJumpyCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "mInput")
	UInputMappingContext* IMCJumpy;

	UPROPERTY(EditAnywhere, Category = "mInput")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = "mInput")
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = "mInput")
	UInputAction* JumpAction;

private:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;
	
	void Move(const FInputActionValue& value);
	void Look(const FInputActionValue& value);
	void JumpFunc(const FInputActionValue& value);
};
