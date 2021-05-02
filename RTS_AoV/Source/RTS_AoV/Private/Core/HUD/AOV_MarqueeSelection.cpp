// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/HUD/AOV_MarqueeSelection.h"
#include "RendererInterface.h"
#include "GameFramework/HUD.h"
#include "Math/Color.h"
#include "GameFramework/PlayerController.h"
#include "/Robocze_ProjektyGier/GAME-RTS_AgeOfVikings-UE4-Cpp/RTS_AoV/Source/RTS_AoV/Public/Core/Units/AOV_UnitMaster.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

void AAOV_MarqueeSelection::BeginPlay()
{
	Super::BeginPlay();
	PlayerControllerRef = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)); // Populates PlayerControllerRef
	UnitMasterRef = Cast<AAOV_UnitMaster>(GetOwner());
}

void AAOV_MarqueeSelection::OnInputStart_Implementation()
{
	if (SelectedUnits.Num() > 0)
	{
		for (AAOV_UnitMaster* Unit : SelectedUnits)
		{
			UnitMasterRef->SetDeselectedDecal();
		}
	}
	else
	{
		PlayerControllerRef->GetMousePosition(MouseLocationX, MouseLocationY); 
		ClickedLocation = FVector2D(MouseLocationX, MouseLocationY);
		HoldingLocation = ClickedLocation;
		bIsDrawing = true;
	}
}

void AAOV_MarqueeSelection::OnInputHold_Implementation()
{
	PlayerControllerRef->GetMousePosition(MouseLocationX, MouseLocationY); 
	HoldingLocation = FVector2D(MouseLocationX, MouseLocationY);
}

void AAOV_MarqueeSelection::OnInputRelease_Implementation(float HoldTime)
{
	bIsDrawing = false;
}

void AAOV_MarqueeSelection::DrawHUD()
{
	if (bIsDrawing)
	{
		DrawMarquee();
	}
}

void AAOV_MarqueeSelection::DrawMarquee()
{
	Subtraction = HoldingLocation - ClickedLocation;
	FString test = Subtraction.ToString();
	UE_LOG(LogTemp, Warning, TEXT("Subtraction value: Holding - Clicked: %s"), *test);
	FLinearColor Black03 = FLinearColor(0.0f, 0.0f, 0.0f, 0.3f);
	FLinearColor Blue1 = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);
	AHUD::DrawRect(Blue1, ClickedLocation.X, ClickedLocation.Y, 0.1f, 0.1f);
	AHUD::DrawRect(Blue1, HoldingLocation.X, HoldingLocation.Y, 0.1f, 0.1f);
	AHUD::DrawRect(Black03, ClickedLocation.X, ClickedLocation.Y, Subtraction.X, Subtraction.Y);
}

