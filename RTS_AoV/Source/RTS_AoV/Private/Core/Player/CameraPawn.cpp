// Fill out your copyright notice in the Description page of Project Settings.


#include "/Robocze_ProjektyGier/GAME-RTS_AgeOfVikings-UE4-Cpp/RTS_AoV/Source/RTS_AoV/Public/Core/Player/CameraPawn.h"

// Sets default values
ACameraPawn::ACameraPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACameraPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


