// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/HUD/AOV_MarqueeSelection.h"
#include "RendererInterface.h"
#include "GameFramework/HUD.h"
#include "Math/Color.h"
#include "/Robocze_ProjektyGier/GAME-RTS_AgeOfVikings-UE4-Cpp/RTS_AoV/Source/RTS_AoV/Public/Core/Units/AOV_UnitMaster.h"
#include "/Robocze_ProjektyGier/GAME-RTS_AgeOfVikings-UE4-Cpp/RTS_AoV/Source/RTS_AoV/Public/Core/Player/AOV_PlayerController.h"
#include "UObject/Class.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

class AAOV_UnitMaster;

#define OUT

void AAOV_MarqueeSelection::BeginPlay()
{
	Super::BeginPlay();
	AOV_PlayerController = Cast<AAOV_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)); // Populates AOV_PlayerController
}

void AAOV_MarqueeSelection::OnInputStart_Implementation()
{
	if (SelectedUnits.Num() > 0)
	{
		for (AAOV_UnitMaster* Unit : SelectedUnits)
		{
			Unit->SetDeselectedDecal();
			Unit->bIsSelected = false;
			AOV_PlayerController->bIsUnitSelected = false;
		}
		SelectedUnits.Empty();
		AOV_PlayerController->GetMousePosition(MouseLocationX, MouseLocationY);
		ClickedLocation = FVector2D(MouseLocationX, MouseLocationY);
		HoldingLocation = ClickedLocation;
		bIsDrawing = true;
	}
	else
	{
		AOV_PlayerController->GetMousePosition(MouseLocationX, MouseLocationY); 
		ClickedLocation = FVector2D(MouseLocationX, MouseLocationY);
		HoldingLocation = ClickedLocation;
		bIsDrawing = true;
	}
}

void AAOV_MarqueeSelection::OnInputHold_Implementation()
{
	AOV_PlayerController->GetMousePosition(MouseLocationX, MouseLocationY); 
	HoldingLocation = FVector2D(MouseLocationX, MouseLocationY);
}

void AAOV_MarqueeSelection::OnInputRelease_Implementation(float HoldTime)
{
	bIsDrawing = false;
	AOV_PlayerController->SetSelectedUnits(SelectedUnits);
}

void AAOV_MarqueeSelection::DrawHUD()
{
	if (bIsDrawing)
	{
		DrawMarquee();
		TArray<AActor*> Out_UnitsInSelectionArea;
		bool bIncludeNonCollidingComponents;
		bool bActorMustBeFullyEnclosed;
		AHUD::GetActorsInSelectionRectangle
		(	
			AOV_PlayerController->UnitToSpawn_Class, 
			ClickedLocation, 
			HoldingLocation, 
			OUT Out_UnitsInSelectionArea,
			bIncludeNonCollidingComponents = false, 
			bActorMustBeFullyEnclosed = false
		);
		for (AActor* UnitFromSelectionArea : Out_UnitsInSelectionArea)
		{
			bool IsUnitMasterChild = UnitFromSelectionArea->GetClass()->IsChildOf(AAOV_UnitMaster::StaticClass());
			if (IsUnitMasterChild)
			{
				SelectedUnitFromArea = Cast<AAOV_UnitMaster>(UnitFromSelectionArea);
				SelectedUnits.AddUnique(SelectedUnitFromArea);
				for (AAOV_UnitMaster* Unit : SelectedUnits)
				{
					Unit->SetSelectedDecal();
					Unit->bIsSelected = true;
				}
			}
		}
	}
}

void AAOV_MarqueeSelection::DrawMarquee()
{
	Subtraction = HoldingLocation - ClickedLocation;
	FString test = Subtraction.ToString();
	UE_LOG(LogTemp, Warning, TEXT("Subtraction value: Holding - Clicked: %s"), *test);
	FLinearColor Black04 = FLinearColor(0.0f, 0.0f, 0.0f, 0.4f);
	FLinearColor White04 = FLinearColor(1.0f, 1.0f, 1.0f, 0.4f);
	AHUD::DrawRect(White04, ClickedLocation.X, ClickedLocation.Y, 0.0f, 0.0f);
	AHUD::DrawRect(White04, HoldingLocation.X, HoldingLocation.Y, 0.0f, 0.0f);
	AHUD::DrawRect(Black04, ClickedLocation.X, ClickedLocation.Y, Subtraction.X, Subtraction.Y);
}

