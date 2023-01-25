// Copyright Epic Games, Inc. All Rights Reserved.

using System;
using System.IO;
using UnrealBuildTool;

public class Project_LD : ModuleRules
{
	public Project_LD(ReadOnlyTargetRules Target) : base(Target)
	{
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        CppStandard = CppStandardVersion.Cpp17;

        PublicIncludePaths.AddRange
           (
               new string[]
               {
                        Path.Combine(ModuleDirectory, "Public"),
                        Path.Combine(ModuleDirectory, "Public/Framework"),
                        Path.Combine(ModuleDirectory, "Public/Widget"),
                        Path.Combine(ModuleDirectory, "Public/Network"),
                        Path.Combine(ModuleDirectory, "Public/Protobuf/Handler"),
                        Path.Combine(ModuleDirectory, "Public/Protobuf/Packet"),
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
                            "AIModule",
                            "ProtobufLibrary"
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

        bEnableUndefinedIdentifierWarnings = false;
        bEnableExceptions = true;
    }
}
