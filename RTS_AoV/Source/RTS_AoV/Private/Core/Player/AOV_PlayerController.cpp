// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/Player/AOV_PlayerController.h"
#include "GameFramework/PlayerController.h"
#include "Components/InputComponent.h"
#include "/Robocze_ProjektyGier/GAME-RTS_AgeOfVikings-UE4-Cpp/RTS_AoV/Source/RTS_AoV/Public/Core/Player/CameraMovement_Component.h"
#include "Math/TransformNonVectorized.h"

AAOV_PlayerController::AAOV_PlayerController()
{
	/*Set this pawn to call Tick() every frame.
	We can turn off as we needed */
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	/*Change class od UnitMaster - switch for C++ or BP Unit*/
	UnitToSpawn_Class = AAOV_UnitMaster::StaticClass();
}

/*Begin Play*/
void AAOV_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	/*Refrence casts*/
	CameraPawnRef = Cast<ACameraPawn>(GetPawn()); //Get camera pawn
	CameraMovementRef = CameraPawnRef->PawnMovementComponent;

	/*Show Mouse*/
	bShowMouseCursor = true;
}

void AAOV_PlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CameraMovementRef->EdgeScroll();

	UE_LOG(LogTemp, Warning, TEXT("Vector: %s"), *SetCursorWorldPositionRef.ToString());
	
}

void AAOV_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent(); // This gives the ability to start doing input
	
	/*Setup gameplay key bindings*/
	check(InputComponent);

	/*Input Events - Related to BasicMovement*/
	/*Move Forward*/
	InputComponent->BindAxis("MoveForward", this, &AAOV_PlayerController::CallMoveForward);
	/*Move Right*/
	InputComponent->BindAxis("MoveRight", this, &AAOV_PlayerController::CallMoveRight);
	/*SpeedModifier - increase movement speed while shift is held down*/
	InputComponent->BindAction("SpeedModifier", IE_Pressed, this, &AAOV_PlayerController::CallIncreaseSpeedModifier);
	/*SpeedModifier - restore default movement speed when shift is not held down*/
	InputComponent->BindAction("SpeedModifier", IE_Released, this, &AAOV_PlayerController::CallDecreaseSpeedModifier);

	/*InputEvents - Related to other movements*/
	/*PanCameraLeft*/
	InputComponent->BindAction("PanCameraLeft", IE_Pressed, this, &AAOV_PlayerController::CallPanCameraLeft);
	/*PanCameraRight*/
	InputComponent->BindAction("PanCameraRight", IE_Pressed, this, &AAOV_PlayerController::CallPanCameraRight);
	/*PanReset*/
	InputComponent->BindAction("PanReset", IE_Pressed, this, &AAOV_PlayerController::CallPanReset);
	/*ZoomIn*/
	InputComponent->BindAction("ZoomIn", IE_Pressed, this, &AAOV_PlayerController::CallZoomIn);
	/*ZoomOut*/
	InputComponent->BindAction("ZoomOut", IE_Pressed, this, &AAOV_PlayerController::CallZoomOut);
	/*ZoomReset*/
	InputComponent->BindAction("ResetZoom", IE_Pressed, this, &AAOV_PlayerController::CallZoomReset);
	/*UnitTest*/
	InputComponent->BindAction("UnitTest", IE_Pressed, this, &AAOV_PlayerController::CallUnitTest);
}

void AAOV_PlayerController::CallMoveForward(float Value)
{
	CameraMovementRef->BasicMovementControl(Value, 0.0);
}

void AAOV_PlayerController::CallMoveRight(float Value)
{
	CameraMovementRef->BasicMovementControl(0.0, Value);
} 

void AAOV_PlayerController::CallIncreaseSpeedModifier()
{
	CameraMovementRef->SetMovementSpeedModifier(2.0f);
}

void AAOV_PlayerController::CallDecreaseSpeedModifier()
{
	CameraMovementRef->SetMovementSpeedModifier(1.0f);
}

void AAOV_PlayerController::CallPanCameraLeft()
{
	CameraMovementRef->PanCamera(18.0f);
}

void AAOV_PlayerController::CallPanCameraRight()
{
	CameraMovementRef->PanCamera(-18.0f);
}

void AAOV_PlayerController::CallPanReset()
{
	CameraMovementRef->ResetPan();
}

void AAOV_PlayerController::CallZoomIn()
{
	CameraMovementRef->ZoomIn();
}

void AAOV_PlayerController::CallZoomOut()
{
	CameraMovementRef->ZoomOut();
}

void AAOV_PlayerController::CallZoomReset()
{
	CameraMovementRef->DefaultZoom();
}

void AAOV_PlayerController::CallUnitTest()
{
	//Attributes
	SightDistance = 1200.0f;
	SetCursorWorldPositionRef = FuncLibRef->SetCursorWorldPosition(this, SightDistance, RelativeCursorsLocationInGame);

	FVector Location (SetCursorWorldPositionRef.X, SetCursorWorldPositionRef.Y, 150.0f); 
	FRotator Rotation(0.0f, 0.0f, 0.0f); 

	//Methods
	/*Spawn Unit*/
	SpawnedUnit = Cast<AAOV_UnitMaster>(GetWorld()->SpawnActor<AActor>(UnitToSpawn_Class, Location, Rotation));
	if (SpawnedUnit != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Set Owner Called"));
	}
}