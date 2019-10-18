// Fill out your copyright notice in the Description page of Project Settings.


#include "VR_Pawn.h"
#include "HeadMountedDisplay.h"
#include "MotionControllerComponent.h"
#include "IMotionController.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AVR_Pawn::AVR_Pawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	///Component Init
	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Scene Component"));
	RootComponent = RootSceneComponent;

	CameraSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Camera Component"));
	CameraSceneComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(CameraSceneComponent);

	LeftMotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("Left Motion Controller"));
	LeftMotionController->SetupAttachment(RootComponent);
	LeftMotionController->MotionSource = "Left";

	RightMotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("Right Motion Controller"));
	RightMotionController->SetupAttachment(RootComponent);
	RightMotionController->MotionSource = "Right";

	


	///VariableInit
	BaseEyeHeight = 0.0;
}

// Called when the game starts or when spawned
void AVR_Pawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVR_Pawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AVR_Pawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

