// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/SceneComponent.h"
#include "MotionControllerComponent.h"
#include "Camera/CameraComponent.h"
//#include "XRDeviceVisualizationComponent.h"
#include "PlayerVR.generated.h"

UCLASS()
class JUMP_API APlayerVR : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerVR();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCameraComponent* VRCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UMotionControllerComponent* LeftController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UMotionControllerComponent* RightController;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private: 
	//UPROPERTY(VisibleAnywhere)
	//USceneComponent* Root;

	//UPROPERTY(VisibleAnywhere)
	//UMotionControllerComponent* LeftMotionController; 
	//UPROPERTY(VisibleAnywhere)
	//UMotionControllerComponent* RightMotionController;

	///*UPROPERTY(VisibleAnywhere) 
	//UXRDeviceVisualizationComponent* LeftXRDeviceVisualization;
	//UPROPERTY(VisibleAnywhere)
	//UXRDeviceVisualizationComponent* RightXRDeviceVisualization;*/

	void MoveForward(float Value);
	void MoveRight(float Value);
	void StartTeleport();
	void FinishTeleport();
};
