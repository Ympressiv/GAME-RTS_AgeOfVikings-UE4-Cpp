// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "../Interface/AOV_MarqueeSelection_IF.h"
#include "/Robocze_ProjektyGier/GAME-RTS_AgeOfVikings-UE4-Cpp/RTS_AoV/Source/RTS_AoV/Public/Core/Units/AOV_UnitMaster.h"
#include "GameFramework/HUD.h"
#include "AOV_MarqueeSelection.generated.h"

/**
 * 
 */
UCLASS()
class RTS_AOV_API AAOV_MarqueeSelection : public AHUD, public IAOV_MarqueeSelection_IF
{
	GENERATED_BODY()

protected:
	/*Begin Play*/
	virtual void BeginPlay() override;

public:

	void OnInputStart_Implementation() override; //When the user has hit the button that you have set as your primary action (left mouse button)
	void OnInputHold_Implementation() override; //When a holding we button down 
	void OnInputRelease_Implementation(float HoldTime) override;

	/*This is a refrence to the PlayerController*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "References")
	APlayerController* PlayerControllerRef;

	/*This is a refrence to the Unit Master*/
	UPROPERTY(EditAnywhere, Category = "Units")
	TArray<AAOV_UnitMaster*> SelectedUnits;

	/*Localization of Mouse cursor*/
	float MouseLocationX;
	float MouseLocationY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Marquee Variables")
	FVector2D HoldingLocation;
	FVector2D ClickedLocation;
	FVector2D Subtraction; //Substraction = Holding - Clicked

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bool")
	bool bIsDrawing;

	/*Received HUD*/
	void ReceiveDrawHUD();

	int32 SizeX;
	int32 SizeY;

	UFUNCTION()
	void DrawMarquee();
};
