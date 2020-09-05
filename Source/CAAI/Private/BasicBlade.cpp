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

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ABasicBlade::MountBlade);
	
}

// Called every frame
void ABasicBlade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasicBlade::Pickup_Implementation(USceneComponent* AttachTo)
{
	if (AttachTo->GetAttachmentRoot() != RootComponent->GetAttachParent()->GetAttachmentRoot()) {
		
		UE_LOG(LogTemp, Warning, TEXT("Atasez de %s"), *AttachTo->GetName())

		if (RootComponent->GetAttachParent() != nullptr) {
			RootComponent->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, false));
			UE_LOG(LogTemp, Warning, TEXT("%s is different from %s"), *RootComponent->GetAttachParent()->GetAttachmentRoot()->GetName(), *AttachTo->GetAttachmentRoot()->GetName())
		}
		BladeMesh->SetSimulatePhysics(false);

		RootComponent->AttachToComponent(AttachTo, FAttachmentTransformRules(EAttachmentRule::KeepWorld, false));

		bIsInHand = true;
		bIsMounted = false;
	}
	
}

void ABasicBlade::Drop_Implementation()
{
	if (!bIsMounted) {
		RootComponent->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, false));

		BladeMesh->SetSimulatePhysics(true);

		bIsInHand = false;
		bIsMounted = false;
	}

}

void ABasicBlade::MountBlade(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AHandController* OtherHand = Cast<AHandController>(OtherActor);

	if (bIsInHand && OtherHand != nullptr && OtherActor != GetAttachParentActor()) {
		RootComponent->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, false));
		bIsInHand = false;
		bIsMounted = true;

		RootComponent->AttachToComponent(OtherHand->HandMesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), "BladeSocket");

	}

}
