// Fill out your copyright notice in the Description page of Project Settings.


#include "Fan.h"

// Sets default values
AFan::AFan()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Frame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FanFrame"));
	Fan = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Fan"));
	FanGrating = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FanGrating"));
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	ForceDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Wind = CreateDefaultSubobject<UNiagaraComponent>(TEXT("VisualEffects"));

	Frame->SetupAttachment(GetRootComponent());
	Fan->SetupAttachment(Frame);
	FanGrating->SetupAttachment(Frame);
	Box->SetupAttachment(Frame);
	ForceDirection->SetupAttachment(Box);
	Wind->SetupAttachment(Frame);
}

// Called when the game starts or when spawned
void AFan::BeginPlay()
{
	Super::BeginPlay();
	
	Box->OnComponentBeginOverlap.AddDynamic(this, &AFan::OnPlayerEnter);
	Box->OnComponentEndOverlap.AddDynamic(this, &AFan::OnPlayerExit);

	ACharacter* Character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	Player = Cast<AJumpyCharacter>(Character);
}

void AFan::OnPlayerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AJumpyCharacter* TempPlayer = Cast<AJumpyCharacter>(OtherActor);
	if (TempPlayer)
	{
		GetWorldTimerManager().SetTimer(timerHandle, this, &AFan::ShootPlayer, 0.01, true);
	}
}

void AFan::OnPlayerExit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AJumpyCharacter* TempPlayer = Cast<AJumpyCharacter>(OtherActor);
	if (TempPlayer)
	{
		GetWorldTimerManager().ClearTimer(timerHandle);
	}
}

void AFan::ShootPlayer()
{
	Player->LaunchCharacter(ForceDirection->GetForwardVector() * Power, false, true);
}

// Called every frame
void AFan::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Fan->AddLocalRotation(FRotator(0, 0, 5));
}

