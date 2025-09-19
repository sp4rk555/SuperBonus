// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/CatchAi.h"

#include "Bonus.h"
#include "Components/BoxComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACatchAi::ACatchAi()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	RootComponent = BoxCollision;

	MovementComponent = CreateDefaultSubobject<UPawnMovementComponent, UFloatingPawnMovement>(TEXT("MovementComponent"));
	MovementComponent->UpdatedComponent = BoxCollision;
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ACatchAi::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABonus::StaticClass(), FoundActors);
	if (FoundActors.Num() > 0)
	{
		NextBonus = FoundActors[0];
	}
}

FVector ACatchAi::Seek(FVector TargetLocation)
{
	FVector DesiredLocation = TargetLocation - GetActorLocation();
	DesiredLocation.Normalize();
	DesiredLocation*= MovementComponent->GetMaxSpeed();

	FVector Steering = DesiredLocation - MovementComponent->Velocity;
	Steering = Steering.GetClampedToMaxSize(MovementComponent->GetMaxSpeed());
	return Steering;
}

// Called every frame
void ACatchAi::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABonus::StaticClass(), FoundActors);
	if (FoundActors.Num() > 0)
	{
		NextBonus = FoundActors[0];
	}
	if (NextBonus)
	{
		MovementComponent->AddInputVector(Seek(FVector(GetActorLocation().X,NextBonus->GetActorLocation().Y,GetActorLocation().Z)));
	}
}

void ACatchAi::AddScore()
{
	Score ++;
}


