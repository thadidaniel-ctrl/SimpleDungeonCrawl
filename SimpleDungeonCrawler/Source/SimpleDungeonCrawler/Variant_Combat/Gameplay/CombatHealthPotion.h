// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CombatHealthPotion.generated.h"

class USphereComponent;

/**
 *  A health potion that heals the player who picks it up.
 */
UCLASS()
class ACombatHealthPotion : public AActor
{
	GENERATED_BODY()
	
public:	
	/** Constructor */
	ACombatHealthPotion();

protected:
	/** Called when the game starts or when spawned */
	virtual void BeginPlay() override;

	/** Handles overlap events */
	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/** The healing amount to apply when picked up */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Potion", meta=(ClampMin="0.1", UIMin="0.1", UIMax="10.0"))
	float HealingAmount = 1.0f;

	/** The sphere component used for overlap detection */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	USphereComponent* Sphere;

	/** Has this potion already been consumed? */
	bool bIsConsumed = false;
};
