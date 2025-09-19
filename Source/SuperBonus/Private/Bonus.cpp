// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/Bonus.h"

#include "CatchAi.h"
#include "ThrowAi.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABonus::ABonus()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	RootComponent = BoxCollision;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(BoxCollision);
	ProjectileMovementComponent->InitialSpeed = 200.0f;
	ProjectileMovementComponent->MaxSpeed = 200.0f;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void ABonus::BeginPlay()
{
	Super::BeginPlay();
	this->OnActorBeginOverlap.AddDynamic(this, &ABonus::OnOverlapBegin);

	
}

// Called every frame
void ABonus::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetActorLocation().Z < -420.0f)
	{
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AThrowAi::StaticClass(), FoundActors);
		if (FoundActors.Num() > 0)
		{
			AActor* Actor = FoundActors[0];
			AThrowAi* ThrowAi = Cast<AThrowAi>(Actor);
			ThrowAi->AddNumberOfBonusThrowAndDestroyed();
		}
		Destroy();
	}

}

void ABonus::GoToDirection(const FVector& Direction)
{
	ProjectileMovementComponent->Velocity = Direction * ProjectileMovementComponent->InitialSpeed;
}

void ABonus::OnOverlapBegin(AActor* MyActor, AActor* OtherActor)
{

	if (OtherActor && OtherActor != this)
	{
		ACatchAi* CatchAi = Cast<ACatchAi>(OtherActor);

		if (CatchAi)
		{
			TArray<AActor*> FoundActors;
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), AThrowAi::StaticClass(), FoundActors);
			if (FoundActors.Num() > 0)
			{
				AActor* Actor = FoundActors[0];
				AThrowAi* ThrowAi = Cast<AThrowAi>(Actor);
				ThrowAi->AddNumberOfBonusThrowAndDestroyed();
			}
			CatchAi->AddScore();
			Destroy();
		}
	}
}



