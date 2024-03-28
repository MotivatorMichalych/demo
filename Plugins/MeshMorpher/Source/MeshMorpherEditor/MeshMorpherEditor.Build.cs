// Copyright 2017-2024 SC Pug Life Studio S.R.L. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class MeshMorpherEditor : ModuleRules
{

    private string ModulePath
    {
        get { return ModuleDirectory; }
    }

    public MeshMorpherEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        bUsePrecompiled = true;
        PublicIncludePaths.Add(Path.Combine(ModulePath, "Public"));
        string EnginePath = Path.GetFullPath(Target.RelativeEnginePath);
        PrivateIncludePaths.Add(Path.Combine(EnginePath, "Source/Runtime/Slate/Private"));

        PrivateIncludePaths.AddRange(
            new string[] {
				// ... add other private include paths required here ...
			}
            );


        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core", "HTTP", "AnimGraph"
                // ... add other public dependencies that you statically link with here ...
			}
            );


        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "UnrealEd",
                "EditorStyle",
                "RenderCore",
                "RHI",
                "MeshConversion",
                "ToolMenus",
                "InputCore",
                "LevelEditor",
                "ApplicationCore",
                "Projects",
                "MeshDescription",
                "StaticMeshDescription",
                "SkeletalMeshDescription",
                "MeshDescriptionOperations",
                "ViewportInteraction",
                "UMG",
                "AssetTools",
                "AssetRegistry",
                "PropertyEditor",
                "Settings",
                "InteractiveToolsFramework",
                "EditorInteractiveToolsFramework",
                "MeshModelingTools",
                "MeshModelingToolsEditorOnly",
                "ViewportInteraction",
                "AdvancedPreviewScene",
                "ModelingComponents",
                "FBX",
                "AnimationCore",
                "AnimGraph", 
                "AnimGraphRuntime",
                "BlueprintGraph",                 
                "MeshMorpherCore",
                "MeshUtilities",
                "ContentBrowser",
                "Settings",
                "HTTP",
                "Json",
                "DynamicMesh",
                "EditorFramework",
                "GeometryCore",
                "GeometryFramework",
                "Eigen",
                "Persona", 
                "EditorWidgets", "ControlRig", "ControlRigDeveloper", "RigLogicModule", "RigLogicLib", "CommonMenuExtensions"
                // ... add private dependencies that you statically link with here ...	
			}
            );
 
        DynamicallyLoadedModuleNames.AddRange(
            new string[]
            {
				// ... add any modules that your module loads dynamically here ...
			}
            );
    }
}
