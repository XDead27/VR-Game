// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicBlade.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "HandController.h"

// Sets default values
ABasicBlade::ABasicBlade()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Init Components
	BladeMesh = CreateDefaultSubobject<UStaticMeshComponent>("Blade Mesh");
	RootComponent = BladeMesh;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>("Box Collision");
	BoxCollision->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ABasicBlade::BeginPlay()
{
	Super::BeginPlay();

	BoxCollision->OnComponentHit.AddDynamic(this, &ABasicBlade::MountBlade);
	
}

// Called every frame
void ABasicBlade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasicBlade::Pickup_Implementation(USceneComponent* AttachTo)
{
	if (RootComponent->GetAttachParent() != nullptr) {
		RootComponent->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, false));
	}

	BladeMesh->SetSimulatePhysics(false);

	RootComponent->AttachToComponent(AttachTo, FAttachmentTransformRules(EAttachmentRule::KeepWorld, false));

	bIsInHand = true;
}

void ABasicBlade::Drop_Implementation()
{
	RootComponent->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, false));

	BladeMesh->SetSimulatePhysics(true);

	bIsInHand = false;

}

void ABasicBlade::MountBlade(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	AHandController* OtherHand = Cast<AHandController>(OtherActor);
	if (bIsInHand && OtherHand && OtherActor != GetAttachParentActor()) {
		RootComponent->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, false));
		bIsInHand = false;

		RootComponent->AttachToComponent(OtherHand->HandMesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), "BladeSocket");

	}

}
