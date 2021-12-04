// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"

ATank::ATank(){
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm->SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);
}

void ATank::BeginPlay(){
    Super::BeginPlay();

    Controller = Cast<APlayerController>(APawn::GetController());
}

void ATank::Tick(float DeltaTime){
    Super::Tick(DeltaTime);

    if(Controller){
        FHitResult HitResult;
        Controller->GetHitResultUnderCursor(
            ECollisionChannel::ECC_Visibility,
            false, 
            HitResult
        );
        Rotate(HitResult.ImpactPoint);

    }
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent){
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
    PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
}

void ATank::Move(float Value){
    FVector DeltaLocation(0.f, 0.f, 0.f);
    DeltaLocation.X = Value*Speed*UGameplayStatics::GetWorldDeltaSeconds(this);

	AddActorLocalOffset(DeltaLocation, true);
}

void ATank::Turn(float Value){
    FRotator DeltaRotation(0.f);
    DeltaRotation.Yaw = Value*TurnSpeed*UGameplayStatics::GetWorldDeltaSeconds(this);

	AddActorLocalRotation(DeltaRotation, true);
}