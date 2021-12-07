// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()

	private:
		class ATank* Tank;
		class AToonTanksPlayerController* Controller;
		float StartDelay = 3.f;

		void HandleGameStart();

		int32 TowerCount = 0;
		int32 GetTowerCount();

	protected:
		virtual void BeginPlay() override;

		UFUNCTION(BlueprintImplementableEvent)
		void StartGame();
		
		UFUNCTION(BlueprintImplementableEvent)
		void GameOver(bool wbGameWon);

	public:
		void ActorDied(AActor* DeadActor);

};
