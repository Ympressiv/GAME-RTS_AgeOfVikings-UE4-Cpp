// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/FuncLib/AOV_FuncLib.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

void UAOV_FuncLib::SetCursorWorldPlacement(APlayerController* PlayerControllerRef, float SightDistance)
{
	/*Attributes*/
	PlayerControllerRef = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GEngine->GameViewport->GetWorld(), 0));
	FVector Location;
	FVector Direction;

	/*Convert Mouse 2D position To World*/
	PlayerControllerRef->DeprojectMousePositionToWorld(Location, Direction);
	FVector WorldDirection_Multiply_SightDistance = Direction * SightDistance;
	FVector WorldLocation_Plus_WorldDirection = Location + WorldDirection_Multiply_SightDistance;

	/*Line Trace By Channel*/
	//LineTrace
}