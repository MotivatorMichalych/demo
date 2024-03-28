// Copyright 2017-2024 SC Pug Life Studio S.R.L. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Animation/MorphTarget.h"
#include "StandaloneMorphTarget.generated.h"

class USkeletalMesh;

DECLARE_STATS_GROUP(TEXT("MeshMorpherStandaloneMorphTarget"), STATGROUP_MeshMorpherStandaloneMorphTarget, STATCAT_MeshMorpher);
DECLARE_CYCLE_STAT(TEXT("MeshMorpherStandaloneMorphTarget_SetWeight"), STAT_MeshMorpherStandaloneMorphTarget_SetWeight, STATGROUP_MeshMorpherStandaloneMorphTarget);
DECLARE_CYCLE_STAT(TEXT("MeshMorpherStandaloneMorphTarget_UpdateRHI"), STAT_MeshMorpherStandaloneMorphTarget_UpdateRHI, STATGROUP_MeshMorpherStandaloneMorphTarget);

UCLASS(hidecategories = Object, BlueprintType)
class MESHMORPHERRUNTIME_API UStandaloneMorphTarget : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(AssetRegistrySearchable)
		USkeletalMesh* SkeletalMesh;

	UPROPERTY()
		FName MorphTargetName;

	UPROPERTY(Transient)
		float Weight = 0.0f;
	
	TArray<TArray<FMorphTargetDelta>> Deltas;
public:
	/**
	* Get the Skeletal Mesh used by this Standalone Morph Target
	*/  	
	UFUNCTION(BlueprintPure, Category = "Standalone Morph Target")
		USkeletalMesh* GetSkeletalMesh() const;

	/**
	* Get the amount of deltas for specified LOD
	* @return Morph Target Name
	*/  	
	UFUNCTION(BlueprintPure, Category = "Standalone Morph Target")
		int32 GetDeltaNum(const int32 LOD) const;

	/**
	* Get the Standalone Morph Target Name
	* @return Morph Target Name
	*/  	
	UFUNCTION(BlueprintPure, Category = "Standalone Morph Target")
		FName GetMorphTargetName() const;

	/**
	* Set a new Standalone Morph Target name
	*/  	
	UFUNCTION(BlueprintCallable, Category = "Standalone Morph Target")
		void SetMorphTargetName(const FName& NewName);

	/**
	* Get the amount of LODs used by this Standalone Morph Target
	* @return LOD Count
	*/  
	UFUNCTION(BlueprintPure, Category = "Standalone Morph Target")
		int32 GetDeltaLODs() const;

	/**
	* Get the Delta at index for the specified LOD
	* @return True if found
	*/  	
	UFUNCTION(BlueprintPure, Category = "Standalone Morph Target")
		bool GetDelta(const int32 LOD, const int32 Index, FVector& Position, FVector& Normal, int32& SourceIndex) const;

	/**
	* Returns the weight of the Standalone Morph Target
	* @return Weight
	*/  	
	UFUNCTION(BlueprintPure, Category = "Standalone Morph Target")
		float GetWeight() const;

	/**
	* Bakes the Standalone Morph Target in Skeletal Mesh render data
	* @param NewWeight		Set the weight of this Standalone Morph Target
	*/  		
	UFUNCTION(BlueprintCallable, Category = "Standalone Morph Target")
		void SetWeight(float NewWeight);
	
protected:	
	virtual void Serialize(FArchive& Ar) override
	{
		Super::Serialize( Ar );
		Ar << Deltas;	
	}
};