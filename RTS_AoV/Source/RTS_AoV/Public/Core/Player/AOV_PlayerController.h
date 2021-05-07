// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "/Robocze_ProjektyGier/GAME-RTS_AgeOfVikings-UE4-Cpp/RTS_AoV/Source/RTS_AoV/Public/Core/FuncLib/AOV_FuncLib.h"
#include "/Robocze_ProjektyGier/GAME-RTS_AgeOfVikings-UE4-Cpp/RTS_AoV/Source/RTS_AoV/Public/Core/Units/AOV_UnitMaster.h"
#include "CoreMinimal.h"
#include "CameraPawn.h"
#include "GameFramework/PlayerController.h"
#include "RTS_AoV/Public/Core/HUD/AOV_MarqueeSelection.h"
#include "AOV_PlayerController.generated.h"

class AAOV_MarqueeSelection;

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

/* Methods */

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

	virtual void CallUnitTest();

	virtual void CallPrimaryAction_Pressed();

	virtual void CallPrimaryAction_Released();

	virtual void CallSecondaryAction_Pressed();

	/*Selection Units Update*/
	UFUNCTION()
	void UpdateSelection(float DeltaTime);

	/*Set selected units*/
	UFUNCTION(BlueprintCallable, Category = "UnitControl")
	virtual void SetSelectedUnits(TArray<AAOV_UnitMaster*> SelectedUnits);

/* Attributes */
	/*Get Hit Result Under Cursor By Trace Channel*/
	UPROPERTY(EditAnywhere, Category = "MarqeeVariables")
	FHitResult HitMouseTrace;

	ETraceTypeQuery TraceChannel;

	/*Holding pressed LeftMouseButton*/
	UPROPERTY(EditAnywhere, Category = "MarqeeVariables")
	float HoldingTime;

	/*Sight Distance*/
	float SightDistance;

	/*Target Location of trace hit from: Get Hit Result Under Cursor By Trace Channel */
	FVector TargetLocation;

	/*Decal spawned in hit result*/
	UMaterialInterface* MovementDecal;

	/*Player is holding input?*/
	UPROPERTY(EditAnywhere, Category = "MarqeeVariables")
	bool bIsHoldingInput;

	/*Is Unit Selected?*/
	UPROPERTY(EditAnywhere, Category = "MarqeeVariables")
	bool bIsUnitSelected;

	/*Output of SetCursorWorldPosition*/
	FVector RelativeCursorsLocationInGame;

	/*Refrence to SetCursorWorldPosition*/
	FVector SetCursorWorldPositionRef;

	/*This is a refrence to the Camera Pawn*/
	UPROPERTY(Transient)
	ACameraPawn* CameraPawnRef = nullptr;

	/*This is a refrence to the Camera Movement Component */
	UPROPERTY(Transient)
	UCameraMovement_Component* CameraMovementRef = nullptr;

	/*This is a refrence to the Function Library*/
	UPROPERTY()
	UAOV_FuncLib* FuncLibRef;

	/*This is a refrence to the Unit Master*/
	UPROPERTY()
	AAOV_UnitMaster* SpawnedUnit;

	/*This is a refrence to the Unit Master*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AAOV_UnitMaster> UnitToSpawn_Class;

	/*This is a refrence to the MarqueeSelection*/
	UPROPERTY()
	AAOV_MarqueeSelection* MarqueeSelectionRef;

	/*This is a refrence to the MarqueeSelectionInterface_Ref*/
	IAOV_MarqueeSelection_IF* MarqueeSelectionInterface_Ref;

	/*Spawned Decal at location*/
	UDecalComponent* PreviousLocationDecal;


};
