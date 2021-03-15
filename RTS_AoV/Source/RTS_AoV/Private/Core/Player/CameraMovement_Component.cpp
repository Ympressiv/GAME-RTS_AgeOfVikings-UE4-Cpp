// Fill out your copyright notice in the Description page of Project Settings.

#include "/Robocze_ProjektyGier/GAME-RTS_AgeOfVikings-UE4-Cpp/RTS_AoV/Source/RTS_AoV/Public/Core/Player/CameraMovement_Component.h"
#include "/Robocze_ProjektyGier/GAME-RTS_AgeOfVikings-UE4-Cpp/RTS_AoV/Source/RTS_AoV/Public/Core/Player/CameraPawn.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"

// Sets default values for this component's properties
UCameraMovement_Component::UCameraMovement_Component()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;

	// Set Default attributes
	bDisableCameraMovement = false;
	DefaultMovementSpeed = 15.0;
	MovementSpeedModifier = 1.0;
	DefaultZoomLength = 1350.0;
	DeltaArm = 150.0;
	DeltaRotation = FRotator(7.15, 0.0, 0.0);
	MaxZoom = 300.0; // The closest the camera can get from the map
	MinZoom = 3000.0; // The farthest the camera can get from the map
}

// Called when the game starts
void UCameraMovement_Component::BeginPlay()
{
	Super::BeginPlay();
	CameraOwner = Cast<ACameraPawn>(GetOwner()); // Populates the owner of this component
	PlayerControllerRef = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)); // Populates PlayerControllerRef
}

// Called every frame
void UCameraMovement_Component::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

//Methods
//Getters
FVector UCameraMovement_Component::GetCameraLocation()
{
	return CameraOwner->GetActorLocation();
}
FVector UCameraMovement_Component::GetFaceDirection()
{
	return CameraOwner->GetActorForwardVector();
}
FRotator UCameraMovement_Component::GetCameraRotation()
{
	return CameraOwner->GetActorRotation();
}

//Setters
float UCameraMovement_Component::SetMovementSpeedModifier(float ModifierAmount)
{
	return MovementSpeedModifier = ModifierAmount;
}
float UCameraMovement_Component::SetMovementSpeed(float MovementSpeedAdjustment)
{
	return DefaultMovementSpeed = MovementSpeedAdjustment;
}
bool UCameraMovement_Component::SetCameraDisable(bool bDisableCamera)
{
	return bDisableCameraMovement = bDisableCamera;
}

//Basic Movement Controlls
/*Movement Control - W A S D*/
void UCameraMovement_Component::BasicMovementControl(float AxisValueX, float AxisValueY)
{
	// Set Variables used in movement calculation
	float MovementValueX;
	float MovementValueY;
	FVector MovementX;
	FVector MovementY;

	if (!IsCameraDisable())
	{
		if (AxisValueX != 0 && AxisValueY != 0)
		{
			MovementValueX = AxisValueX * GetCurrentMovementSpeed() * GetSpeedModifier();
			MovementX = FVector(MovementValueX, 0, 0);

			MovementValueY = AxisValueY * GetCurrentMovementSpeed() * GetSpeedModifier();
			MovementY = FVector(0, MovementValueY, 0);

			CameraOwner->AddActorLocalOffset(MovementX + MovementY, true);
		}
		else if (AxisValueX != 0)
		{
			MovementValueX = AxisValueX * GetCurrentMovementSpeed() * GetSpeedModifier();
			MovementX = FVector(MovementValueX, 0, 0);

			CameraOwner->AddActorLocalOffset(MovementX, true);
		}
		else if (AxisValueY != 0)
		{
			MovementValueY = AxisValueY * GetCurrentMovementSpeed() * GetSpeedModifier();
			MovementY = FVector(0, MovementValueY, 0);

			CameraOwner->AddActorLocalOffset(MovementY, true);
		}
	}
}
/*Camera Pan*/
void UCameraMovement_Component::PanCamera(float RotationAmount)
{
	FRotator NewRotation = GetCameraRotation().Add(0, RotationAmount, 0);
	CameraOwner->SetActorRotation(NewRotation);
}
/*Resets Camera Pan/Rotation*/
void UCameraMovement_Component::ResetPan()
{
	CameraOwner->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
}
/*Edge Scroll - X and Y are reveresed on screen from the game world*/
void UCameraMovement_Component::EdgeScroll()
{
	//Variables for movement
	float DeltaSpeedX;
	float DeltaSpeedY;
	FVector MovementX; // Use with DeltaSpeedY
	FVector MovementY; // Use with DeltaSpeedX

	//Get Mouse Position
	float MousePositionX{ 0 };
	float MousePositionY{ 0 };
	PlayerControllerRef->GetMousePosition(MousePositionX, MousePositionY);

	//Get Viewport (play screen) size
	int32 ViewportSizeX;
	int32 ViewportSizeY;
	PlayerControllerRef->GetViewportSize(ViewportSizeX, ViewportSizeY);

	//Calculate proportions (we want these calculation to be updated with the mouses movement)
	float ProportionX = MousePositionX / ViewportSizeX;
	float ProportionY = MousePositionY / ViewportSizeY;

	// Set EdgeScrollSpeeds based on Proportion
	if (ProportionX >= .975 && ProportionY <= .025) //Top right corner)
	{
		DeltaSpeedX = 7.07 * GetSpeedModifier();
		DeltaSpeedY = 7.07;

		MovementX = FVector(DeltaSpeedY, 0.0f, 0.0f);
		MovementY = FVector(0.0f, DeltaSpeedX, 0.0f);

		CameraOwner->AddActorLocalOffset(MovementX + MovementY, true);
		SetCameraDisable(true); 
	}
	else if (ProportionX >= .975 && ProportionY >= .975) //Bottom right
	{
		DeltaSpeedX = 7.07 * GetSpeedModifier();
		DeltaSpeedY = -7.07;

		MovementX = FVector(DeltaSpeedY, 0.0f, 0.0f);
		MovementY = FVector(0.0f, DeltaSpeedX, 0.0f);

		CameraOwner->AddActorLocalOffset(MovementX + MovementY, true);
		SetCameraDisable(true);
	}
	else if (ProportionX <= .025 && ProportionY <= .025) //Top left corner
	{
		DeltaSpeedX = -7.07 * GetSpeedModifier();
		DeltaSpeedY = 7.07;

		MovementX = FVector(DeltaSpeedY, 0.0f, 0.0f);
		MovementY = FVector(0.0f, DeltaSpeedX, 0.0f);

		CameraOwner->AddActorLocalOffset(MovementX + MovementY, true);
		SetCameraDisable(true);
	}
	else if (ProportionX <= .025 && ProportionY >= .975) //Bottom left corner
	{
		DeltaSpeedX = -7.07 * GetSpeedModifier();
		DeltaSpeedY = -7.07;

		MovementX = FVector(DeltaSpeedY, 0.0f, 0.0f);
		MovementY = FVector(0.0f, DeltaSpeedX, 0.0f);

		CameraOwner->AddActorLocalOffset(MovementX + MovementY, true);
		SetCameraDisable(true);
	}
	else if (ProportionX >= .975) //Far right
	{
		DeltaSpeedX = 10.0 * GetSpeedModifier();
		DeltaSpeedY = 0;

		MovementY = FVector(0.0f, DeltaSpeedX, 0.0f);

		CameraOwner->AddActorLocalOffset(MovementY, true);
		SetCameraDisable(true);
	}
	else if (ProportionX <= .025) //Far left
	{
		DeltaSpeedX = -10.0 * GetSpeedModifier();
		DeltaSpeedY = 0;

		MovementY = FVector(0.0f, DeltaSpeedX, 0.0f);

		CameraOwner->AddActorLocalOffset(MovementY, true);
		SetCameraDisable(true);
	}
}

void UCameraMovement_Component::ZoomIn()
{

}

void UCameraMovement_Component::ZoomOut()
{

}

void UCameraMovement_Component::DefaultZoom()
{

}