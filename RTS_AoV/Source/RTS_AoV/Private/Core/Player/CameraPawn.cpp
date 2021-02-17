// Fill out your copyright notice in the Description page of Project Settings.


#include "/Robocze_ProjektyGier/GAME-RTS_AgeOfVikings-UE4-Cpp/RTS_AoV/Source/RTS_AoV/Public/Core/Player/CameraPawn.h"
#include "CoreMinimal.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SphereComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"

// Sets default values
ACameraPawn::ACameraPawn()
{
	// Set Defaults
	DefaultZoomLength = 1350.0f;
	DefaultCameraRotation = FRotator(-75.0, 0.0, 0.0);

	// Set Root Component and also set root component size.
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	SetRootComponent(CollisionSphere);
	CollisionSphere->InitSphereRadius(32.0);
	CollisionSphere->SetWorldScale3D(FVector(0.25, 0.25, 0.25));
	
	// The collision profile name - used for map boundries.

	// Default settings for inheriting controller rotations.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create CameraArm and attach to root.
	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	CameraArm->SetupAttachment(RootComponent);
	CameraArm->SetUsingAbsoluteRotation(false);  // Rotate arm (and camera) when pawn rotates
	CameraArm->TargetArmLength = DefaultZoomLength;
	CameraArm->SetRelativeRotation(DefaultCameraRotation);
	CameraArm->bDoCollisionTest = false; // Do not do collision test for camera arm
	CameraArm->bEnableCameraLag = true; // Smoother Movements
	CameraArm->bEnableCameraRotationLag = false;
	CameraArm->bInheritPitch = false; // False - For zoom to update in real time.

	// Create Camera
	PlayerCamera = CreateAbstractDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(CameraArm, USpringArmComponent::SocketName);

 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

// Called when the game starts or when spawned
void ACameraPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ACameraPawn::GetCurrentArmLength()
{
	return CameraArm->TargetArmLength;
}
FRotator ACameraPawn::GetCameraRotation()
{
	return CameraArm->GetRelativeRotation();
}
void ACameraPawn::SetArmLength(float ChangeAmount)
{
	CameraArm->TargetArmLength += ChangeAmount;
}
void ACameraPawn::SetArmRotation(FRotator ChangeAmount)
{
	/* Setting our min and max rotation amounts */
	/* How close to the ground camera gone get*/ 
	const FRotator RotationMax = FRotator(-25.0, 0.0, 0.0); //Zoom in rotation max
	const FRotator RotationMin = DefaultCameraRotation; // Zoom out rotation min

	// Get 'x', the rotation change
	FRotator NewRotation = FRotator(CameraArm->GetRelativeRotation() + ChangeAmount);

	// Clamp the pitch of NewRotation
	NewRotation = NewRotation.Pitch < RotationMin.Pitch ? RotationMin : NewRotation.Pitch < RotationMax.Pitch ? NewRotation : RotationMax;

	CameraArm->SetRelativeRotation(NewRotation); // CameraArm->RelativeRotation
}
void ACameraPawn::SetToDefaultZoom()
{
	CameraArm->TargetArmLength = DefaultZoomLength;
	CameraArm->SetRelativeRotation(DefaultCameraRotation);
}