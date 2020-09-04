// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Gameframework/Pawn.h"
#include "TestTurretController.generated.h"

class ATestTurret;
/**
 * 
 */
UCLASS()
class CAAI_API ATestTurretController : public AAIController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	ATestTurret* ControlledTurret;
	FTimerHandle tHandle;
};
