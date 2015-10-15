#include "NeuronReaderModulePCH.h"
#include "NeuronAnimInstance.h"
#include "NeuronInteraction.h"


//------------------------------------------------------------------------
UNeuronAnimInstance::UNeuronAnimInstance(const FObjectInitializer& PCIP)
	: Super(PCIP)
{
}

//------------------------------------------------------------------------
bool UNeuronAnimInstance::IsConnect()
{
	if (NeuronActorProxy != nullptr 
		&& NeuronActorProxy->IsValid()) {
		return true;
	}
	return false;
}

//------------------------------------------------------------------------
void UNeuronAnimInstance::SetNeuronProxy(UNeuronActorProxy* InNeuronActorProxy)
{
	NeuronActorProxy = InNeuronActorProxy;
}

//------------------------------------------------------------------------
void UNeuronAnimInstance::GetBoneData(ENeuronBones::Type InBoneId, bool& OutIsValid, FVector& OutPosition, FRotator& OutRotation)
{
	if (NeuronActorProxy != nullptr) {
		NeuronActorProxy->GetBoneData(InBoneId, OutIsValid, OutPosition, OutRotation);
		return;
	}
	OutPosition = FVector::ZeroVector;
	OutRotation = FRotator::ZeroRotator;
	OutIsValid = false;
}

//------------------------------------------------------------------------

