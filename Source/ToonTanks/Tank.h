// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()
	
	private:
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "Components", meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* SpringArm;
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "Tank Properties", meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* Camera;
		UPROPERTY(EditAnywhere, category = "Movement")
		float Speed = 800.f;
		UPROPERTY(EditAnywhere, category = "Movement")
		float TurnSpeed = 100.f;

		void Move(float Value);
		void Turn(float Value);

		APlayerController* Controller;

	public:
		ATank();

		// Called when the game starts or when spawned
		virtual void BeginPlay() override;

		// Called to bind functionality to input
		virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

		// Called every frame
		virtual void Tick(float DeltaTime) override;
};
