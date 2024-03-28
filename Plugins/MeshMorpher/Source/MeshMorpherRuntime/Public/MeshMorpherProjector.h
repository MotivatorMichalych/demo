// Copyright 2017-2024 SC Pug Life Studio S.R.L. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "DynamicMesh/DynamicMesh3.h"
#include "Animation/MorphTarget.h"

DECLARE_STATS_GROUP(TEXT("MeshMorpherWrapper"), STATGROUP_MeshMorpherWrapper, STATCAT_MeshMorpher);
DECLARE_CYCLE_STAT(TEXT("MeshMorpherWrapper_Initialize"), STAT_MeshMorpherWrapper_Initialize, STATGROUP_MeshMorpherWrapper);
DECLARE_CYCLE_STAT(TEXT("MeshMorpherWrapper_RecalculateNormals"), STAT_MeshMorpherWrapper_RecalculateNormals, STATGROUP_MeshMorpherWrapper);
DECLARE_CYCLE_STAT(TEXT("MeshMorpherWrapper_IdenticalCheck"), STAT_MeshMorpherWrapper_IdenticalCheck, STATGROUP_MeshMorpherWrapper);
DECLARE_CYCLE_STAT(TEXT("MeshMorpherWrapper_SmoothDeltas"), STAT_MeshMorpherWrapper_SmoothDeltas, STATGROUP_MeshMorpherWrapper);
DECLARE_CYCLE_STAT(TEXT("MeshMorpherWrapper_ApplyToIdenticalVertices"), STAT_MeshMorpherWrapper_ApplyToIdenticalVertices, STATGROUP_MeshMorpherWrapper);
DECLARE_CYCLE_STAT(TEXT("MeshMorpherWrapper_CreateDeltasForVertexPairs"), STAT_MeshMorpherWrapper_CreateDeltasForVertexPairs, STATGROUP_MeshMorpherWrapper);
DECLARE_CYCLE_STAT(TEXT("MeshMorpherWrapper_CalculateDynamicMeshesForTransfer"), STAT_MeshMorpherWrapper_CalculateDynamicMeshesForTransfer, STATGROUP_MeshMorpherWrapper);

using namespace UE::Geometry;

struct MESHMORPHERRUNTIME_API FMeshMorpherWrapPair
{
	int32 SourceIndex = INDEX_NONE;
	int32 TargetIndex = INDEX_NONE;

	FMeshMorpherWrapPair()
	{
		
	}

	FMeshMorpherWrapPair(const int32& InTargetIndex, const int32& InSourceIndex)
	{
		TargetIndex = InTargetIndex;
		SourceIndex = InSourceIndex;
	}
};

UENUM(BlueprintType)
enum class EMeshMorpherSmoothTypes : uint8
{
	/** Preserve UV Flow */
	PreserveUVFlow = 0 UMETA(DisplayName="Preserve UV Flow"),	
	/** Uniform weights, produces regular mesh and fastest convergence */
	Uniform = 1,		
	/** Delta Smoothing algorithm */
	Delta = 2  	
};

class MESHMORPHERRUNTIME_API FMeshMorpherProjector
{

public:
	TUniquePtr<FDynamicMesh3> SourceMesh;
	TUniquePtr<FDynamicMesh3> TargetMesh;
	double VertexThreshold = 20.0;
	double NormalIncompatibilityThreshold = 0.5;
	bool bMatchMaterialIDs = false;
	double SmoothStrength = 0.1;
	int32 SmoothIterations = 1;
	EMeshMorpherSmoothTypes SmoothType = EMeshMorpherSmoothTypes::PreserveUVFlow;
public:
	FMeshMorpherProjector(const FDynamicMesh3& TargetDynamicMesh, const FDynamicMesh3& SourceDynamicMesh);
	static void RecalculateMeshNormals(FDynamicMesh3* Mesh);
	static bool IsDynamicMeshIdentical(FDynamicMesh3* DynamicMeshA, FDynamicMesh3* DynamicMeshB);
	bool ProjectDeltas(const TArray<FMorphTargetDelta>& InDeltas, const bool bCheckMeshesIdentical, TArray<FMorphTargetDelta>& OutDeltas) const;
	bool ProjectDeltas(const TArray<FMorphTargetDelta>& InDeltas, const bool bCheckMeshesIdentical, TArray<TSet<int32>>& VerticesSets, TArray<FMorphTargetDelta>& OutDeltas) const;
protected:
	void ComputeDeltaProjection(FDynamicMesh3* SourceDynamicMesh, FDynamicMesh3 TargetDynamicMesh,
	                            const TArray<FMorphTargetDelta>& InDeltas, TArray<FMorphTargetDelta>& OutDeltas) const;
	void ComputeDeltaProjection(FDynamicMesh3* SourceDynamicMesh, FDynamicMesh3 TargetDynamicMesh,
	                            const TArray<FMorphTargetDelta>& InDeltas, TArray<TSet<int32>>& VerticesSets,
	                            TArray<FMorphTargetDelta>& OutDeltas) const;
	static FVector3d UniformSmooth(const FDynamicMesh3& mesh, int vID, double t);
	static FVector3d PreserveUVFlowSmooth(const FDynamicMesh3& mesh, int vID, double t);
	void GetSmoothDeltas(FDynamicMesh3*, TArray<FMorphTargetDelta>& Deltas) const;
	void ApplyDeltasToIdenticalVertices(const TArray<TSet<int32>>& VerticesSets, TArray<FMorphTargetDelta>& Deltas) const;
	void CreateDeltasForVertexPairs(const TArray<FMeshMorpherWrapPair>& VertexPairs, const TArray<FMorphTargetDelta>& BaseDeltas, TArray<FMorphTargetDelta>& OutDeltas) const;
	void CalculateDynamicMeshesForTransfer(FDynamicMesh3* SourceDynamicMesh, FDynamicMesh3* TargetDynamicMesh, TArray<TSet<int32>>& VerticesSets, TArray<FMeshMorpherWrapPair>& VertexPairs) const;
};
