// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	//int32 VisibleAnywhereInt = 12;

	//UPROPERTY(EditAnywhere)
	//int32 EditAnywhereInt = 32;

	
	//UPROPERTY(VisibleInstanceOnly)
	//int32 VisibleInstanceOnlyInt = 11;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float speed = 400;

	void HandleDestruction();

	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class UCameraShakeBase> DeathCameraShakeClass;

protected:	//protected classes can be accessed by children
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void RotateTurret(FVector LookAtTarget);
	void Fire();

private:
	//we can forward declare with 'class' so we don't include the header
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class UParticleSystem* DeathParticles;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class USoundBase* DeathSound;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;




};


//Summary
/*
Include only what you use in .cpp
We should include as little as possible in .h
	- We don't need the header to declare a pointer
	- We do need the header to construct an object
	- We do need the header to access members
	- We do need the header for inheritance
*/
