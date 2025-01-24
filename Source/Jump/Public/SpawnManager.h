// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetMathLibrary.h"
#include "Item.h"
#include "SpawnManager.generated.h"

UCLASS()
class JUMP_API ASpawnManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnManager();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	UPROPERTY(EditAnywhere, Category = "Spawn")
	TSubclassOf<AActor> BlueprintToSpawn;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	int32 SizeSpawn = 1;

	void SpawnObject();
	FVector RandomLocation();
};
