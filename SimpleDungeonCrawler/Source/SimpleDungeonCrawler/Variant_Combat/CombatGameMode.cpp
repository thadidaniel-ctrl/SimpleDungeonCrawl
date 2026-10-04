// Copyright Epic Games, Inc. All Rights Reserved.

#include "Variant_Combat/CombatGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Engine/StaticMeshActor.h"
#include "Engine/StaticMesh.h"
#include "TimerManager.h"
#include "Math/UnrealMathUtility.h"
#include "UObject/ConstructorHelpers.h"

ACombatGameMode::ACombatGameMode()
{
	// stub
	// Try to load a default room mesh (engine cube) if not set in the editor
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
	if (CubeMesh.Succeeded())
	{
		RoomMesh = CubeMesh.Object;
	}
}

void ACombatGameMode::BeginPlay()
{
	Super::BeginPlay();

	// Only the server should generate the dungeon in a multiplayer context
	if (HasAuthority())
	{
		GenerateDungeon();
	}

	// create each additional local player.
	// Player 0 will be created automatically as part of regular game init
	for (int32 i = 2; i <= NumberOfLocalPlayers; ++i)
	{
		UGameplayStatics::CreatePlayer(GetWorld(), -1, true);
	}
}

void ACombatGameMode::GenerateDungeon()
{
	// Clear any existing rooms first
	ClearDungeon();

	if (!RoomMesh)
	{
		UE_LOG(LogTemp, Warning, TEXT("RoomMesh not assigned in CombatGameMode. Please assign a static mesh for room generation."));
		return;
	}

	// We'll use a simple random walk algorithm to generate rooms
	// Start at (0,0) - the entrance
	TSet<FIntPoint> UsedPositions;
	TArray<FIntPoint> Frontier;

	const FIntPoint Start(0, 0);
	UsedPositions.Add(Start);
	Frontier.Add(Start);

	// Spawn the entrance room
	SpawnRoomAt(Start.X, Start.Y);

	// Keep adding rooms until we reach MaxRooms or run out of frontier
	while (UsedPositions.Num() < MaxRooms && Frontier.Num() > 0)
	{
		// Pick a random frontier cell
		const int32 FrontierIndex = FMath::RandRange(0, Frontier.Num() - 1);
		const FIntPoint Current = Frontier[FrontierIndex];

		// Get all possible adjacent directions (up, down, left, right)
		const TArray<FIntPoint> Directions = {
			FIntPoint(1, 0),   // Right
			FIntPoint(-1, 0),  // Left
			FIntPoint(0, 1),   // Up
			FIntPoint(0, -1)   // Down
		};

		// Shuffle the directions for randomness
		for (int32 i = Directions.Num() - 1; i > 0; --i)
		{
			const int32 SwapIndex = FMath::RandRange(0, i);
			const FIntPoint Temp = Directions[i];
			const FIntPoint Swap = Directions[SwapIndex];
			const_cast<TArray<FIntPoint>&>(Directions)[i] = Swap;
			const_cast<TArray<FIntPoint>&>(Directions)[SwapIndex] = Temp;
		}

		bool bFoundValidPosition = false;
		for (const FIntPoint& Dir : Directions)
		{
			const FIntPoint NewPos = Current + Dir;

			// Check if this position is already used
			if (UsedPositions.Contains(NewPos))
			{
				continue;
			}

			// Check if the new position is valid (not overlapping with existing rooms)
			if (!IsPositionOccupied(NewPos.X, NewPos.Y))
			{
				// Add this position to our dungeon
				UsedPositions.Add(NewPos);
				Frontier.Add(NewPos);
				SpawnRoomAt(NewPos.X, NewPos.Y);
				bFoundValidPosition = true;
				break; // Only add one room per frontier cell per iteration
			}
		}

		// If we didn't find a valid position from this frontier cell, remove it from frontier
		if (!bFoundValidPosition)
		{
			Frontier.RemoveAt(FrontierIndex);
		}
	}
}

void ACombatGameMode::ClearDungeon()
{
	for (TObjectPtr<AStaticMeshActor> RoomActor : SpawnedRooms)
	{
		if (IsValid(RoomActor))
		{
			RoomActor->Destroy();
		}
	}
	SpawnedRooms.Empty();
	OccupiedGridPositions.Empty();
}

void ACombatGameMode::SpawnRoomAt(int32 GridX, int32 GridY)
{
	if (!GetWorld() || !RoomMesh)
	{
		return;
	}

	// Calculate world location based on grid position
	const float WorldX = GridX * RoomSize;
	const float WorldY = GridY * RoomSize;
	const FVector Location(WorldX, WorldY, 0.f);

	// Spawn the room
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AStaticMeshActor* NewRoom = GetWorld()->SpawnActor<AStaticMeshActor>(Location, FRotator::ZeroRotator, SpawnParams);
	if (NewRoom)
	{
		NewRoom->SetStaticMesh(RoomMesh);
		// Scale the mesh to match the RoomSize (assuming the source mesh is 100x100x100)
		const float ScaleFactor = RoomSize / 100.f;
		NewRoom->SetActorScale3D(FVector(ScaleFactor, ScaleFactor, ScaleFactor));
		SpawnedRooms.Add(NewRoom);
		OccupiedGridPositions.Add(FIntPoint(GridX, GridY));
	}
}

bool ACombatGameMode::IsPositionOccupied(int32 GridX, int32 GridY) const
{
	// Check if this grid position is already occupied
	return OccupiedGridPositions.Contains(FIntPoint(GridX, GridY));
}
