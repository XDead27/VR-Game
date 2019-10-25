// Fill out your copyright notice in the Description page of Project Settings.


#include "TeleportOrb.h"

// Sets default values
ATeleportOrb::ATeleportOrb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATeleportOrb::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATeleportOrb::Pickup_Implementation(USceneComponent* AttachTo)
{

}

void ATeleportOrb::Drop_Implementation()
{
}

// Called every frame
void ATeleportOrb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

