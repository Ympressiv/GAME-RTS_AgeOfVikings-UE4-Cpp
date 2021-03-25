// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Misc/DateTime.h"
#include "PrimaryGameState.generated.h"

UCLASS()
class RTS_AOV_API APrimaryGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	/*Constructor to set default values*/
	APrimaryGameState();

protected:
	/*Begin Play*/
	virtual void BeginPlay() override;

public:
	/*Tick*/
	virtual void Tick(float DeltaTime) override;

//Attributes
protected:
	/*Controler REF - Do later*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Calendar");
	int Years;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Calendar");
	int Months;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Calendar");
	int Days;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Calendar");
	int DayOfWeek;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Calendar");
	int DayCounter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Clock");
	int Hours;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Clock");
	int Minutes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Clock");
	int Seconds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Speed Setting");
	float GameSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Speed Setting");
	float GameTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Speed Setting");
	FDateTime DateTimeStruct;
};
