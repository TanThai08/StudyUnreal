// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "JumpyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "Item.generated.h"

UCLASS()
class JUMP_API AItem : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AItem();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	int32 ScoreItem = 1;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxCollision;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Orb;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Ring;

	UFUNCTION()
	void OnPlayerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere)
	USoundBase* CoinCollectedSound;
 
	UPROPERTY(EditAnyWhere, Category = "Grab Component")
	TSubclassOf<USceneComponent> GrabComponentClass;
	USceneComponent* GrabComponent;
	void SetupGrabComponent(); 
};
