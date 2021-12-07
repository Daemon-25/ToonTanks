// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"

void AToonTanksGameMode::BeginPlay(){
    Super::BeginPlay();

    HandleGameStart();
}

void AToonTanksGameMode::HandleGameStart(){
    TowerCount = GetTowerCount();
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    Controller = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

    StartGame();

    if(Controller){
        Controller->SetPlayerEnabledState(false);
        FTimerHandle PlayerEnableTimerHandle;
        FTimerDelegate InputDelegate = FTimerDelegate::CreateUObject(
            Controller,
            &AToonTanksPlayerController::SetPlayerEnabledState,
            true
        );

        GetWorldTimerManager().SetTimer(
            PlayerEnableTimerHandle,
            InputDelegate,
            StartDelay,
            false
        );
    }
}

void AToonTanksGameMode::ActorDied(AActor* ActorDied){
    if(ActorDied == Tank){
        Tank->HandleDestruction();
        if(Controller){
            Controller->SetPlayerEnabledState(false);
        }
        GameOver(false);
    }else if(ATower* DestroyedTower = Cast<ATower>(ActorDied)){
        DestroyedTower->HandleDestruction();
        TowerCount--;
        if(TowerCount==0)
            GameOver(true);
    }
}

int32 AToonTanksGameMode::GetTowerCount(){
    TArray<AActor*> Actors;
    UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Actors);

    return Actors.Num();
}