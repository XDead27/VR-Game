// Fill out your copyright notice in the Description page of Project Settings.


#include "SphereShieldComponent.h"
#include "Public/HandController.h"

// Sets default values for this component's properties
USphereShieldComponent::USphereShieldComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	this->SetGenerateOverlapEvents(true);
	this->SetNotifyRigidBodyCollision(true);

	this->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}


// Called when the game starts
void USphereShieldComponent::BeginPlay()
{
	Super::BeginPlay();

	this->OnComponentBeginOverlap.AddDynamic(this, &USphereShieldComponent::EnteredShield);
	this->OnComponentHit.AddDynamic(this, &USphereShieldComponent::HitShield);
	
}


// Called every frame
void USphereShieldComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USphereShieldComponent::MakeSolid()
{
	this->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
}

void USphereShieldComponent::MakePassthru()
{
	this->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
}

void USphereShieldComponent::EnteredShield(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Error, TEXT("%s entered shield"), *OtherActor->GetName())

	float actorVelocity = 0.0f;

	if (AHandController* handController = Cast<AHandController>(OtherActor)) {
		actorVelocity = handController->GetControllerVelocity();
	}
	else {
		actorVelocity = OtherActor->GetVelocity().Size();
	}

	UE_LOG(LogTemp, Warning, TEXT("Velocity: %f"), actorVelocity)

	if (actorVelocity > maxVelocity) {
		MakeSolid();
		UE_LOG(LogTemp, Warning, TEXT("Shield now solid!"))
	}

}

void USphereShieldComponent::HitShield(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	float actorVelocity = 0.0f;

	if (AHandController* handController = Cast<AHandController>(OtherActor)) {
		actorVelocity = handController->GetControllerVelocity();
	}
	else {
		actorVelocity = OtherActor->GetVelocity().Size();
	}

	if (actorVelocity < maxVelocity) {
		MakePassthru();
	}
}

