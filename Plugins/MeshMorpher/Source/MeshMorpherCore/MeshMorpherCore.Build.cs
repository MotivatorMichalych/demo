// Copyright 2017-2024 SC Pug Life Studio S.R.L. All Rights Reserved.

using UnrealBuildTool;
using System.IO;


public class MeshMorpherCore : ModuleRules
{

    private string ModulePath
    {
        get { return ModuleDirectory; }
    }

    private string ThirdPartyPath
    {
        get { return Path.GetFullPath(Path.Combine(ModulePath, "../ThirdParty/")); }
    }

    public MeshMorpherCore(ReadOnlyTargetRules Target) : base(Target)
    {

        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        bUsePrecompiled = true;
        PublicIncludePaths.Add(Path.Combine(ModulePath, "Public"));

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                 "Core", "Engine"
            }
            );


        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
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
                "ModelingOperators",
                "MeshModelingToolsEditorOnly",
                "ViewportInteraction",
                "AdvancedPreviewScene",
                "ModelingComponents",
                "FBX",
                "AnimGraph", 
                "AnimGraphRuntime",
                "BlueprintGraph",                
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
                "DesktopPlatform",
                "ToolWidgets",
                "EditorWidgets", "ControlRig", "ControlRigDeveloper", "RigLogicModule", "RigLogicLib",
                "ClothingSystemRuntimeCommon", "SkeletalMeshUtilitiesCommon", "DeveloperSettings",
                "Imath", "ModelingComponentsEditorOnly", "ModelingOperators"
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
