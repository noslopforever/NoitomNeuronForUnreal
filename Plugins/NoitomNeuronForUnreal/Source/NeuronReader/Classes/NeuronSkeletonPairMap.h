#pragma once

#include "Animation/BoneControllers/AnimNode_SkeletalControlBase.h"
#include "AnimGraphNode_SkeletalControlBase.h"
#include "NeuronSkeletonPairMap.generated.h"


/** Neuron skeleton pair
*/
USTRUCT()
struct NEURONREADER_API FNeuronSkeletonPair
{
	GENERATED_USTRUCT_BODY()
public:

	/** Neuron bone. **/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = NeuronSkeletonPair)
	TEnumAsByte<ENeuronBones::Type> NeuronBone;

	/** Name of bone to control. This is the main bone chain to modify from. **/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = NeuronSkeletonPair)
	FBoneReference TargetBoneReference;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = NeuronSkeletonPair)
	FVector TranslationModifier;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = NeuronSkeletonPair)
	FRotator RotationModifier;

};


UENUM()
enum ETestCommand
{
	Identity,
	Neuron,
	This,
	InvNeuron,
	InvThis,
};

/** AnimNode : Neuron skeleton pair
*	Similar as AnimNode_WheelHandler
*/
USTRUCT()
struct NEURONREADER_API FAnimNode_AutoNeuronSkeletonMatch : public FAnimNode_SkeletalControlBase
{
	GENERATED_USTRUCT_BODY()
public:

	/** Neuron skeleton pairs
	*/
	UPROPERTY(EditAnywhere, Category = SkeletalControl)
	TArray<FNeuronSkeletonPair> Pairs;

	UPROPERTY(EditAnywhere, Category = SkeletalControl)
	bool IgnoreBoneDisplacement;

	UPROPERTY(EditAnywhere, Category = SkeletalControl)
	bool IgnoreRootDisplacement;

public:

	FAnimNode_AutoNeuronSkeletonMatch();

	// FAnimNode_Base interface
	virtual void GatherDebugData(FNodeDebugData& DebugData) override;
	// End of FAnimNode_Base interface

	// FAnimNode_SkeletalControlBase interface
	virtual void EvaluateComponentSpace(FComponentSpacePoseContext& Output) override;
	//virtual void EvaluateBoneTransforms(USkeletalMeshComponent* SkelComp, const FBoneContainer& RequiredBones, FA2CSPose& MeshBases, TArray<FBoneTransform>& OutBoneTransforms) override;
	virtual bool IsValidToEvaluate(const USkeleton* Skeleton, const FBoneContainer& RequiredBones) override;
	// End of FAnimNode_SkeletalControlBase interface

private:
	// FAnimNode_SkeletalControlBase interface
	virtual void InitializeBoneReferences(const FBoneContainer& RequiredBones) override;
	// End of FAnimNode_SkeletalControlBase interface
};


UCLASS(MinimalAPI, meta = (Keywords = "Neuron Noitom"))
class UAnimGraphNode_AutoNeuronSkeletonMatch : public UAnimGraphNode_SkeletalControlBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(EditAnywhere, Category = Settings)
	FAnimNode_AutoNeuronSkeletonMatch Node;

public:
	// UEdGraphNode interface
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FText GetTooltipText() const override;
	// End of UEdGraphNode interface

protected:
	// UAnimGraphNode_SkeletalControlBase interface
	virtual FText GetControllerDescription() const override;
	// End of UAnimGraphNode_SkeletalControlBase interface

};

