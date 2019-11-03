// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HandController.generated.h"


UCLASS()
class CAAI_API AHandController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHandController();
	void Initialize(FName MotionSource);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	///COMPONENTS
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class USceneComponent* Scene;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UMotionControllerComponent* MotionController;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UStaticMeshComponent* HandMesh;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class USphereComponent* GrabCollision;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class USteamVRChaperoneComponent* SteamVRChaperone;

	///VARIABLES
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName Hand;

	///FUNCTIONS
	UFUNCTION(BlueprintCallable)
	AActor* GetGrabbedActor();

	UFUNCTION(BlueprintCallable)
	void Grab();

	UFUNCTION(BlueprintCallable)
	void Drop();

private:
	AActor* GrabbedActor;
};
