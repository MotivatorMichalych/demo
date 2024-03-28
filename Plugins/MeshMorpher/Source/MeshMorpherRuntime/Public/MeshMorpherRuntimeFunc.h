// Copyright 2017-2024 SC Pug Life Studio S.R.L. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/SkeletalMesh.h"
#include "Rendering/SkeletalMeshRenderData.h"
#include "DynamicMesh/DynamicMesh3.h"
#include "MeshMorpherProjector.h"
#include "Animation/MorphTarget.h"
#include "SkeletalRenderPublic.h"
#include "Engine/EngineTypes.h"
#if ENGINE_MINOR_VERSION >= 2
#include "Engine/SkinnedAssetCommon.h"
#endif
DECLARE_STATS_GROUP(TEXT("MeshMorpherRuntimeTools"), STATGROUP_MeshMorpherRuntimeTools, STATCAT_MeshMorpher);

DECLARE_CYCLE_STAT(TEXT("MeshMorpherRuntimeTools_ExportOBJ"), STAT_MeshMorpherRuntimeTools_ExportOBJ, STATGROUP_MeshMorpherRuntimeTools);
DECLARE_CYCLE_STAT(TEXT("MeshMorpherRuntimeTools_ExportOBJWelded"), STAT_MeshMorpherRuntimeTools_ExportOBJWelded, STATGROUP_MeshMorpherRuntimeTools);

DECLARE_CYCLE_STAT(TEXT("MeshMorpherRuntimeTools_UpdateImportFilesTransform"), STAT_MeshMorpherRuntimeTools_UpdateImportFileTransform, STATGROUP_MeshMorpherRuntimeTools);

DECLARE_CYCLE_STAT(TEXT("MeshMorpherRuntimeTools_MorphTargetPopulateDeltas"), STAT_MeshMorpherRuntimeTools_MorphTargetPopulateDeltas, STATGROUP_MeshMorpherRuntimeTools);
DECLARE_CYCLE_STAT(TEXT("MeshMorpherRuntimeTools_RecreateMorphTargetVertexInfoBuffer"), STAT_MeshMorpherRuntimeTools_RecreateMorphTargetVertexInfoBuffer, STATGROUP_MeshMorpherRuntimeTools);


DECLARE_STATS_GROUP(TEXT("MeshMorpherRuntime"), STATGROUP_MeshMorpherRuntime, STATCAT_MeshMorpher);
DECLARE_CYCLE_STAT(TEXT("MeshMorpherRuntime_GetMorphDeltas"), STAT_MeshMorpherRuntime_GetMorphDeltas, STATGROUP_MeshMorpherRuntime);
DECLARE_CYCLE_STAT(TEXT("MeshMorpherRuntime_ApplyDeltasDynamicMesh"), STAT_MeshMorpherRuntime_ApplyDeltasDynamicMesh, STATGROUP_MeshMorpherRuntime);
DECLARE_CYCLE_STAT(TEXT("MeshMorpherRuntime_SkeletalMeshToDynamicMesh"), STAT_MeshMorpherRuntime_SkeletalMeshToDynamicMesh, STATGROUP_MeshMorpherRuntime);
DECLARE_CYCLE_STAT(TEXT("MeshMorpherRuntime_GetUsedMaterials"), STAT_MeshMorpherRuntime_GetUsedMaterials, STATGROUP_MeshMorpherRuntime);

class UStandaloneMorphTarget;
class UMeshMorpherBoneSnapshot;

using namespace UE::Geometry;

struct FFBXTransform
{
public:
	FVector Position = FVector(0, 0, 0);	
	FVector Rotation = FVector(0, 0, 0);
	FVector Scale = FVector::OneVector;
};


struct FFBXInput
{
public:

	/**
	* Path to the FBX File.
	*/
	FFilePath File;

	/**
	* T0 Pose
	*/
	bool bUseT0 = true;
	
	/**
	* Coordinate System. 0 right, 1 Left
	*/
	int32 FrontCoordinateSystem = 0;
	
	/**
	* Front Axis, 0 X, 1 Y, 2 Z
	*/
	int32 FrontAxis = 1;

	/**
	* Up Axis, 0 X, 1 Y, 2 Z
	*/
	int32 UpAxis = 2;	

	/**
	* Transform
	*/
	FFBXTransform Transform;
};	


class MESHMORPHERRUNTIME_API FMeshMorpherRuntimeFunc
{
public:
	static void InvalidateCachedBounds(USkeletalMeshComponent* SkeletalMeshComponent);
	static USceneComponent* CreateComponent(UObject* Outer, TSubclassOf<USceneComponent> Class);
	static void DestroyComponent(USceneComponent* Component);
	static UMorphTarget* FindMorphTarget(USkeletalMesh* SkeletalMesh, FName Name);
	static void GetMorphTargetsNames(USkeletalMesh* SkeletalMesh, TArray<FName>& Names);
	static bool RemoveMorphTarget(USkeletalMesh* SkeletalMesh, FName Name);

	/**
	* Projects an array of Standalone Morph Targets on a Target Mesh
	* Standalone Morph Targets are projected on all Target Mesh LODs
	* Projection is multi-threaded but can be very intensive on meshes with big data.
	* @param Outer								Outer used for the resulted Standalone Morph Targets created during Projection.
	* @param MorphTargets						Standalone Morph Targets to project.
	* @param OutMorphTargets					Resulted Standalone Morph Targets.
	* @param TargetMesh							Target Mesh to project Standalone Morph Targets on.
	* @param MaxLOD								Maximum LOD Index on the Target Mesh to project the Morph Targets
	* @param VertexThreshold					Maximum Distance threshold between a vertex in the target mesh and a morphed vertex, at which it is considered to be compatible.
	* @param NormalIncompatibilityThreshold		Normal threshold at which a triangle is deemed as incompatible. This helps to avoid triangle flipping during Projection.
	* @param SmoothIterations					Smooth Iterations steps used to Smooth the resulted Projection Deltas.
	* @param SmoothStrength						Smooth Strength used to Smooth the resulted Projection Deltas.
	* @param SmoothType							Smooth Type used to Smooth the resulted Projection Deltas.
	*/  	
	static void ProjectStandaloneMorphTargets(UObject* Outer, const TArray<UStandaloneMorphTarget*>& MorphTargets,
		                                          TArray<UStandaloneMorphTarget*>& OutMorphTargets,
		                                          USkeletalMesh* TargetMesh, int32 MaxLOD = -1,
		                                          const double VertexThreshold = 20.0,
		                                          const double NormalIncompatibilityThreshold = 0.5,
		                                          const int32 SmoothIterations = 1, const double SmoothStrength = 0.1,
		                                          const EMeshMorpherSmoothTypes SmoothType = EMeshMorpherSmoothTypes::PreserveUVFlow);

	/**
	* Projects an array of Standalone Morph Targets on a Target Mesh
	* Standalone Morph Targets are projected on all Target Mesh LODs
	* Projection is multi-threaded but can be very intensive on meshes with big data.
	* @param MorphTargets						Standalone Morph Targets to project.
	* @param TargetMesh							Target Mesh to project Standalone Morph Targets on.
	* @param MaxLOD								Maximum LOD Index on the Target Mesh to project the Morph Targets
	* @param VertexThreshold					Maximum Distance threshold between a vertex in the target mesh and a morphed vertex, at which it is considered to be compatible.
	* @param NormalIncompatibilityThreshold		Normal threshold at which a triangle is deemed as incompatible. This helps to avoid triangle flipping during Projection.
	* @param SmoothIterations					Smooth Iterations steps used to Smooth the resulted Projection Deltas.
	* @param SmoothStrength						Smooth Strength used to Smooth the resulted Projection Deltas.
	* @param SmoothType							Smooth Type used to Smooth the resulted Projection Deltas.
	*/  	
	static bool ProjectStandaloneMorphTargetsToMorphTargets(const TArray<UStandaloneMorphTarget*>& MorphTargets,
		                                          USkeletalMesh* TargetMesh, int32 MaxLOD = -1,
		                                          const double VertexThreshold = 20.0,
		                                          const double NormalIncompatibilityThreshold = 0.5,
		                                          const int32 SmoothIterations = 1, const double SmoothStrength = 0.1,
		                                          const EMeshMorpherSmoothTypes SmoothType = EMeshMorpherSmoothTypes::PreserveUVFlow);	

	static void GetUsedMaterials(USkeletalMesh* SkeletalMesh, int32 LOD, TArray<FSkeletalMaterial>& OutMaterials);
	
	static bool SkeletalMeshToDynamicMesh_RenderData(USkeletalMesh* SkeletalMesh, FDynamicMesh3& IdenticalDynamicMesh, FDynamicMesh3* WeldedDynamicMesh = NULL, const TArray<FFinalSkinVertex>& FinalVertices = TArray<FFinalSkinVertex>(), double MergeVertexTolerance = FMathd::ZeroTolerance, double MergeSearchTolerance = 2 * FMathd::ZeroTolerance, bool OnlyUniquePairs = false, int32 LOD = 0);
	static UMorphTarget* FindMorphTarget(USkeletalMesh* Mesh, FString MorphTargetName);
	static UMorphTarget*  CreateMorphTargetObj(USkeletalMesh* Mesh, FString MorphTargetName, bool bInvalidateRenderData = true, bool bEditor = true);
	static void GetMorphDeltas(const FDynamicMesh3& Original, const FDynamicMesh3& Changed, TArray<FMorphTargetDelta>& Deltas, bool bCalculateNormals = true);
	static void ApplyDeltasToDynamicMesh(const TArray<FMorphTargetDelta>& Deltas, FDynamicMesh3& DynamicMesh);
	static USkeletalMesh* DuplicateSkeletalMesh(UObject* Outer, USkeletalMesh* SkeletalMesh, bool bNeedsCPUAccess);
};

