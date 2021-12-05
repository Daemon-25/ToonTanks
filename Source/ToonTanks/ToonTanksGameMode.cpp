// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"

void AToonTanksGameMode::BeginPlay(){
    Super::BeginPlay();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    Controller = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
}

void AToonTanksGameMode::ActorDied(AActor* ActorDied){
    if(ActorDied == Tank){
        Tank->HandleDestruction();
        if(Controller){
            Controller->SetPlayerEnabledState(false);
        }
    }else if(ATower* DestroyedTower = Cast<ATower>(ActorDied)){
        DestroyedTower->HandleDestruction();
    }
}