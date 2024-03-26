// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
//Includes for enhanced input usage
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "MyInputConfigData.h"
 

ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//Create spring arm for our tank holding the camera
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	//location for spawning projectiles
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}


void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    // Get the player controller
    APlayerController* PC = Cast<APlayerController>(GetController());
 
    // Get the local player subsystem
    UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());
    // Clear out existing mapping, and add our mapping
    Subsystem->ClearAllMappings();
    Subsystem->AddMappingContext(InputMapping, 0);

	// Get the EnhancedInputComponent
	UEnhancedInputComponent* PEI = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	// Bind the actions
	PEI->BindAction(InputActions->InputMove, ETriggerEvent::Triggered, this, &ATank::Move);
	PEI->BindAction(InputActions->InputLook, ETriggerEvent::Triggered, this, &ATank::Look);
}

void ATank::Move(const FInputActionValue& Value)
{
    if (Controller != nullptr)
    {
        const FVector2D MoveValue = Value.Get<FVector2D>();
		UE_LOG(LogTemp, Display, TEXT("Value: %f"), MoveValue.Y);
        const FRotator MovementRotation(0, Controller->GetControlRotation().Yaw, 0);
 
        // Forward/Backward direction
        if (MoveValue.Y != 0.f)
        {
            // Get forward vector
            const FVector Direction = MovementRotation.RotateVector(FVector::ForwardVector);
 
            AddMovementInput(Direction, MoveValue.Y);
        }
 

        // Right/Left direction
        if (MoveValue.X != 0.f)
        {
            // Get right vector
            //const FVector Direction = MovementRotation.RotateVector(FVector::RightVector);
 
            //AddMovementInput(Direction, MoveValue.X);
			AddControllerYawInput(MoveValue.X * TurnRate);
        }
    }
}
 
void ATank::Look(const FInputActionValue& Value)
{
    // if (Controller != nullptr)
    // {
    //     const FVector2D LookValue = Value.Get<FVector2D>();
 
    //     if (LookValue.X != 0.f)
    //     {
    //         AddControllerYawInput(LookValue.X);
    //     }
 
    //     if (LookValue.Y != 0.f)
    //     {
    //         AddControllerPitchInput(LookValue.Y);
    //     }
    // }
}