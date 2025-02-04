// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	Orb = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Orb"));
	Ring = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ring"));

	BoxCollision->SetupAttachment(GetRootComponent());
	Orb->SetupAttachment(BoxCollision);
	Ring->SetupAttachment(Orb);
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	
	Ring->SetWorldRotation(FRotator(0, 0, UKismetMathLibrary::RandomIntegerInRange(0, 15) * 22));

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnPlayerEnter);
}

void AItem::OnPlayerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AJumpyCharacter* tempPlayer = Cast<AJumpyCharacter>(OtherActor);

	if (tempPlayer)
	{
		tempPlayer->PlayerHUD->IncreaseCoin(ScoreItem);
		UGameplayStatics::PlaySoundAtLocation(this, CoinCollectedSound, GetActorLocation());
		Destroy();
	}
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Ring->AddLocalRotation(FRotator(0, 0, DeltaTime * 100));
	Orb->AddLocalRotation(FRotator(0, DeltaTime * 100, 0));
}

