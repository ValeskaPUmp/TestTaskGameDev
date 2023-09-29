// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "DefaultGameMode.generated.h"
class ACubeActor;
/**
 * 
 */
UCLASS()
class MYPROJECT2_API ADefaultGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	ADefaultGameMode();
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TSet <ACubeActor*> CleanedCubes;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TSet <ACubeActor*> CleanerCubes;

	UFUNCTION(BlueprintCallable)
	bool GameOver() const;

	void AddCubePtr(ACubeActor* Cube);

	void UpdateCubePtr(ACubeActor* Cube);

	void RemoveCubePtr(ACubeActor* Cube);
	
};
