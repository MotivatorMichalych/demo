// Copyright 2017-2024 SC Pug Life Studio S.R.L. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class MeshMorpherRuntime : ModuleRules
{
	
	public MeshMorpherRuntime(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        bUsePrecompiled = true;
		PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Public"));
        PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core", "AnimGraphRuntime"
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"InputCore",
				"SlateCore",
				"RenderCore",
				"RHI",
				"MeshDescription",
				"StaticMeshDescription",
				"GeometryCore",
				"GeometryFramework",
				"ModelingComponents",
				"MeshConversion",
				"InteractiveToolsFramework",
				"DynamicMesh",
				"AnimGraphRuntime",
				"HTTP",
				"Json", "ClothingSystemRuntimeCommon",
				// ... add private dependencies that you statically link with here ...	
			}
			);

		if (Target.Type == TargetRules.TargetType.Editor)
			PrivateDependencyModuleNames.AddRange(
				new[]
				{
					"UnrealEd",
					"DesktopPlatform"
				}
			);

		BuildVersion Version;
		var File = BuildVersion.GetDefaultFileName();
		if(BuildVersion.TryRead(File, out Version))
		{
			if(Version.MajorVersion == 5 && Version.MinorVersion >= 1)
			{
				if (Target.Platform == UnrealTargetPlatform.Win64)
				{
					if (Target.Type == TargetType.Editor)
					{
						AddEngineThirdPartyPrivateStaticDependencies(Target,
							"FBX"
						);
					}
					else
					{
						string FBXSDKDir = Target.UEThirdPartySourceDirectory + "FBX/2020.2/";
						PublicSystemIncludePaths.AddRange(
							new string[]
							{
								FBXSDKDir + "include",
								FBXSDKDir + "include/fbxsdk",
							}
						);

						string FBXDLLDir = Target.UEThirdPartyBinariesDirectory + "FBX/2020.2/";

						string FBxLibPath = FBXSDKDir + "lib/vs2017/";
						string FBxDllPath = FBXDLLDir + "Win64/libfbxsdk.dll";

						FBxLibPath += "x64/release/";						
						
						PublicAdditionalLibraries.Add(FBxLibPath + "libfbxsdk.lib");

						// We are using DLL versions of the FBX libraries
						PublicDefinitions.Add("FBXSDK_SHARED");

						RuntimeDependencies.Add("$(TargetOutputDir)/libfbxsdk.dll", FBxDllPath);
					}
				}
				else
				{
					AddEngineThirdPartyPrivateStaticDependencies(Target,
						"FBX"
					);	
				}
			} else if (Version.MajorVersion == 5 && Version.MinorVersion == 0)
			{
				AddEngineThirdPartyPrivateStaticDependencies(Target,
					"FBX"
				);
			}
			else
			{
				throw new BuildException("Invalid engine version.");
			}
		} else
		{
			throw new BuildException("Couldn't read engine version.");
		}
		
		

	}
}
