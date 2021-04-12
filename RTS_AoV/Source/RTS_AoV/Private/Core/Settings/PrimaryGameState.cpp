// Fill out your copyright notice in the Description page of Project Settings.


#include "/Robocze_ProjektyGier/GAME-RTS_AgeOfVikings-UE4-Cpp/RTS_AoV/Source/RTS_AoV/Public/Core/Settings/PrimaryGameState.h"
#include "Misc/DateTime.h"
#include "Engine/Engine.h"

/*Constructor*/
APrimaryGameState::APrimaryGameState()
{
	/*Init*/

	/*Calendar*/
	Years = 2021;
	Months = 03;
	Days = 31;
	DayOfWeek = 3;
	DayCounter = 0;

	/*Clock*/
	Hours = 23;
	Minutes = 59;
	Seconds = 0;

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
	DateTimeStruct = (Years, Months, Days, Hours, Minutes, Seconds);

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
		CalculateTime(DeltaTime, GameSpeed, GameTime, GameTime, DayCounter);
		SetClockCalendar();
	}
	//UE_LOG(LogTemp, Warning, TEXT("%i : %i : %i - godzina, minuta, sekunda "), Hours, Minutes, Seconds);
	//UE_LOG(LogTemp, Warning, TEXT("%i : %i : %i - dzien, miesiac, rok"), Days, Months, Years);
	//UE_LOG(LogTemp, Warning, TEXT("%i"), DateTimeStruct.GetHour12());
}

void APrimaryGameState::CalculateTime(float DeltaTime, float CurrentGameSpeed, float GameTimeIn, float& GameTimeOut, int& DayCounterOut)
{
	GameTime = fmod(((DeltaTime / CurrentGameSpeed) + GameTimeIn), 24.0);
	DayCounter = (((DeltaTime / CurrentGameSpeed) + GameTimeIn) / 24.0);
	GameTimeOut = GameTime; //For BP use only
	DayCounterOut = DayCounter; //For BP use only
}

void APrimaryGameState::SetClockCalendar()
{
	//Calculate Seconds, Minutes, Hours
	float InitialConversion = GameTime * 3600.0f;
	Seconds = floor(fmod(InitialConversion, 60));
	Minutes = floor(fmod(int(InitialConversion / 60), 60.0));
	Hours = floor(fmod(int((InitialConversion / 60) / 60), 24.0));

	//Set Calendar
	DayOfWeek += DayCounter;
	if (DayOfWeek > 7)
	{
		DayOfWeek = 1;
	}
	Days += DayCounter;
	if (Days > DateTimeStruct.DaysInMonth(Years, Months))
	{
		Days = 1;
		Months++; 
	}
	if (Months > 12)
	{
		Months = 1;
		Years++;
	}
	SetDateTime(Years, Months, Days, Hours, Minutes, Seconds);
}

void APrimaryGameState::SetDateTime(UPARAM(ref) int& Year, UPARAM(ref) int& Month, UPARAM(ref) int& Day, UPARAM(ref) int& Hour, UPARAM(ref) int& Minute, UPARAM(ref) int& Second)
{
	DateTimeStruct = (Year, Month, Day, Hour, Minute, Second);
}

