// Fill out your copyright notice in the Description page of Project Settings.


#include "TestTurretController.h"
#include "TestTurret.h"
#include "Engine/World.h"
#include "TimerManager.h"

void ATestTurretController::BeginPlay()
{
	Super::BeginPlay();

	ControlledTurret = Cast<ATestTurret>(GetPawn());

	//GetWorldTimerManager().SetTimer(tHandle, &ATestTurret::Shoot, 5.0f, 1.0f);
}

void ATestTurretController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}