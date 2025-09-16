// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "public/Bonus.h"
#include "ThrowAi.generated.h"


UCLASS()
class SUPERBONUS_API AThrowAi : public APawn
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AThrowAi();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* StaticMesh;

	UPROPERTY(Category = Pawn, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UPawnMovementComponent* MovementComponent;

	FVector PreviousVector;
	
	FVector Seek(FVector TargetLocation);

	UPROPERTY(EditDefaultsOnly, Category = Bonus)
	TSubclassOf<class ABonus> Bonus;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void Throw();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bonus)
	FVector MuzzleOffset;
};
