// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupInterface.h"
#include "BasicBlade.generated.h"

UCLASS()
class CAAI_API ABasicBlade : public AActor, public IPickupInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasicBlade();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* BladeMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UBoxComponent* BoxCollision;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	///FUNCTIONS
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
	void Pickup(USceneComponent* AttachTo);
	virtual void Pickup_Implementation(USceneComponent* AttachTo) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
	void Drop();
	virtual void Drop_Implementation() override;

	UFUNCTION()
	void MountBlade(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	bool bIsInHand = false;
	bool bIsMounted = false;


};
