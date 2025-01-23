// Fill out your copyright notice in the Description page of Project Settings.


#include "Elevator.h"

// Sets default values
AElevator::AElevator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ElevatorMesh"));
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));

	Root->SetupAttachment(GetRootComponent());
	Mesh->SetupAttachment(Root);
	Box->SetupAttachment(Mesh);
}

// Called when the game starts or when spawned
void AElevator::BeginPlay()
{
	Super::BeginPlay();

	//Câu lệnh này khá giống Invoke bên unity
	GetWorldTimerManager().SetTimer(TimerForStayingDown, this, &AElevator::SetGoToEndLocation, TimeToStayDown, false);
	
	Box->OnComponentBeginOverlap.AddDynamic(this, &AElevator::OnBeginElevatorOverlap);
	Box->OnComponentEndOverlap.AddDynamic(this, &AElevator::OnEndElevatorOverlap);
}

void AElevator::SetGoToEndLocation()
{
	GoToEndLocation = true;
	GoToStartLocation = false;
}

void AElevator::SetGoToStartLocation()
{
	GoToEndLocation = false;
	GoToStartLocation = true;
}

void AElevator::OnBeginElevatorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AJumpyCharacter* PLayer = Cast<AJumpyCharacter>(OtherActor);

	if (PLayer)
	{
		isPlayerOut = false;
		GetWorldTimerManager().SetTimer(TimerForStayUp, this, &AElevator::SetGoToStartLocation, TimeToStayUp, false);
	}	
}

void AElevator::OnEndElevatorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AJumpyCharacter* PLayer = Cast<AJumpyCharacter>(OtherActor);

	if (PLayer)
	{
		isPlayerOut = true;
		GetWorldTimerManager().SetTimer(TimerForStayingDown, this, &AElevator::SetGoToEndLocation, TimeToStayDown, false);
	}
}

// Called every frame
void AElevator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GoToEndLocation)
	{
		if (isPlayerOut)
		{
			FVector TempLocation = UKismetMathLibrary::VInterpTo(Mesh->GetRelativeLocation(), EndLocation, DeltaTime, 2);
			Mesh->SetRelativeLocation(TempLocation);

			double Distance = UKismetMathLibrary::Vector_Distance(TempLocation, EndLocation);
			if (Distance < 20)
			{
				GoToEndLocation = false;
			}

		}		
	}

	if (GoToStartLocation)
	{
		FVector TempLocation = UKismetMathLibrary::VInterpTo(Mesh->GetRelativeLocation(), StartLocation, DeltaTime, 2);
		Mesh->SetRelativeLocation(TempLocation);

		double Distance = UKismetMathLibrary::Vector_Distance(TempLocation, StartLocation);
		if (Distance < 20)
		{
			GoToStartLocation = false;
		}
	}
}

