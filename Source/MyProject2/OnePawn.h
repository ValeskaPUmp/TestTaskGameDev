// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "OnePawn.generated.h"
class UCameraComponent;
class UFloatingPawnMovement;
class UAudioComponent;
class UAnimMontage;
UCLASS()
class MYPROJECT2_API AOnePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AOnePawn();

protected:
	//Properties
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* Sphere;

	UPROPERTY(VisibleAnywhere)
	float Velocity=10.;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere)
	UFloatingPawnMovement* FloatingPawnMovement;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UAudioComponent* AudioComponent;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void AxisForward(float Axis);
	void AxisRight(float Axis);

	void AxisLookAround(float Axis);
	void AxisLookUp(float Axis);

	UFUNCTION()
	void HitActor(UPrimitiveComponent* HitComponent,AActor* OtherActor,UPrimitiveComponent* OtherComp,FVector NormalImpulse,const FHitResult& Hit);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
