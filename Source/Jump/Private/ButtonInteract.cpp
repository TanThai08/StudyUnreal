// Fill out your copyright notice in the Description page of Project Settings.


#include "ButtonInteract.h"

// Sets default values
AButtonInteract::AButtonInteract()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseBoard = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Board"));
	Button = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button"));
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));

	BaseBoard->SetupAttachment(GetRootComponent());
	Button->SetupAttachment(BaseBoard);
	BoxCollision->SetupAttachment(Button);
}

// Called when the game starts or when spawned
void AButtonInteract::BeginPlay()
{
	Super::BeginPlay();
	
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AButtonInteract::OnPlayerEnter);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &AButtonInteract::OnPlayerExit);

	Button->SetMaterial(0, materialButtonNormal);
}

void AButtonInteract::OnPlayerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Button->SetMaterial(0, materialButtonInteract);
}

void AButtonInteract::OnPlayerExit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Button->SetMaterial(0, materialButtonNormal);
}

// Called every frame
void AButtonInteract::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

