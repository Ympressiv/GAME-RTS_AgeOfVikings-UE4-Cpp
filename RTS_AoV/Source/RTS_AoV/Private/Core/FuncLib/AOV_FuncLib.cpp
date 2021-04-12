// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/FuncLib/AOV_FuncLib.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

#define OUT

FVector UAOV_FuncLib::SetCursorWorldPosition(APlayerController* PlayerControllerRef, float SightDistance, FVector& RelativeCursorsLocationInGame)
{
	//Attributes
	PlayerControllerRef = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GEngine->GameViewport->GetWorld(), 0));
	FVector Location;
	FVector Direction;
	FVector Start = Location;
	FHitResult Hit;
	FCollisionQueryParams TraceParams;

	//Methods
	/*Convert Mouse 2D position To World*/
	PlayerControllerRef->DeprojectMousePositionToWorld(Location, Direction);
	FVector End = Location + (Direction * SightDistance);

	/*Line Trace By Channel*/
	bool bHit = GEngine->GameViewport->GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, TraceParams);
	DrawDebugLine(GEngine->GameViewport->GetWorld(), Start, End, FColor::Green, true, 2.0f);

	/*Statement*/
	if (bHit) //Musimy w ifach mieæ warunek bool
	{
		OUT RelativeCursorsLocationInGame = Hit.Location;
		DrawDebugBox(GEngine->GameViewport->GetWorld(), RelativeCursorsLocationInGame, FVector(5, 5, 5), FColor::Green, true, 2.0f);
	}

	return OUT RelativeCursorsLocationInGame;
}