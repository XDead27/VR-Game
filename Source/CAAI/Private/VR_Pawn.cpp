// Fill out your copyright notice in the Description page of Project Settings.


#include "VR_Pawn.h"
#include "HeadMountedDisplay.h"
#include "MotionControllerComponent.h"
#include "IMotionController.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "HandController.h"
#include "Kismet/GameplayStatics.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "GameFramework/WorldSettings.h"

// Sets default values
AVR_Pawn::AVR_Pawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	///Component Init
	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	RootComponent = RootSceneComponent;

	CameraSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("VR Origin"));
	CameraSceneComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("HeadCamera"));
	CameraComponent->SetupAttachment(CameraSceneComponent);


	///Variable Init
	BaseEyeHeight = 0.0;
}

// Called when the game starts or when spawned
void AVR_Pawn::BeginPlay()
{
	Super::BeginPlay();

	
	//Spawn Motion Controllers With Deffer
	
	MotionL = Cast<AHandController>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, HandSpawn, RootComponent->GetComponentTransform(), ESpawnActorCollisionHandlingMethod::Undefined, this));
	if (MotionL) {
		MotionL->Initialize("Left");

		UGameplayStatics::FinishSpawningActor(MotionL, RootComponent->GetComponentTransform());

		MotionL->AttachToComponent(RootSceneComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	}

	MotionR = Cast<AHandController>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, HandSpawn, RootComponent->GetComponentTransform(), ESpawnActorCollisionHandlingMethod::Undefined, this));
	if (MotionR) {
		MotionR->Initialize("Right");

		UGameplayStatics::FinishSpawningActor(MotionR, RootComponent->GetComponentTransform());

		MotionR->AttachToComponent(RootSceneComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	}


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

	InputComponent->BindAction("GrabL", IE_Pressed, this, &AVR_Pawn::GrabL);
	InputComponent->BindAction("GrabR", IE_Pressed, this, &AVR_Pawn::GrabR);
	InputComponent->BindAction("GrabL", IE_Released, this, &AVR_Pawn::DropL);
	InputComponent->BindAction("GrabR", IE_Released, this, &AVR_Pawn::DropR);
	InputComponent->BindAction("UseL", IE_Pressed, this, &AVR_Pawn::UseL);
	InputComponent->BindAction("UseL", IE_Released, this, &AVR_Pawn::StopUsingL);
}

void AVR_Pawn::GrabL()
{
	MotionL->Grab();
}

void AVR_Pawn::GrabR()
{
	MotionR->Grab();
}

void AVR_Pawn::DropL()
{
	MotionL->Drop();
}

void AVR_Pawn::DropR()
{
	MotionR->Drop();
}

void AVR_Pawn::UseL()
{
	GetWorld()->GetWorldSettings()->SetTimeDilation(DilationScale);
}

void AVR_Pawn::StopUsingL()
{
	GetWorld()->GetWorldSettings()->SetTimeDilation(1.0f);
}

void AVR_Pawn::UseR()
{
}


