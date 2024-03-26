// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

// Called when the game starts or when spawned
void ATower::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

    //Instantiate for timing our shots
    GetWorldTimerManager().SetTimer(FireRateTimerHandle,this,&ATower::CheckFireCondition, FireRate, true);
}

// Called every frame
void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if(InFireRange())
    {
        //If in range, rotate turret toward tank
        RotateTurret(Tank->GetActorLocation());
    }
}

void ATower::CheckFireCondition()
{
    if(InFireRange())
    {
        //If in range, fire
        Fire();
    }
}

bool ATower::InFireRange()
{
    if(Tank != nullptr)
    {
        //Find the distance to the Tank
        float distance = FVector::Dist(GetActorLocation(),Tank->GetActorLocation());
        //Check to see if the tank is in range
        if(distance <= FireRange)
        {
            //If in range, rotate turret toward tank
            return true;
        }
    }
    return false;
}