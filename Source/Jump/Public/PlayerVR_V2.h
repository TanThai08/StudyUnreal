// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MotionControllerComponent.h"
#include "Camera/CameraComponent.h"
//#include "XRDeviceVisualizationComponent.h"
#include "PlayerVR_V2.generated.h"

UCLASS()
class JUMP_API APlayerVR_V2 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerVR_V2();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private: 
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	UMotionControllerComponent* LeftMotionController;
	UPROPERTY(VisibleAnywhere)
	UMotionControllerComponent* RightMotionController;

	/*UPROPERTY(VisibleAnywhere)
	UXRDeviceVisualizationComponent* LeftXRDeviceVisualization;
	UPROPERTY(VisibleAnywhere)
	UXRDeviceVisualizationComponent* RightXRDeviceVisualization;*/

};
