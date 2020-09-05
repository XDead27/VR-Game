// Fill out your copyright notice in the Description page of Project Settings.


#include "TestTurret.h"
#include "Components/StaticMeshComponent.h"
#include "DestructibleComponent.h" 
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "VR_Pawn.h"
#include "Bullet.h"
#include "Engine/World.h"
#include "Camera/CameraComponent.h"
#include "Math/UnrealMathUtility.h" 


// Sets default values
ATestTurret::ATestTurret()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("Base Mesh");
	RootComponent = BaseMesh;

	HeadMesh = CreateDefaultSubobject<UDestructibleComponent>("Head Mesh");
	HeadMesh->SetupAttachment(RootComponent, "HeadSocket");

	HeadMaxSpeed = 2.0f;

}

// Called when the game starts or when spawned
void ATestTurret::BeginPlay()
{
	Super::BeginPlay();
	
	HeadMesh->OnComponentFracture.AddDynamic(this, &ATestTurret::SetDead);
}

// Called every frame
void ATestTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AVR_Pawn* PlayerPawn = Cast<AVR_Pawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	//Rotate Head Towards Player
	if (PlayerPawn && !bIsDead) {
		FRotator LookAt = UKismetMathLibrary::FindLookAtRotation(HeadMesh->GetComponentLocation(), PlayerPawn->CameraComponent->GetComponentLocation());

		//Calculate shortest path
		if (LookAt.Roll - HeadMesh->GetComponentRotation().Roll > 180) {
			LookAt.Roll -= 360;
		}
		else if (LookAt.Roll - HeadMesh->GetComponentRotation().Roll < -180) {
			LookAt.Roll += 360;
		}

		if (LookAt.Yaw - HeadMesh->GetComponentRotation().Yaw > 180) {
			LookAt.Yaw -= 360;
		}
		else if (LookAt.Yaw - HeadMesh->GetComponentRotation().Yaw < -180) {
			LookAt.Yaw += 360;
		}

		if (LookAt.Pitch - HeadMesh->GetComponentRotation().Pitch > 180) {
			LookAt.Pitch -= 360;
		}
		else if (LookAt.Pitch - HeadMesh->GetComponentRotation().Pitch < -180) {
			LookAt.Pitch += 360;
		}

		FRotator Delta;
		Delta.Roll = FMath::Clamp(LookAt.Roll - HeadMesh->GetComponentRotation().Roll, -HeadMaxSpeed, HeadMaxSpeed);
		Delta.Yaw = FMath::Clamp(LookAt.Yaw - HeadMesh->GetComponentRotation().Yaw, -HeadMaxSpeed, HeadMaxSpeed);
		Delta.Pitch = FMath::Clamp(LookAt.Pitch - HeadMesh->GetComponentRotation().Pitch, -HeadMaxSpeed, HeadMaxSpeed);

		HeadMesh->AddRelativeRotation(Delta);
	}
}

// Called to bind functionality to input
void ATestTurret::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATestTurret::Shoot()
{
	if (!bIsDead) {
		GetWorld()->SpawnActor<ABullet>(AmmoClass, HeadMesh->GetComponentTransform(), FActorSpawnParameters());
	}
}

void ATestTurret::SetDead(const FVector& HitPoint, const FVector& HitDirection)
{
	this->bIsDead = true;

	UE_LOG(LogTemp, Error, TEXT("Is now dead wtf"))
}

