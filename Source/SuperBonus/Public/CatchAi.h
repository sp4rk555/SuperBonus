// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CatchAi.generated.h"

UCLASS()
class SUPERBONUS_API ACatchAi : public APawn
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACatchAi();

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* StaticMesh;

	UPROPERTY(Category = Pawn, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UPawnMovementComponent* MovementComponent;
	
	FVector Seek(FVector TargetLocation);

	AActor* NextBonus;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float Score = 0;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AddScore();

};
