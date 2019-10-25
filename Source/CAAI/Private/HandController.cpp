// Fill out your copyright notice in the Description page of Project Settings.


#include "HandController.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "MotionControllerComponent.h"
#include "PickupInterface.h"

// Sets default values
AHandController::AHandController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	///Component Init
	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = Scene;

	MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("Motion Controller"));
	MotionController->SetupAttachment(RootComponent);
	MotionController->MotionSource = Hand;

	HandMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hand Mesh"));
	HandMesh->SetupAttachment(MotionController);

	GrabCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Grab Sphere"));
	GrabCollision->SetupAttachment(HandMesh);



}

// Called when the game starts or when spawned
void AHandController::BeginPlay()
{
	Super::BeginPlay();

	if (Hand == "Left") {
		HandMesh->SetRelativeScale3D(FVector(1.0, 1.0, -1.0));
	}

	
}

// Called every frame
void AHandController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHandController::Grab()
{
	TSet<AActor*> OverlappingActors;
	GrabCollision->GetOverlappingActors(OverlappingActors);


	AActor* NearestOverlap = nullptr;
	float SmallestDist = 10*GrabCollision->GetScaledSphereRadius();
	for (AActor* a : OverlappingActors) {
		//Check if the actor is pickable
		if (IPickupInterface* HasInterface = Cast<IPickupInterface>(a)) {

			//Get the closest one to the grab sphere
			float distance = FVector::Dist(a->GetActorLocation(), GrabCollision->GetComponentLocation());
			if (distance < SmallestDist) {
				SmallestDist = distance;
				NearestOverlap = a;
			}
		}
	}

	if (NearestOverlap) {
		IPickupInterface* PickupInterface = Cast<IPickupInterface>(NearestOverlap);
		PickupInterface->Execute_Pickup(NearestOverlap, HandMesh);
	}
}

