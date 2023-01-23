// Copyright Epic Games, Inc. All Rights Reserved.

using System;
using System.IO;
using UnrealBuildTool;

public class Project_LD : ModuleRules
{
	public Project_LD(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange
           (
               new string[]
               {
                        Path.Combine(ModuleDirectory, "Public"),
                        Path.Combine(ModuleDirectory, "Public/Framework"),
                        Path.Combine(ModuleDirectory, "Public/Widget"),
               }
           );

        PrivateIncludePaths.AddRange
            (
                new string[]
                {
                            Path.Combine(ModuleDirectory, "Private"),
                }
            );

        PublicDependencyModuleNames.AddRange
            (
                new string[]
                {
                            "Core",
                            "CoreUObject",
                            "Engine",
                            "InputCore",
                            "Sockets",
                            "Networking",
                            "OnlineSubsystem",
                            "OnlineSubsystemUtils",
                            "HeadMountedDisplay",
                            "NavigationSystem",
                            "AIModule"
                }
            );

        PrivateDependencyModuleNames.AddRange
            (
                new string[]
                {
                            "Slate",
                            "SlateCore",
                }
            );

        DynamicallyLoadedModuleNames.AddRange
            (
                new string[]
                {
                    // ... add any modules that your module loads dynamically here ...
                }
            );
	}
}
