// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CameraPawn.h"
#include "GameFramework/PlayerController.h"
#include "AOV_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class RTS_AOV_API AAOV_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	/*Constructor*/
	AAOV_PlayerController();

protected:
	/*Begin Play*/
	virtual void BeginPlay() override;

public:
	/*Methods*/
	virtual void Tick(float DeltaTime) override;

	virtual void SetupInputComponent();

	virtual void CallMoveForward(float Value);

	virtual void CallMoveRight(float Value);

	virtual void CallIncreaseSpeedModifier();

	virtual void CallDecreaseSpeedModifier();

	virtual void CallPanCameraLeft();

	virtual void CallPanCameraRight();

	virtual void CallPanReset();

	virtual void CallZoomIn();

	virtual void CallZoomOut();

	virtual void CallZoomReset();

	/*Attributes*/

	/*This is a refrence to the Camera Pawn*/
	UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite)
	ACameraPawn* CameraPawnRef;

	/*This is a refrence to the Camera Movement Component */
	UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite)
	UCameraMovement_Component* CameraMovementRef;
};
