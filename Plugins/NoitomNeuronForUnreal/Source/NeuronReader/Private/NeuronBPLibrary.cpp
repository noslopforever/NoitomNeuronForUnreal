#include "NeuronReaderModulePCH.h"
#include "NeuronBPLibrary.h"
#include "NeuronInteraction.h"


//------------------------------------------------------------------------
UNeuronBPLibrary::UNeuronBPLibrary(const FObjectInitializer& PCIP)
	: Super(PCIP)
{
}

//------------------------------------------------------------------------
class USkeleton* UNeuronBPLibrary::GetNeuronStandardSkeleton()
{
	// TODO noslopforever : Do some cache or something like that.
	return ::LoadObject<USkeleton>(nullptr, TEXT("/NeuronForUnreal/Meshes/Skel_NeuronStandard.Skel_NeuronStandard"));
}

//------------------------------------------------------------------------
FVector UNeuronBPLibrary::GetNeuronActorHipMoveCS(UNeuronActorProxy* InActorProxy)
{
	return GetNeuronBonePosCS(InActorProxy, ENeuronBones::Hips);
}

//------------------------------------------------------------------------
FVector UNeuronBPLibrary::GetNeuronBonePosCS(class UNeuronActorProxy* InActorProxy, ENeuronBones::Type InBone)
{
	if (InActorProxy == nullptr) {
		return FVector::ZeroVector;
	}

	bool isValid = false;
	FVector translation;
	FRotator rotation;
	InActorProxy->GetBoneData(InBone, isValid, translation, rotation);
	if (false == isValid) {
		return FVector::ZeroVector;
	}
	return FVector(translation.X, translation.Z, -translation.Y);
}

//------------------------------------------------------------------------
