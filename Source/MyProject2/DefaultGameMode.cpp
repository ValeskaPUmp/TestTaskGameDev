// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultGameMode.h"
#include "CubeActor.h"

ADefaultGameMode::ADefaultGameMode()
{
}

bool ADefaultGameMode::GameOver() const
{
	return CleanedCubes.IsEmpty() && CleanerCubes.IsEmpty();
}

void ADefaultGameMode::AddCubePtr(ACubeActor* Cube)
{
	switch (Cube->GetState())
	{
	case(ECubeState::CLEANED):
		CleanedCubes.Add(Cube);
		break;
	case(ECubeState::CLEANER):
		CleanerCubes.Add(Cube);
		break;
	default:
		break;
	}
}

void ADefaultGameMode::UpdateCubePtr(ACubeActor* Cube)
{
	RemoveCubePtr(Cube);
	AddCubePtr(Cube);
}

void ADefaultGameMode::RemoveCubePtr(ACubeActor* Cube)
{
	CleanedCubes.Remove(Cube);
	CleanerCubes.Remove(Cube);
}
