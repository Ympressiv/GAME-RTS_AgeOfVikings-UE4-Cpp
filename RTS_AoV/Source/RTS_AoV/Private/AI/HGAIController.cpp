// Fill out your copyright notice in the Description page of Project Settings.


#include "/Robocze_ProjektyGier/GAME-RTS_AgeOfVikings-UE4-Cpp/RTS_AoV/Source/RTS_AoV/Public/AI/HGAIController.h"
#include "/Robocze_ProjektyGier/GAME-RTS_AgeOfVikings-UE4-Cpp/RTS_AoV/Source/RTS_AoV/Public/AI/HGPathFollowingComponent.h"

/**
 * Here we assign our HGPathFollowingComponent class to the HGAIController so when we make an instance of this class it will use our component instead of the default,
 * keep attention on the TEXT() parameter, to work well it must be the same as the default component of the parent AIController class!
 */
AHGAIController::AHGAIController(const FObjectInitializer &ObjectInitializer /*= FObjectInitializer::Get()*/)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UHGPathFollowingComponent>(TEXT("PathFollowingComponent")))
{

}
