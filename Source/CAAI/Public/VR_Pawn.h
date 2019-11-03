// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "VR_Pawn.generated.h"

UCLASS()
class CAAI_API AVR_Pawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AVR_Pawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	///Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* RootSceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* CameraSceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	///Variables
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AHandController> HandSpawn;

	UPROPERTY(BlueprintReadWrite)
	class AHandController* MotionL;

	UPROPERTY(BlueprintReadWrite)
	class AHandController* MotionR;

	///Functions
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void GrabL();
	void GrabR();
	void DropL();
	void DropR();

};
