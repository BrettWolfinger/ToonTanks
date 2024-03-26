// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputAction.h"
#include "MyInputConfigData.generated.h"

/**
 * Data asset to hold all InputActions so that they can be referenced by the player scripts
 */
UCLASS()
class TOONTANKS_API UMyInputConfigData : public UDataAsset
{
	GENERATED_BODY()

	//Grouping for all desired input actions
	public:
		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		UInputAction* InputMove;
	
		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		UInputAction* InputLook;

		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		UInputAction* InputFire;
};
