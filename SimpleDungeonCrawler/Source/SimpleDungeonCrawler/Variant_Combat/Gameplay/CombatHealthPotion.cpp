// Copyright Epic Games, Inc. All Rights Reserved.

#include "CombatHealthPotion.h"
#include "Components/SphereComponent.h"
#include "CombatCharacter.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"

ACombatHealthPotion::ACombatHealthPotion()
{
	PrimaryActorTick.bCanEverTick = false;

	// Create the sphere component for overlap detection
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(RootComponent);
	
	// Configure sphere for overlap events
	Sphere->SetSphereRadius(100.0f);
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Sphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	Sphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	
	// Add overlap event handler
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ACombatHealthPotion::OnSphereOverlap);
}

void ACombatHealthPotion::BeginPlay()
{
	Super::BeginPlay();
}

void ACombatHealthPotion::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Only process on server
	if (!HasAuthority())
	{
		return;
	}
	
	// Prevent multiple consumptions
	if (bIsConsumed)
	{
		return;
	}
	
	// Check if the overlapping actor is a player character
	if (ACharacter* OverlappedCharacter = Cast<ACharacter>(OtherActor))
	{
		// Check if it's a player-controlled character
		if (OverlappedCharacter->IsPlayerControlled())
		{
			// Cast to combat character to access healing functionality
			if (ACombatCharacter* CombatCharacter = Cast<ACombatCharacter>(OverlappedCharacter))
			{
				// Only heal if not at max HP
				if (CombatCharacter->CurrentHP < CombatCharacter->MaxHP)
				{
					// Apply healing through the combat damageable interface
					CombatCharacter->ApplyHealing(HealingAmount, this);
					
					// Mark as consumed
					bIsConsumed = true;
					
					// Destroy the potion - this will replicate to all clients
					Destroy();
				}
				// If at max HP, we don't consume the potion (save it for others)
			}
		}
	}
}
