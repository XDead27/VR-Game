// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TestTurret.generated.h"

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
	class UStaticMeshComponent* HeadMesh;

	//UPROPERTY(BlueprintReadOnly, EditAnywhere)
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
