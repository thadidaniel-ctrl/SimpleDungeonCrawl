// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CombatGameMode.generated.h"

/**
 *  Simple GameMode for a third person combat game
 */
UCLASS(abstract)
class ACombatGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	/** Constructor */
	ACombatGameMode();

protected:

	/** Initialization */
	virtual void BeginPlay() override;

	/** Assigns a PlayerStart to a specific player */
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

	/** Generates the procedural dungeon */
	void GenerateDungeon();

	/** Destroys all generated room actors */
	void ClearDungeon();

	/** Spawns a room at the given grid position */
	void SpawnRoomAt(int32 GridX, int32 GridY);

	/** Checks if a grid position is occupied */
	bool IsPositionOccupied(int32 GridX, int32 GridY) const;

	/** The size of each room in UU */
	UPROPERTY(EditDefaultsOnly, Category="Dungeon Generation")
	float RoomSize = 500.f;

	/** The maximum number of rooms to generate */
	UPROPERTY(EditDefaultsOnly, Category="Dungeon Generation")
	int32 MaxRooms = 8;

	/** The static mesh to use for rooms */
	UPROPERTY(EditDefaultsOnly, Category="Dungeon Generation")
	TObjectPtr<UStaticMesh> RoomMesh;

	/** List of spawned room actors */
	TArray<TObjectPtr<AStaticMeshActor>> SpawnedRooms;

	/** Set of occupied grid positions (to avoid overlaps) */
	TSet<FIntPoint> OccupiedGridPositions;

	/** Used to assign players to different PlayerStarts in the level */
	int32 CurrentPlayerStartAssignment = 0;
};
