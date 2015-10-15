#include "NeuronReaderModulePCH.h"
#include "NeuronInteraction.h"


//------------------------------------------------------------------------
UNeuronActorProxy::UNeuronActorProxy(const FObjectInitializer& PCIP)
	: Super(PCIP)
{
	UsingAddress = TEXT("");
	UsingPort = 0;
	UsingCmdPort = 0;
	UsingActorID = -1;
	UsingSocketType = ENeuronSocketType::None;
}

//------------------------------------------------------------------------
UNeuronActorProxy* UNeuronActorProxy::ConnectUDP(int32 InPort, int32 InActorID)
{
	// gain and acquire Actors
	INeuronReaderSingleton* singleton = INeuronReaderModule::Get().GetSingleton();
	if (singleton != nullptr)
	{
		FNeuronSourceSharePtr sourcePtr = singleton->GetConnectToSource("", InPort, 0, ENeuronSocketType::UDP);
		if (false == sourcePtr.IsValid()) {
			return nullptr;
		}
		FNeuronSourceActorSharePtr actorPtr = sourcePtr->AcquireActor(InActorID);
		if (false == actorPtr.IsValid()) {
			return nullptr;
		}

		// create proxy
		UNeuronActorProxy* proxy = ::NewObject<UNeuronActorProxy>();
		proxy->NeuronSourcePtr = sourcePtr;
		proxy->NeuronSourceActorPtr = actorPtr;

		proxy->UsingAddress = TEXT("");
		proxy->UsingPort = InPort;
		proxy->UsingCmdPort = 0;
		proxy->UsingActorID = InActorID;
		proxy->UsingSocketType = ENeuronSocketType::UDP;

		return proxy;
	}

	return nullptr;
}

//------------------------------------------------------------------------
bool UNeuronActorProxy::IsValid()
{
	return NeuronSourceActorPtr.IsValid();
}

//------------------------------------------------------------------------
void UNeuronActorProxy::GetBoneData(ENeuronBones::Type InBoneId, bool& OutIsValid, FVector& OutPosition, FRotator& OutRotation)
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
