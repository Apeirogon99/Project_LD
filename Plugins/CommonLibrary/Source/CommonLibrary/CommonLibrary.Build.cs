// Copyright Epic Games, Inc. All Rights Reserved.

using System;
using System.IO;
using UnrealBuildTool;

public class CommonLibrary : ModuleRules
{
	public CommonLibrary(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        string ThirdPartyDirectory = Path.Combine(ModuleDirectory, "../ThirdParty/");
        string CommonIncludePath = Path.Combine(ThirdPartyDirectory, "CommonLibrary/include");
        string CommonLibraryPath = Path.Combine(ThirdPartyDirectory, "CommonLibrary/");

        PublicDefinitions.Add("WITH_COMMONLIBRARY=1");

        Console.WriteLine("Start Common Plugin [" + Target.Configuration + "Platform = " + Target.Platform + "]");

        if (true == IsDebug(Target.Configuration))
        {
            CommonLibraryPath += "debug/lib/";
            PublicAdditionalLibraries.Add(Path.Combine(CommonLibraryPath, "CommonLibrary.lib"));
        }
        else
        {
            CommonLibraryPath += "release/lib/";
            PublicAdditionalLibraries.Add(Path.Combine(CommonLibraryPath, "CommonLibrary.lib"));
        }

        PublicSystemIncludePaths.Add(CommonIncludePath);

        PublicDependencyModuleNames.AddRange
        (
            new string[]
            {
                    "Core",
            }
        );


    }

    public bool IsDebug(UnrealTargetConfiguration Configuration)
    {
        if (Configuration == UnrealTargetConfiguration.Debug || Configuration == UnrealTargetConfiguration.DebugGame)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}
