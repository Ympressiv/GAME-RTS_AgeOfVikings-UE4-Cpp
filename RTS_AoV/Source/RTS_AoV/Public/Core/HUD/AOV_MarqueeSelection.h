// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "../Interface/AOV_MarqueeSelection_IF.h"
#include "/Robocze_ProjektyGier/GAME-RTS_AgeOfVikings-UE4-Cpp/RTS_AoV/Source/RTS_AoV/Public/Core/Units/AOV_UnitMaster.h"
#include "/Robocze_ProjektyGier/GAME-RTS_AgeOfVikings-UE4-Cpp/RTS_AoV/Source/RTS_AoV/Public/Core/Player/AOV_PlayerController.h"
#include "GameFramework/HUD.h"
#include "RendererInterface.h"
#include "AOV_MarqueeSelection.generated.h"


class AAOV_PlayerController;

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
	AAOV_PlayerController* AOV_PlayerController;

	/*This is a refrence to the Unit Master*/
	UPROPERTY(EditAnywhere, Category = "Units")
	TArray<AAOV_UnitMaster*> SelectedUnits;

	/*This is a refrence to the UnitMaster*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "References")
	AAOV_UnitMaster* SelectedUnitFromArea = Cast<AAOV_UnitMaster>(GetOwner());

	/*Localization of Mouse cursor*/
	float MouseLocationX;
	float MouseLocationY;

	/*Marquee Variables*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Marquee Variables")
	FVector2D HoldingLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Marquee Variables")
	FVector2D ClickedLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Marquee Variables")
	FVector2D Subtraction; //Substraction = Holding - Clicked

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bool")
	bool bIsDrawing;

	/*Draw HUD*/
	UFUNCTION(BlueprintCallable)
	void DrawHUD() override;
	UFUNCTION(BlueprintCallable)
	void DrawMarquee();
};
