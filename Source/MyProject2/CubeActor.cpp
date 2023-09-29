// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeActor.h"

#include "OnePawn.h"
#include "DefaultGameMode.h"
#include "GameModeInfoCustomizer.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACubeActor::ACubeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Cube=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Box"));
	SetRootComponent(Cube);
	

}

// Called when the game starts or when spawned
void ACubeActor::BeginPlay()
{
	Super::BeginPlay();
	CurrentGameMode=Cast<ADefaultGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	Cube->OnComponentHit.AddDynamic(this,&ThisClass::HitActor);
	if(FMath::RandBool())
	{
		SetState(ECubeState::CLEANER);
	}else
	{
		SetState(ECubeState::CLEANED);
	}
}

void ACubeActor::SetGameMode(ADefaultGameMode* GameMode)
{
	CurrentGameMode=GameMode;	
}

ECubeState ACubeActor::GetState() const
{
	return CurrentState;
}

void ACubeActor::HitActor(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                          FVector NormalImpulse, const FHitResult& Hit)
{
	AOnePawn* ball=Cast<AOnePawn>(OtherActor);
	ACubeActor* anotherCube=Cast<ACubeActor>(OtherActor);

	if(anotherCube)//collision happened with cube
	{
		if(CurrentState==ECubeState::PAINTED && anotherCube->CurrentState!=ECubeState::CLEANER)
		{
			anotherCube->SetState(ECubeState::PAINTED);	
		}else if(CurrentState==ECubeState::CLEANER && anotherCube->CurrentState!=ECubeState::CLEANER)
		{
			anotherCube->SetState(ECubeState::CLEANED);
		}
	}	else if(ball)//collision happened with ball
	{
		SetState(ECubeState::PAINTED);
	}
}

void ACubeActor::JumpEvent()
{
	FVector randomVector=FMath::VRand();
	randomVector.Z=FMath::Abs(randomVector.Z);
	Cube->AddImpulse(randomVector*JumpForce,NAME_None,true);
}

void ACubeActor::SetState(ECubeState State)
{
		CurrentState=State;
		switch (State)
		{
		case ECubeState::CLEANED:
			Cube->SetMaterial(0,CleanedMaterial);
			break;
		case ECubeState::CLEANER:
			Cube->SetMaterial(0,CleanerMaterial);
			break;
		default:
			Cube->SetMaterial(0,PaintedMaterial);
			break;
		}
	CurrentGameMode->UpdateCubePtr(this);
}

// Called every frame
void ACubeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(GetVelocity().IsZero())
	{
		JumpEvent();
	}
}

