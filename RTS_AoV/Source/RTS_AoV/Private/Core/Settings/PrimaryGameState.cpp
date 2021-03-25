// Fill out your copyright notice in the Description page of Project Settings.


#include "/Robocze_ProjektyGier/GAME-RTS_AgeOfVikings-UE4-Cpp/RTS_AoV/Source/RTS_AoV/Public/Core/Settings/PrimaryGameState.h"

/*Constructor*/
APrimaryGameState::APrimaryGameState()
{
	/*Init*/

	/*Calendar*/
	Years = 2021;
	Months = 03;
	Days = 25;
	DayOfWeek = 4; //Thursday
	DayCounter = 0;

	/*Clock*/
	Hours = 10;
	Minutes = 15;
	Seconds = 15;

	/*Game Speed Settings*/
	/*
	Real Time : GameSpeed = Time in Game
	1s : 1 = 1 game hour
	1s : 60  = 1 game minute
	1s : 3600 = real time (1s in real is 1s in game)
	1m : 2.5 = 1 game day
	1hr : 150 = 1 game day
	*/

	GameSpeed = 60;
	GameTime = (Hours + (Minutes / float(60.0f)) + (Seconds / float(3600.0f)));
	DateTimeStruct = (Years, Months, Days, Seconds);

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

/*BeginPlay*/
void APrimaryGameState::BeginPlay()
{
	Super::BeginPlay();
}

/*Tick*/
void APrimaryGameState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GameSpeed != 0)
	{

	}
}