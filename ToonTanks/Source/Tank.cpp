// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Math/Rotator.h"
//#include "DrawDebugHelpers.h"

ATank::ATank() {
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm->SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    //name of axis component, object to notice, address of class
    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);

    PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
}

void ATank::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if(TankPlayerController)
    {
        FHitResult HitResult;
        TankPlayerController->GetHitResultUnderCursor(
            ECollisionChannel::ECC_Visibility, 
            false, 
            HitResult);
        
       // DrawDebugSphere(
       // GetWorld(), 
       // HitResult.ImpactPoint,  //location of the debug sphere
       // 25.f,   //sphere radius
       // 12, //number of sections: More equals a better circle
       // FColor::Red,
       // false,   //persistant lines
       // -1.f);  //duration of how long it will be displayed (-1.f calls for single frame)
    
        RotateTurret(HitResult.ImpactPoint);
    }

}

void ATank::HandleDestruction(){
    Super::HandleDestruction();
    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
    bAlive = false;
}

void ATank::BeginPlay()
{
    Super::BeginPlay();
    //get player controller reference
    TankPlayerController = Cast<APlayerController>(GetController());
}


void ATank::Move(float Value)
{
    FVector DeltaLocation(0.f); //zero's out the vector
    // X = Value * DeltaTime * Speed

    DeltaLocation.X = Value * MoveSpeed * GetWorld()->GetDeltaSeconds();
    //DeltaLocation.X = Value;
    AddActorLocalOffset(DeltaLocation, true); //allows for movement to local space
}

void ATank::Turn(float Value)
{
    FRotator DeltaRotation = FRotator::ZeroRotator;
    // Yaw = Value * DeltaTime * TurnRate;
    DeltaRotation.Yaw = Value * TurnRate * GetWorld()->GetDeltaSeconds();
    AddActorLocalRotation(DeltaRotation, true);
}

