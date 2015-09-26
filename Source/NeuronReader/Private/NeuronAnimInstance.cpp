#include "NeuronReaderModulePCH.h"
#include "NeuronAnimInstance.h"


//------------------------------------------------------------------------
UNeuronAnimInstance::UNeuronAnimInstance(const FObjectInitializer& PCIP)
	: Super(PCIP)
{
}

//------------------------------------------------------------------------
bool UNeuronAnimInstance::IsConnect()
{
	if (NeuronSourceActorPtr.IsValid()) {
		return true;
	}
	return false;
}

//------------------------------------------------------------------------
void UNeuronAnimInstance::Connect(FString InAddress, int32 InPort, int32 InActorID, ENeuronSocketType::Type InSocketType)
{
	INeuronReaderSingleton* singleton = INeuronReaderModule::Get().GetSingleton();
	if (singleton == nullptr) {
		return;
	}
	// try connect to Axis
	FNeuronSourceSharePtr ptr = singleton->GetConnectToSource(InAddress, InPort, 0, InSocketType);
	if (false == ptr.IsValid()) {
		return;
	}
	// try acquire actor
	FNeuronSourceActorSharePtr actorPtr = ptr->AcquireActor(InActorID);
	if (false == actorPtr.IsValid()) {
		return;
	}

	UsingAddress = InAddress;
	UsingPort = InPort;
	UsingCmdPort = 0;
	UsingActorID = InActorID;
	UsingSocketType = InSocketType;
	NeuronSourcePtr = ptr;
	NeuronSourceActorPtr = actorPtr;
}

//------------------------------------------------------------------------
void UNeuronAnimInstance::GetBoneData(ENeuronBones::Type InBoneId, bool& OutIsValid, FVector& OutPosition, FRotator& OutRotation)
{
	if (NeuronSourceActorPtr.IsValid()) {
		NeuronSourceActorPtr->GetBoneData(InBoneId, OutPosition, OutRotation);
		OutIsValid = true;
		return;
	}
	OutPosition = FVector::ZeroVector;
	OutRotation = FRotator::ZeroRotator;
	OutIsValid = false;
}

//------------------------------------------------------------------------

