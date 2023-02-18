// Copyright Epic Games, Inc. All Rights Reserved.

using System;
using System.IO;
using UnrealBuildTool;

public class ProtobufLibrary : ModuleRules
{
	public ProtobufLibrary(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        string ThirdPartyDirectory = Path.Combine(ModuleDirectory, "../ThirdParty/");
        string ProtobufIncludePath = Path.Combine(ThirdPartyDirectory, "ProtobufLibrary/include");
        string ProtobufLibraryPath = Path.Combine(ThirdPartyDirectory, "ProtobufLibrary/");

        PublicDefinitions.Add("WITH_PROTOBUFLIBRARY=1");

        Console.WriteLine("Configuration = " + Target.Configuration + "Platform = " + Target.Platform);

        if (true == IsDebug(Target.Configuration))
        {
            ProtobufLibraryPath += "debug/lib/";
            PublicAdditionalLibraries.Add(Path.Combine(ProtobufLibraryPath, "libprotobufd.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ProtobufLibraryPath, "libprotobuf-lited.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ProtobufLibraryPath, "libprotocd.lib"));
        }
        else
        {
            ProtobufLibraryPath += "release/lib/";
            PublicAdditionalLibraries.Add(Path.Combine(ProtobufLibraryPath, "libprotobuf.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ProtobufLibraryPath, "libprotobuf-lite.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ProtobufLibraryPath, "libprotoc.lib"));
        }

        PublicSystemIncludePaths.Add(ProtobufIncludePath);

        PublicDependencyModuleNames.AddRange
            (
                new string[]
                {
                            "Core",
                }
            );

        PublicDefinitions.AddRange(
            new string[]
            {
                "GOOGLE_PROTOBUF_NO_RTTI=1",
                "GOOGLE_PROTOBUF_USE_UNALIGNED=0",
                "_CRT_SECURE_NO_WARNINGS"
            });

        bEnableUndefinedIdentifierWarnings = false;
        bEnableExceptions = true;
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
