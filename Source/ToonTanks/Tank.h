// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "InputActionValue.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

	public:
	// TankConstructor
	ATank();

	protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	private:
		UPROPERTY(VisibleAnywhere, Category = "Components")
		class USpringArmComponent* SpringArm;

		UPROPERTY(VisibleAnywhere, Category = "Components")
		class UCameraComponent* Camera;

		UPROPERTY(EditAnywhere, Category = "Movement")
		float TurnRate = .5f;


	//Enhanced Input 
	protected:
		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
		class UInputMappingContext* InputMapping;
		
		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
		class UMyInputConfigData* InputActions;

		// Handle move input
		void Move(const FInputActionValue& Value);
		
		// Handle look input
		void Look(const FInputActionValue& Value);

	public:
		// Called to bind functionality to input
		virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;






};
