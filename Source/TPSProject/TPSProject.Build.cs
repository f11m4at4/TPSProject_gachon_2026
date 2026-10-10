// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TPSProject : ModuleRules
{
	public TPSProject(ReadOnlyTargetRules Target) : base(Target)
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
			"TPSProject",
			"TPSProject/Variant_Platforming",
			"TPSProject/Variant_Platforming/Animation",
			"TPSProject/Variant_Combat",
			"TPSProject/Variant_Combat/AI",
			"TPSProject/Variant_Combat/Animation",
			"TPSProject/Variant_Combat/Gameplay",
			"TPSProject/Variant_Combat/Interfaces",
			"TPSProject/Variant_Combat/UI",
			"TPSProject/Variant_SideScrolling",
			"TPSProject/Variant_SideScrolling/AI",
			"TPSProject/Variant_SideScrolling/Gameplay",
			"TPSProject/Variant_SideScrolling/Interfaces",
			"TPSProject/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
