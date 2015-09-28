#include "NeuronReaderModulePCH.h"
#include "NeuronSkeletonPairMap.h"


#define LOCTEXT_NAMESPACE "AnimGraph_LookAt"

//------------------------------------------------------------------------
FAnimNode_NeuronSkeletonPair::FAnimNode_NeuronSkeletonPair()
	: IgnoreBoneDisplacement(true)
	, IgnoreRootDisplacement(false)
{
}

//------------------------------------------------------------------------
void FAnimNode_NeuronSkeletonPair::GatherDebugData(FNodeDebugData& DebugData)
{
	FString DebugLine = DebugData.GetNodeName(this);

	//DebugLine += "(";
	//AddDebugNodeData(DebugLine);
	//if (LookAtBone.BoneIndex != INDEX_NONE)
	//{
	//	DebugLine += FString::Printf(TEXT(" Target: %s, Look At Bone: %s, Location : %s)"), *BoneToModify.BoneName.ToString(), *LookAtBone.BoneName.ToString(), *CurrentLookAtLocation.ToString());
	//}
	//else
	//{
	//	DebugLine += FString::Printf(TEXT(" Target: %s, Look At Location : %s, Location : %s)"), *BoneToModify.BoneName.ToString(), *LookAtLocation.ToString(), *CurrentLookAtLocation.ToString());
	//}

	//DebugData.AddDebugItem(DebugLine);

	ComponentPose.GatherDebugData(DebugData);
}

//------------------------------------------------------------------------
void FAnimNode_NeuronSkeletonPair::EvaluateComponentSpace(FComponentSpacePoseContext& Output)
{
	// modified from FAnimNode_SkeletalControlBase::EvaluateComponentSpace

	// Evaluate the input
	ComponentPose.EvaluateComponentSpace(Output);

	// Apply the skeletal control if it's valid
	const float ActualAlpha = AlphaScaleBias.ApplyTo(Alpha);
	if ((ActualAlpha >= ZERO_ANIMWEIGHT_THRESH) && IsValidToEvaluate(Output.AnimInstance->CurrentSkeleton, Output.AnimInstance->RequiredBones))
	{
		USkeletalMeshComponent* Component = Output.AnimInstance->GetSkelMeshComponent();

#if WITH_EDITORONLY_DATA
		// save current pose before applying skeletal control to compute the exact gizmo location in AnimGraphNode
		ForwardedPose = Output.Pose;
#endif // #if WITH_EDITORONLY_DATA

		// begin region EvaluateBoneTransforms
		{
			USkeletalMeshComponent* SkelComp = Component;
			FBoneContainer& RequiredBones = Output.AnimInstance->RequiredBones;
			FA2CSPose& MeshBases = Output.Pose;
			// Must used with NeuronAnimInstance
			// TODO by noslopforever @ 2015-9-28
			//		Use interface instead?
			UNeuronAnimInstance* neuronAnimInst = Cast<UNeuronAnimInstance>(SkelComp->GetAnimInstance());
			if (neuronAnimInst == nullptr) {
				return;
			}

			TArray<FBoneTransform> BoneTransforms;
			BoneTransforms.AddZeroed(1);
			for (const auto & pair : Pairs)
			{
				if (!pair.TargetBoneReference.IsValid(RequiredBones)) {
					continue;
				}

				// get data from Neuron
				bool isValid = false;
				FVector trans = FVector::ZeroVector;
				FRotator rot = FRotator::ZeroRotator;
				neuronAnimInst->GetBoneData(pair.NeuronBone, isValid, trans, rot);

				if (!isValid) {
					continue;
				}
				// the way we apply transform is same as FMatrix or FTransform
				// we apply scale first, and rotation, and translation
				// if you'd like to translate first, you'll need two nodes that first node does translate and second nodes to rotate. 
				FTransform NewBoneTM = MeshBases.GetComponentSpaceTransform(pair.TargetBoneReference.BoneIndex);

				FAnimationRuntime::ConvertCSTransformToBoneSpace(SkelComp, MeshBases, NewBoneTM, pair.TargetBoneReference.BoneIndex, BCS_BoneSpace);

				// Apply rotation offset
				const FQuat rotation(rot);
				NewBoneTM.SetRotation(rotation);
				// Apply translations if needed
				if (pair.NeuronBone == ENeuronBones::Hips)
				{
					if (!IgnoreRootDisplacement) {
						NewBoneTM.SetTranslation(trans);
					}
				}
				else
				{
					if (!IgnoreBoneDisplacement) {
						NewBoneTM.SetTranslation(trans);
					}
				}

				// Convert back to Component Space.
				FAnimationRuntime::ConvertBoneSpaceTransformToCS(SkelComp, MeshBases, NewBoneTM, pair.TargetBoneReference.BoneIndex, BCS_BoneSpace);

				// add back to it
				BoneTransforms[0] = FBoneTransform(pair.TargetBoneReference.BoneIndex, NewBoneTM);
				checkSlow(!BoneTransforms[0].Transform.ContainsNaN());

				// 
				if (BoneTransforms.Num() > 0)
				{
					const float BlendWeight = FMath::Clamp<float>(ActualAlpha, 0.f, 1.f);
					Output.Pose.LocalBlendCSBoneTransforms(BoneTransforms, BlendWeight);
				}
			} // end for pairs

		} // end region EvaluateBoneTransforms

	} // end Alpha check
}

//------------------------------------------------------------------------
bool FAnimNode_NeuronSkeletonPair::IsValidToEvaluate(const USkeleton* Skeleton, const FBoneContainer& RequiredBones)
{
	// if both bones are valid
	for (const auto & pair : Pairs)
	{
		// if one of them is valid
		if (pair.TargetBoneReference.IsValid(RequiredBones) == true)
		{
			return true;
		}
	}

	return false;
}

//------------------------------------------------------------------------
void FAnimNode_NeuronSkeletonPair::InitializeBoneReferences(const FBoneContainer& RequiredBones)
{
	// for each configurated bone in Pairs
	for (int32 i = 0; i < Pairs.Num(); ++i)
	{
		Pairs[i].TargetBoneReference.Initialize(RequiredBones);
	}
	// sort by bone indices
	Pairs.Sort([](FNeuronSkeletonPair L, FNeuronSkeletonPair R) { return L.TargetBoneReference.BoneIndex < R.TargetBoneReference.BoneIndex; });
}

//------------------------------------------------------------------------



//------------------------------------------------------------------------
UAnimGraphNode_NeuronSkeletonPair::UAnimGraphNode_NeuronSkeletonPair(const FObjectInitializer& PCIP)
	:Super(PCIP)
{
}

//------------------------------------------------------------------------
FText UAnimGraphNode_NeuronSkeletonPair::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return GetControllerDescription();
}

//------------------------------------------------------------------------
FText UAnimGraphNode_NeuronSkeletonPair::GetTooltipText() const
{
	return LOCTEXT("AnimGraphNode_NeuronSkeletonPair_Tooltip", "This node allow a skeleton seems similar to which shown in Neuron skeleton.");
}

//------------------------------------------------------------------------
FText UAnimGraphNode_NeuronSkeletonPair::GetControllerDescription() const
{
	return LOCTEXT("NeuronSkeletonPair", "Do Neuron Skeleton");
}

//------------------------------------------------------------------------

#undef LOCTEXT_NAMESPACE
