#include "NeuronReaderModulePCH.h"
#include "NeuronInteractionComponent.h"


//------------------------------------------------------------------------
UNeuronInteractionComponent::UNeuronInteractionComponent(const FObjectInitializer& PCIP)
	: Super(PCIP)
{
	AxisAddress = "";
	AxisPort = 0;
	AxisCommandPort = 0;
	AxisActorID = 0;
	AxisSocketType = ENeuronSocketType::None;

	UsingAddress = AxisAddress;
	UsingPort = AxisPort;
	UsingCmdPort = AxisCommandPort;
	UsingActorID = AxisActorID;
	UsingSocketType = AxisSocketType;
}

//------------------------------------------------------------------------
void UNeuronInteractionComponent::UpdateLink()
{
	INeuronReaderSingleton* singleton = INeuronReaderModule::Get().GetSingleton();
	if (singleton == nullptr) {
		return;
	}
	// try connect to Axis
	FNeuronSourceSharePtr ptr = singleton->GetConnectToSource(AxisAddress, AxisPort, AxisCommandPort, AxisSocketType);
	if (false == ptr.IsValid()) {
		return;
	}
	// try acquire actor
	FNeuronSourceActorSharePtr actorPtr = ptr->AcquireActor(AxisActorID);
	if (false == actorPtr.IsValid()) {
		return;
	}

	UsingAddress = AxisAddress;
	UsingPort = AxisPort;
	UsingCmdPort = AxisCommandPort;
	UsingActorID = AxisActorID;
	UsingSocketType = AxisSocketType;
	NeuronSourceActorPtr = actorPtr;
}

//------------------------------------------------------------------------
void UNeuronInteractionComponent::GetBoneData(ENeuronBones::Type InBoneId, bool& OutIsValid, FVector& OutPosition, FRotator& OutRotation)
{
	if (NeuronSourceActorPtr.IsValid()) {
		NeuronSourceActorPtr->GetBoneData(InBoneId, OutPosition, OutRotation);
		OutIsValid = true;
	}
	OutIsValid = false;
}

//------------------------------------------------------------------------
