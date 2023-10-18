// Fill out your copyright notice in the Description page of Project Settings.


#include "OnePawn.h"

#include "CubeActor.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/AudioComponent.h"

// Sets default values
AOnePawn::AOnePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Sphere=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere"));
	SetRootComponent(Sphere);
	Camera=CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(Sphere);
	FloatingPawnMovement=CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));
	AudioComponent=CreateDefaultSubobject<UAudioComponent>(TEXT("PawnSpeaker"));
	AudioComponent->SetupAttachment(Sphere);
}

// Called when the game starts or when spawned
void AOnePawn::BeginPlay()
{
	Super::BeginPlay();
	Sphere->OnComponentHit.AddDynamic(this,&ThisClass::HitActor);
}

void AOnePawn::AxisForward(float Axis)
{
	FVector result=GetActorForwardVector();
	result.Z=0;
	result*=Velocity*Axis;
	AddMovementInput(result);
}

void AOnePawn::AxisRight(float Axis)
{
	FVector result=GetActorRightVector();
	result.Z=0;
	result*=Velocity*Axis;
	AddMovementInput(result);
}

void AOnePawn::AxisLookAround(float Axis)
{
	AddControllerYawInput(Axis);
}

void AOnePawn::AxisLookUp(float Axis)
{
	AddControllerPitchInput(Axis);
}

void AOnePawn::HitActor(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if(Cast<ACubeActor>(OtherActor))
	{
		OtherComp->AddImpulse(-Hit.Normal*Velocity*100,NAME_None,true);
		AudioComponent->Play();
	}
}

// Called every frame
void AOnePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AOnePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("FB",this,&ThisClass::AxisForward);
	PlayerInputComponent->BindAxis("RL",this,&ThisClass::AxisRight);
	PlayerInputComponent->BindAxis("LookAround",this,&ThisClass::AxisLookAround);
	PlayerInputComponent->BindAxis("LookUp",this,&ThisClass::AxisLookUp);
}

