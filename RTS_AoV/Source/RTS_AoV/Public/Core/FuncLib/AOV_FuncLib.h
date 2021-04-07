// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AOV_FuncLib.generated.h"

/**
 * 
 */
UCLASS()
class RTS_AOV_API UAOV_FuncLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

		UFUNCTION(BlueprintCallable, Category = "Cursor")
		static void SetCursorWorldPlacement(APlayerController* PlayerControllerRef, float SightDistance);
};
