// Fill out your copyright notice in the Description page of Project Settings.


#include "TestTurret.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "VR_Pawn.h"
#include "Camera/CameraComponent.h"
#include "Math/UnrealMathUtility.h" 


// Sets default values
ATestTurret::ATestTurret()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("Base Mesh");
	RootComponent = BaseMesh;

	HeadMesh = CreateDefaultSubobject<UStaticMeshComponent>("Head Mesh");
	HeadMesh->SetupAttachment(RootComponent, "HeadSocket");

	HeadMaxSpeed = 2.0f;

}

// Called when the game starts or when spawned
void ATestTurret::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AVR_Pawn* PlayerPawn = Cast<AVR_Pawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	//Rotate Head Towards Player
	if (PlayerPawn) {
		FRotator LookAt = UKismetMathLibrary::FindLookAtRotation(HeadMesh->GetComponentLocation(), PlayerPawn->CameraComponent->GetComponentLocation());
		FRotator Delta;
		Delta.Roll = FMath::Clamp(LookAt.Roll - HeadMesh->GetComponentRotation().Roll, -HeadMaxSpeed, HeadMaxSpeed);
		Delta.Yaw = FMath::Clamp(LookAt.Yaw - HeadMesh->GetComponentRotation().Yaw, -HeadMaxSpeed, HeadMaxSpeed);
		Delta.Pitch = FMath::Clamp(LookAt.Pitch - HeadMesh->GetComponentRotation().Pitch, -HeadMaxSpeed, HeadMaxSpeed);

		HeadMesh->AddRelativeRotation(Delta);

		UE_LOG(LogTemp, Warning, TEXT("LookAt: %f, %f, %f"), LookAt.Roll, LookAt.Yaw, LookAt.Pitch)
		UE_LOG(LogTemp, Warning, TEXT("Delta: %f, %f, %f"), Delta.Roll, Delta.Yaw, Delta.Pitch)
	}
}

// Called to bind functionality to input
void ATestTurret::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

