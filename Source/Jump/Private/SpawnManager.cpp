// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnManager.h"

// Sets default values
ASpawnManager::ASpawnManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawnManager::BeginPlay()
{
	Super::BeginPlay();

	SpawnObject();
	
}

void ASpawnManager::SpawnObject()
{
	for (size_t i = 0; i < SizeSpawn; i++)
	{
		// Create Items
		//FVector tempLocation = RandomLocation();

		//location spawn
		FVector tempLocation = FVector(GetActorLocation().X, GetActorLocation().Y, 50);
		int32 Row = i / 10;
		int32 Colum = i % 10;
		tempLocation.X += Row * 250;
		tempLocation.Y += Colum * 250;

		FRotator tempRotation = FRotator::ZeroRotator;
		AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(BlueprintToSpawn, tempLocation, tempRotation);

		//Set value
		AItem* item = Cast<AItem>(SpawnedActor); 
		item->ScoreItem = i + 1;
	}	
}

FVector ASpawnManager::RandomLocation()
{

	return FVector(UKismetMathLibrary::RandomFloatInRange(-1000, 1000),UKismetMathLibrary::RandomFloatInRange(-1000, 1000), 30);
}

// Called every frame
void ASpawnManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

