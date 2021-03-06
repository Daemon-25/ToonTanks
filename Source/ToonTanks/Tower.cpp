// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "TimerManager.h"

void ATower::BeginPlay(){
    Super::BeginPlay();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

    GetWorldTimerManager().SetTimer(
        FireRateTimerHandle, 
        this, 
        &ATower::CheckFireCondition, 
        FireRate, 
        true
    );
}

void ATower::Tick(float DeltaTime){
    Super::Tick(DeltaTime);

    if(InRange())
        Rotate(Tank->GetActorLocation());
}

void ATower::HandleDestruction(){
    Super::HandleDestruction();
    Destroy();
}

void ATower::CheckFireCondition(){
    if(!Tank) return;

    if(InRange() && Tank->bAlive)
        Fire();
    
}

bool ATower::InRange(){
    if(!Tank) return false;

    float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());

    if(Distance > FireRange) return false;
    return true;
}