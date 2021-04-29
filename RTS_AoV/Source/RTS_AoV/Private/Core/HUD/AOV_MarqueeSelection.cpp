// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/HUD/AOV_MarqueeSelection.h"
#include "RendererInterface.h"
#include "GameFramework/HUD.h"
#include "Math/Color.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

void AAOV_MarqueeSelection::BeginPlay()
{
	Super::BeginPlay();
	PlayerControllerRef = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)); // Populates PlayerControllerRef
}

void AAOV_MarqueeSelection::OnInputStart_Implementation()
{
	if (SelectedUnits.Num() >= 0)
	{

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

void AAOV_MarqueeSelection::ReceiveDrawHUD()
{
	AHUD::ReceiveDrawHUD(SizeX, SizeY);
	if (bIsDrawing)
	{
		DrawMarquee();
	}
	UE_LOG(LogTemp, Warning, TEXT("Vectorassadasdasdadda"));
}

void AAOV_MarqueeSelection::DrawMarquee()
{
	Subtraction = HoldingLocation - ClickedLocation;
	FLinearColor Black1 = FLinearColor(1.0f, 0.2f, 0.2f, 0.6f);
	FLinearColor Blue06 = FLinearColor(0.2f, 0.2f, 1.0f, 0.6f);
	AHUD::DrawRect(Black1, ClickedLocation.X, ClickedLocation.Y, 0.0f, 0.0f);
	AHUD::DrawRect(Black1, HoldingLocation.X, HoldingLocation.Y, 0.0f, 0.0f);
	AHUD::DrawRect(Blue06, ClickedLocation.X, ClickedLocation.Y, Subtraction.X, Subtraction.Y);
}

