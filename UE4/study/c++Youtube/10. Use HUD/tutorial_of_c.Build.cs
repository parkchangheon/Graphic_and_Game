// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class tutorial_of_c : ModuleRules
{
	public tutorial_of_c(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay","UMG" });

		PrivateDependencyModuleNames.AddRange(new string[] { "Slate","SlateCore" });

	}
}
