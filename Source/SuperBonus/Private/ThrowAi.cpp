// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/ThrowAi.h"
#include "Components/BoxComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Public/Bonus.h"

// Sets default values
AThrowAi::AThrowAi()
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
void AThrowAi::BeginPlay()
{
	Super::BeginPlay();
	PreviousVector = FVector(-20.0f, 0.0f, 390.0f);
}

FVector AThrowAi::Seek(FVector TargetLocation)
{
	FVector DesiredLocation = TargetLocation - GetActorLocation();
	DesiredLocation.Normalize();
	DesiredLocation*= MovementComponent->GetMaxSpeed();

	FVector Steering = DesiredLocation - MovementComponent->Velocity;
	Steering = Steering.GetClampedToMaxSize(MovementComponent->GetMaxSpeed());
	return Steering;
}

// Called every frame
void AThrowAi::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector RandomVector = FVector(-20.0f, FMath::RandRange(-600.0f,600.0f) , 390.0f);
	if (PreviousVector.Dist(PreviousVector, GetActorLocation()) < 10.0f)
	{

		MovementComponent->AddInputVector(Seek(FVector((RandomVector))));
		PreviousVector = RandomVector;
		Throw();
	}
	MovementComponent->AddInputVector(Seek(FVector((PreviousVector))));
}

void AThrowAi::Throw()
{

	// Attempt to fire a projectile.
	if (Bonus)
	{

		// Get the camera transform.
		FVector ActorLocation = FVector(GetActorLocation().X , GetActorLocation().Y, GetActorLocation().Z - 30.0f);
		FRotator ActorRotation = FRotator(0.0f, -90.0f, 0.0f);
		;
	 
		//MuzzleOffset.Set(0.0f, 10.0f, 0.0f);
	 
		// Transform MuzzleOffset from camera space to world space.
		FVector MuzzleLocation = ActorLocation; // + FTransform(ActorRotation).TransformVector(MuzzleOffset);;
	        
		// Skew the aim to be slightly upwards.
		FRotator MuzzleRotation = ActorRotation;
	 
		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();
	 
			// Spawn the projectile at the muzzle.
			ABonus* Projectile = World->SpawnActor<ABonus>(Bonus, MuzzleLocation, MuzzleRotation, SpawnParams);
			if (Projectile)
			{
				// Set the projectile's initial trajectory.
				FVector LaunchDirection = MuzzleRotation.Vector();
				
				Projectile->GoToDirection((LaunchDirection));
			}
		}
	}
}

void AThrowAi::AddNumberOfBonusThrowAndDestroyed()
{
	numberOfBonusThrowAndDestroyed ++;
}
