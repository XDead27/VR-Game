// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupInterface.h"
#include "TeleportOrb.generated.h"

UCLASS()
class CAAI_API ATeleportOrb : public AActor, public IPickupInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATeleportOrb();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	///COMPONENTS
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class USphereComponent* SphereCollision;


	///FUNCTIONS
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
	void Pickup(USceneComponent* AttachTo);
	virtual void Pickup_Implementation(USceneComponent* AttachTo) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
	void Drop();
	virtual void Drop_Implementation() override;
	
	UFUNCTION()
	void Teleport(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	///VARIABLES
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	class APawn* PawnToTeleport;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
