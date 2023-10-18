// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CubeActor.generated.h"

class ADefaultGameMode;
UENUM()
enum class  ECubeState:uint8
{
	CLEANED,
	CLEANER,
	PAINTED
	
};
UCLASS()
class MYPROJECT2_API ACubeActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACubeActor();
	ECubeState GetState() const;

protected:
	//Properties
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* Cube;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	UMaterial* CleanedMaterial;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	UMaterial* CleanerMaterial;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	UMaterial* PaintedMaterial;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	float JumpForce=600;

	UPROPERTY(EditDefaultsOnly)
	ADefaultGameMode* CurrentGameMode;
	
	ECubeState CurrentState ;
	
	// Methods
	virtual void BeginPlay() override;
	

	UFUNCTION()
	void HitActor(UPrimitiveComponent* HitComponent,AActor* OtherActor,UPrimitiveComponent* OtherComp,FVector NormalImpulse,const FHitResult& Hit);

	void JumpEvent();
	
	void SetState(ECubeState);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
