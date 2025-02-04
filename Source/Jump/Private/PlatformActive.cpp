// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformActive.h"

// Sets default values
APlatformActive::APlatformActive()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collsion"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Object"));

	Mesh->SetupAttachment(GetRootComponent());
	BoxCollision->SetupAttachment(Mesh);
}

// Called when the game starts or when spawned
void APlatformActive::BeginPlay()
{
	Super::BeginPlay();

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &APlatformActive::OnPlayerEnter);
}

void APlatformActive::OnPlayerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{	
	AJumpyCharacter* PlayerTemp = Cast<AJumpyCharacter>(OtherActor);
	
	if (PlayerTemp && !isActive)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cham"));
		Destroy();
	}
}

// Called every frame
void APlatformActive::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

