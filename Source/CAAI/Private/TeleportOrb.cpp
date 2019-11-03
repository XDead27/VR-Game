// Fill out your copyright notice in the Description page of Project Settings.


#include "TeleportOrb.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ATeleportOrb::ATeleportOrb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	

	

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Orb Mesh"));
	Mesh->SetSimulatePhysics(true);
	RootComponent = Mesh;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	SphereCollision->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ATeleportOrb::BeginPlay()
{
	Super::BeginPlay();
	
	SphereCollision->OnComponentHit.AddDynamic(this, &ATeleportOrb::Teleport);

}

void ATeleportOrb::Pickup_Implementation(USceneComponent* AttachTo)
{
	if (RootComponent->GetAttachParent() != nullptr) {
		RootComponent->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, false));
	}

	Mesh->SetSimulatePhysics(false);

	RootComponent->AttachToComponent(AttachTo, FAttachmentTransformRules(EAttachmentRule::KeepWorld, false));
}

void ATeleportOrb::Drop_Implementation()
{
	RootComponent->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, false));

	Mesh->SetSimulatePhysics(true);

}

void ATeleportOrb::Teleport(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherComp->GetCollisionObjectType() == ECollisionChannel::ECC_GameTraceChannel1) {
		UE_LOG(LogTemp, Warning, TEXT("%s"), *this->PawnToTeleport->GetName());


		if (this->PawnToTeleport) {
			//PawnToTeleport->SetActorLocation(Hit.Location);
			PawnToTeleport->TeleportTo(Hit.Location, PawnToTeleport->GetActorRotation());
			this->Destroy();
			UE_LOG(LogTemp, Warning, TEXT("Te am teleportat"));
		}
	}
}

// Called every frame
void ATeleportOrb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	

}

