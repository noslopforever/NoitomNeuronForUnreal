#include "NeuronReaderModulePCH.h"
#include "NeuronSkeletonPairMap.h"


#define LOCTEXT_NAMESPACE "AnimGraph_LookAt"


struct FNeuronEnumBonePair
{
public:
	FNeuronEnumBonePair()
	{
		EnumBoneReferencePair.AddUninitialized(ENeuronBones::NumOfBones);
		// TODO noslopforever @ 2015-10-1 : Need support for WideChar and Mac
#define __MAKE_PAIR_NEURON_BONE(ENUMTAG) EnumBoneReferencePair[ENeuronBones::ENUMTAG].BoneName = TEXT("Robot_" L## #ENUMTAG)
		__MAKE_PAIR_NEURON_BONE(Hips);
		__MAKE_PAIR_NEURON_BONE(RightUpLeg);
		__MAKE_PAIR_NEURON_BONE(RightLeg);
		__MAKE_PAIR_NEURON_BONE(RightFoot);
		__MAKE_PAIR_NEURON_BONE(LeftUpLeg);
		__MAKE_PAIR_NEURON_BONE(LeftLeg);
		__MAKE_PAIR_NEURON_BONE(LeftFoot);
		__MAKE_PAIR_NEURON_BONE(Spine);
		__MAKE_PAIR_NEURON_BONE(Spine1);
		__MAKE_PAIR_NEURON_BONE(Spine2);
		__MAKE_PAIR_NEURON_BONE(Spine3);
		__MAKE_PAIR_NEURON_BONE(Neck);
		__MAKE_PAIR_NEURON_BONE(Head);
		__MAKE_PAIR_NEURON_BONE(RightShoulder);
		__MAKE_PAIR_NEURON_BONE(RightArm);
		__MAKE_PAIR_NEURON_BONE(RightForeArm);
		__MAKE_PAIR_NEURON_BONE(RightHand);
		__MAKE_PAIR_NEURON_BONE(RightHandThumb1);
		__MAKE_PAIR_NEURON_BONE(RightHandThumb2);
		__MAKE_PAIR_NEURON_BONE(RightHandThumb3);
		__MAKE_PAIR_NEURON_BONE(RightInHandIndex);
		__MAKE_PAIR_NEURON_BONE(RightHandIndex1);
		__MAKE_PAIR_NEURON_BONE(RightHandIndex2);
		__MAKE_PAIR_NEURON_BONE(RightHandIndex3);
		__MAKE_PAIR_NEURON_BONE(RightInHandMiddle);
		__MAKE_PAIR_NEURON_BONE(RightHandMiddle1);
		__MAKE_PAIR_NEURON_BONE(RightHandMiddle2);
		__MAKE_PAIR_NEURON_BONE(RightHandMiddle3);
		__MAKE_PAIR_NEURON_BONE(RightInHandRing);
		__MAKE_PAIR_NEURON_BONE(RightHandRing1);
		__MAKE_PAIR_NEURON_BONE(RightHandRing2);
		__MAKE_PAIR_NEURON_BONE(RightHandRing3);
		__MAKE_PAIR_NEURON_BONE(RightInHandPinky);
		__MAKE_PAIR_NEURON_BONE(RightHandPinky1);
		__MAKE_PAIR_NEURON_BONE(RightHandPinky2);
		__MAKE_PAIR_NEURON_BONE(RightHandPinky3);
		__MAKE_PAIR_NEURON_BONE(LeftShoulder);
		__MAKE_PAIR_NEURON_BONE(LeftArm);
		__MAKE_PAIR_NEURON_BONE(LeftForeArm);
		__MAKE_PAIR_NEURON_BONE(LeftHand);
		__MAKE_PAIR_NEURON_BONE(LeftHandThumb1);
		__MAKE_PAIR_NEURON_BONE(LeftHandThumb2);
		__MAKE_PAIR_NEURON_BONE(LeftHandThumb3);
		__MAKE_PAIR_NEURON_BONE(LeftInHandIndex);
		__MAKE_PAIR_NEURON_BONE(LeftHandIndex1);
		__MAKE_PAIR_NEURON_BONE(LeftHandIndex2);
		__MAKE_PAIR_NEURON_BONE(LeftHandIndex3);
		__MAKE_PAIR_NEURON_BONE(LeftInHandMiddle);
		__MAKE_PAIR_NEURON_BONE(LeftHandMiddle1);
		__MAKE_PAIR_NEURON_BONE(LeftHandMiddle2);
		__MAKE_PAIR_NEURON_BONE(LeftHandMiddle3);
		__MAKE_PAIR_NEURON_BONE(LeftInHandRing);
		__MAKE_PAIR_NEURON_BONE(LeftHandRing1);
		__MAKE_PAIR_NEURON_BONE(LeftHandRing2);
		__MAKE_PAIR_NEURON_BONE(LeftHandRing3);
		__MAKE_PAIR_NEURON_BONE(LeftInHandPinky);
		__MAKE_PAIR_NEURON_BONE(LeftHandPinky1);
		__MAKE_PAIR_NEURON_BONE(LeftHandPinky2);
		__MAKE_PAIR_NEURON_BONE(LeftHandPinky3);
#undef __MAKE_PAIR_NEURON_BONE

		// construct from standard skeleton
		USkeleton* skel = UNeuronBPLibrary::GetNeuronStandardSkeleton();
		for (int32 i = 0; i < EnumBoneReferencePair.Num(); ++i) {
			EnumBoneReferencePair[i].Initialize(skel);
		}
	}

	FORCEINLINE const FBoneReference& GetReferenceFromEnum(ENeuronBones::Type InBoneEnum){
		return EnumBoneReferencePair[(int32)InBoneEnum];
	}

private:

	TArray<FBoneReference> EnumBoneReferencePair;

};

static FNeuronEnumBonePair GNeuronEnumBonePair;


//------------------------------------------------------------------------
FAnimNode_AutoNeuronSkeletonMatch::FAnimNode_AutoNeuronSkeletonMatch()
	: IgnoreBoneDisplacement(true)
	, IgnoreRootDisplacement(false)
{
}

//------------------------------------------------------------------------
void FAnimNode_AutoNeuronSkeletonMatch::GatherDebugData(FNodeDebugData& DebugData)
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
FMatrix _GetComponentTransform(const FReferenceSkeleton& InRefSkel, int32 InBoneIndex)
{
	FMatrix refBonePose = InRefSkel.GetRefBonePose()[InBoneIndex].ToMatrixWithScale();
	const FMeshBoneInfo& refBoneInfo = InRefSkel.GetRefBoneInfo()[InBoneIndex];
	int32 parentIndex = refBoneInfo.ParentIndex;
	while (parentIndex != INDEX_NONE)
	{
		int32 boneIndex = parentIndex;
		refBonePose = refBonePose * InRefSkel.GetRefBonePose()[boneIndex].ToMatrixWithScale();
		parentIndex = InRefSkel.GetRefBoneInfo()[boneIndex].ParentIndex;
	}
	return refBonePose;
}
FMatrix _GetComponentInvTransform(const FReferenceSkeleton& InRefSkel, int32 InBoneIndex)
{
	FMatrix refBonePose = InRefSkel.GetRefBonePose()[InBoneIndex].ToMatrixWithScale().Inverse();
	const FMeshBoneInfo& refBoneInfo = InRefSkel.GetRefBoneInfo()[InBoneIndex];
	int32 parentIndex = refBoneInfo.ParentIndex;
	while (parentIndex != INDEX_NONE)
	{
		int32 boneIndex = parentIndex;
		// parent inverse * this
		refBonePose = InRefSkel.GetRefBonePose()[boneIndex].ToMatrixWithScale().Inverse() * refBonePose;
		parentIndex = InRefSkel.GetRefBoneInfo()[boneIndex].ParentIndex;
	}
	return refBonePose;
}
//------------------------------------------------------------------------
void FAnimNode_AutoNeuronSkeletonMatch::EvaluateComponentSpace(FComponentSpacePoseContext& Output)
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

			USkeleton* NeuronSkeleton = UNeuronBPLibrary::GetNeuronStandardSkeleton();
			if (NeuronSkeleton == nullptr) {
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
				if (SkelComp->SkeletalMesh == nullptr) {
					continue;
				}
				if (GNeuronEnumBonePair.GetReferenceFromEnum(pair.NeuronBone).BoneIndex == INDEX_NONE || pair.TargetBoneReference.BoneIndex == INDEX_NONE) {
					continue;
				}

				// TODO 2015-10-9 by noslopforever : These matrix should cached in some place. There is no need to calculate it at each frame.
				FMatrix matNeuronRef = _GetComponentTransform(NeuronSkeleton->GetReferenceSkeleton(), GNeuronEnumBonePair.GetReferenceFromEnum(pair.NeuronBone).BoneIndex);
				FMatrix matInvThisRef = _GetComponentInvTransform(SkelComp->SkeletalMesh->RefSkeleton, pair.TargetBoneReference.BoneIndex);
				FMatrix matFinalTrans = matNeuronRef * matInvThisRef;

				// get basic transform
				FTransform NewBoneTM = MeshBases.GetComponentSpaceTransform(pair.TargetBoneReference.BoneIndex);

				FAnimationRuntime::ConvertBoneSpaceTransformToCS(SkelComp, MeshBases, NewBoneTM, pair.TargetBoneReference.BoneIndex, BCS_BoneSpace);

				// get old rotation axis and angle
				FQuat oldQuat = FQuat(rot);
				FVector axis;
				float angle;
				oldQuat.ToAxisAndAngle(axis, angle);

				// try convert axis to new space
				FVector newAxis = matFinalTrans.TransformVector(axis);

				// apply new rotation axis and old angle
				FQuat newQuat(newAxis, angle);
				NewBoneTM.SetRotation(newQuat);

				// Apply translations if needed
				if (pair.NeuronBone == ENeuronBones::Hips)
				{
					// root test root
					if (IgnoreRootDisplacement) {
						//trans = NewBoneTM.GetLocation();
						trans = FVector::ZeroVector;
					}
					// convert to dest space
					FVector destTrans = matFinalTrans.TransformVector(trans);
					NewBoneTM.SetTranslation(destTrans);
				}
				else
				{
					// normal test normal
					if (IgnoreBoneDisplacement) {
						trans = FVector::ZeroVector;
					}
					// convert to dest space
					FVector destTrans = matFinalTrans.TransformVector(trans);
					NewBoneTM.SetTranslation(destTrans);
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
bool FAnimNode_AutoNeuronSkeletonMatch::IsValidToEvaluate(const USkeleton* Skeleton, const FBoneContainer& RequiredBones)
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
void FAnimNode_AutoNeuronSkeletonMatch::InitializeBoneReferences(const FBoneContainer& RequiredBones)
{
	// Neuron skeleton
	USkeleton* NeuronSkeleton = ::LoadObject<USkeleton>(nullptr, TEXT("/NeuronForUnreal/Meshes/Skel_NeuronStandard.Skel_NeuronStandard"));
	if (NeuronSkeleton == nullptr) {
		return;
	}
	// for each configurated bone in Pairs
	for (int32 i = 0; i < Pairs.Num(); ++i) {
		Pairs[i].TargetBoneReference.Initialize(RequiredBones);
	}
	// sort by bone indices
	Pairs.Sort([](FNeuronSkeletonPair L, FNeuronSkeletonPair R) { return L.TargetBoneReference.BoneIndex < R.TargetBoneReference.BoneIndex; });
}

//------------------------------------------------------------------------



//------------------------------------------------------------------------
UAnimGraphNode_AutoNeuronSkeletonMatch::UAnimGraphNode_AutoNeuronSkeletonMatch(const FObjectInitializer& PCIP)
	:Super(PCIP)
{
}

//------------------------------------------------------------------------
FText UAnimGraphNode_AutoNeuronSkeletonMatch::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return GetControllerDescription();
}

//------------------------------------------------------------------------
FText UAnimGraphNode_AutoNeuronSkeletonMatch::GetTooltipText() const
{
	return LOCTEXT("AnimGraphNode_NeuronSkeletonPair_Tooltip", "This node allow a skeleton seems similar to which shown in Neuron skeleton.");
}

//------------------------------------------------------------------------
FText UAnimGraphNode_AutoNeuronSkeletonMatch::GetControllerDescription() const
{
	return LOCTEXT("NeuronSkeletonPair", "Do Neuron Skeleton");
}

//------------------------------------------------------------------------

#undef LOCTEXT_NAMESPACE
