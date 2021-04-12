// Copyright Epic Games, Inc. All Rights Reserved.

#include "/Robocze_ProjektyGier/GAME-RTS_AgeOfVikings-UE4-Cpp/RTS_AoV/Source/RTS_AoV/Public/Core//Units/AOV_UnitMaster.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"

AAOV_UnitMaster::AAOV_UnitMaster()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(100.0f, 62.0f);

	// Create a decal in the world to show the cursor's location
	/*Selected Decal*/
	SelectedDecal = CreateDefaultSubobject<UDecalComponent>("SelectedDecal");
	SelectedDecal->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Material'/Game/Materials/GoodSelectionDecal'"));
	if (DecalMaterialAsset.Succeeded())
	{
		SelectedDecal->SetDecalMaterial(DecalMaterialAsset.Object);
	}
	SelectedDecal->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	SelectedDecal->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());

	/*Deselected Decal*/
	DeselectedDecal = CreateDefaultSubobject<UDecalComponent>("DeselectedDecal");
	DeselectedDecal->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UMaterial> DeDecalMaterialAsset(TEXT("Material'/Game/Materials/BadSelectionDecal'"));
	if (DeDecalMaterialAsset.Succeeded())
	{
		DeselectedDecal->SetDecalMaterial(DeDecalMaterialAsset.Object);
	}
	DeselectedDecal->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	DeselectedDecal->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AAOV_UnitMaster::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

}
