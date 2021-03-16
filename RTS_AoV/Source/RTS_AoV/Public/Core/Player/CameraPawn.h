// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Pawn.h"
#include "CameraPawn.generated.h"

class UCameraMovement_Component;

UCLASS()
class RTS_AOV_API ACameraPawn : public APawn
{
	GENERATED_BODY()

public:
	/* Sets default values for this pawn's properties */
	ACameraPawn();

protected:
	/* Called when the game starts or when spawned */
	virtual void BeginPlay() override;

public:
	/* Camera Movement Component declaration */
	UPROPERTY(Category = "Movement Component", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCameraMovement_Component* PawnMovementComponent;

	/* Called every frame */
	virtual void Tick(float DeltaTime) override;

protected:

	/* Collision sphere and root component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Root Comp")
	class USphereComponent* CollisionSphere;

	/* Player Camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class UCameraComponent* PlayerCamera;

	/* SpringArm or CameraArm */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class USpringArmComponent* CameraArm;

	/* Default Camera Length */
	UPROPERTY(Category = "Movement Variables: Zoom", BlueprintReadOnly)
	float DefaultZoomLength;

	/* Default Rotation */
	UPROPERTY(Category = "Movement Variables: Zoom", BlueprintReadOnly)
	FRotator DefaultCameraRotation;

public:
	// Getters
	/* Return Camera */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Getters")
	FORCEINLINE class UCameraComponent* GetCamera() const { return PlayerCamera; }

	/* Reutrn CameraArm */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Getters")
	FORCEINLINE class USpringArmComponent* GetCameraArm() const { return CameraArm; }

	/* Return length of CameraArm */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Camera Zoom")
	float GetCurrentArmLength();

	/* Return CameraArm rotation */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Camera Zoom")
	FRotator GetCameraRotation();

	//Setters
	UFUNCTION(BlueprintCallable, Category = "Camera Zoom")
	virtual void SetArmLength(float ChangeAmount);

	UFUNCTION(BlueprintCallable, Category = "Camera Zoom")
	virtual void SetArmRotation(FRotator ChangeAmount);

	UFUNCTION(BlueprintCallable, Category = "Camera Zoom")
	virtual void SetToDefaultZoom();
};
