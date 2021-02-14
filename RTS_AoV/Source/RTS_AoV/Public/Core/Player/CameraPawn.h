// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Pawn.h"
#include "CameraPawn.generated.h"

UCLASS()
class RTS_AOV_API ACameraPawn : public APawn
{
	GENERATED_BODY()

public:
	/* Sets default values for this pawn's properties */
	ACameraPawn();

	/* Called every frame */
	virtual void Tick(float DeltaTime) override;

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

protected:
	/* Called when the game starts or when spawned */
	virtual void BeginPlay() override;

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
	UPROPERTY(BlueprintReadOnly, Category = "Movement Variables: Zoom")
	float DefaultZoomLength;

	/* Default Rotation */
	UPROPERTY(BlueprintReadOnly, Category = "Movement Variables: Zoom")
	FRotator DefaultCameraRotation; 
};
