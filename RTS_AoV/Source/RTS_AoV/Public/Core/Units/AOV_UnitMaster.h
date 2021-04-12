// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AOV_UnitMaster.generated.h"

UCLASS(Blueprintable)
class AAOV_UnitMaster : public ACharacter
{
	GENERATED_BODY()

public:
	AAOV_UnitMaster();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns SelectedDecal subobject **/
	FORCEINLINE class UDecalComponent* GetSelectedDecal() { return SelectedDecal; }

	/** Returns DeselectedDecal subobject **/
	FORCEINLINE class UDecalComponent* GetDeselectedDecal() { return DeselectedDecal; }

private:
	/** A selected decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* SelectedDecal;

	/** A deselected decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* DeselectedDecal;
};

