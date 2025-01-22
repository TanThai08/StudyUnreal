// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpyAnimationBlueprint.h"

void UJumpyAnimationBlueprint::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	jumpyCharacter = Cast<AJumpyCharacter>(TryGetPawnOwner());
	if (jumpyCharacter) 
	{
		JumpycharacterMovement = jumpyCharacter->GetCharacterMovement();
	}
}


void UJumpyAnimationBlueprint::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (JumpycharacterMovement)
	{
		FVector velocityVector = JumpycharacterMovement->Velocity;
		GroundSpeed = UKismetMathLibrary::VSizeXY(velocityVector);

		//calculate LeanAmount
		CurrentFrameRotation = jumpyCharacter->GetActorRotation();
		
		FRotator DeltaRotator = UKismetMathLibrary::NormalizedDeltaRotator(LastFrameRotation, CurrentFrameRotation);

		leanAmount = UKismetMathLibrary::FInterpTo(leanAmount, DeltaRotator.Yaw, DeltaSeconds, 2);
		//UE_LOG(LogTemp, Warning, TEXT("Value lean: %f"), leanAmount);

		LastFrameRotation = jumpyCharacter->GetActorRotation();

		//Calculate Jump
		isInAir = JumpycharacterMovement->IsFalling();

		FVector MovementInputVector = jumpyCharacter->GetLastMovementInputVector();
		double MovementInputValue = UKismetMathLibrary::VSize(MovementInputVector);

		if (MovementInputValue > 0)		
			isInputMovement = true;
		else
			isInputMovement = false;
	}
}

