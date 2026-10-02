// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SimpleDungeonCrawler : ModuleRules
{
	public SimpleDungeonCrawler(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"SimpleDungeonCrawler",
			"SimpleDungeonCrawler/Variant_Platforming",
			"SimpleDungeonCrawler/Variant_Platforming/Animation",
			"SimpleDungeonCrawler/Variant_Combat",
			"SimpleDungeonCrawler/Variant_Combat/AI",
			"SimpleDungeonCrawler/Variant_Combat/Animation",
			"SimpleDungeonCrawler/Variant_Combat/Gameplay",
			"SimpleDungeonCrawler/Variant_Combat/Interfaces",
			"SimpleDungeonCrawler/Variant_Combat/UI",
			"SimpleDungeonCrawler/Variant_SideScrolling",
			"SimpleDungeonCrawler/Variant_SideScrolling/AI",
			"SimpleDungeonCrawler/Variant_SideScrolling/Gameplay",
			"SimpleDungeonCrawler/Variant_SideScrolling/Interfaces",
			"SimpleDungeonCrawler/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
