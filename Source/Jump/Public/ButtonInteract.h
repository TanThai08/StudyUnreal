// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Materials/Material.h"
#include "ButtonInteract.generated.h"

UCLASS()
class JUMP_API AButtonInteract : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AButtonInteract();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseBoard;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Button;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxCollision;

	UFUNCTION()
	void OnPlayerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void OnPlayerExit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	FVector ButtonLocationStart;
	UPROPERTY(EditAnywhere) 
	UMaterial* materialButtonNormal;
	UPROPERTY(EditAnywhere)
	UMaterial* materialButtonInteract;
};
