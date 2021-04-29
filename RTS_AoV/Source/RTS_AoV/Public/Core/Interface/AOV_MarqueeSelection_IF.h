// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AOV_MarqueeSelection_IF.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAOV_MarqueeSelection_IF : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RTS_AOV_API IAOV_MarqueeSelection_IF
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, Category = "Input")
	void OnInputStart(); //When the user has hit the button that you have set as your primary action (left mouse button)

	UFUNCTION(BlueprintNativeEvent, Category = "Input")
	void OnInputHold(); //When a holding we button down 

	UFUNCTION(BlueprintNativeEvent, Category = "Input")
	void OnInputRelease(float HoldTime); 
};
