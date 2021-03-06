// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TestTurret.generated.h"

class ABullet;

UCLASS()
class CAAI_API ATestTurret : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATestTurret();

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	float HeadMaxSpeed;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UStaticMeshComponent* BaseMesh;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UDestructibleComponent* HeadMesh;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<ABullet> AmmoClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Shoot();

private:
	bool bIsDead = false;

	UFUNCTION()
	void SetDead(const FVector& HitPoint, const FVector& HitDirection);
};
