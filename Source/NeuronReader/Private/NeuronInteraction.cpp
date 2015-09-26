#include "NeuronReaderModulePCH.h"
#include "NeuronInteraction.h"


//------------------------------------------------------------------------
UNeuronActorProxy::UNeuronActorProxy(const FObjectInitializer& PCIP)
	: Super(PCIP)
{
}

//------------------------------------------------------------------------
UNeuronActorProxy* UNeuronActorProxy::ConnectUDP(int32 InPort, int32 InActorID)
{
	// gain and acquire Actors
	INeuronReaderSingleton* singleton = INeuronReaderModule::Get().GetSingleton();
	if (singleton != nullptr)
	{
		FNeuronSourceSharePtr sourcePtr = singleton->GetConnectToSource("", InPort, 0, ENeuronSocketType::UDP);
		FNeuronSourceActorSharePtr actorPtr = sourcePtr->AcquireActor(InActorID);

		// create proxy
		UNeuronActorProxy* proxy = ::NewObject<UNeuronActorProxy>();
		proxy->NeuronSourcePtr = sourcePtr;
		proxy->NeuronSourceActorPtr = actorPtr;
		return proxy;
	}

	return nullptr;
}

//------------------------------------------------------------------------
void UNeuronActorProxy::GetBoneData(ENeuronBones::Type InBoneId, bool& OutIsValid, FVector& OutPosition, FRotator& OutRotation)
{
	if (NeuronSourceActorPtr.IsValid()) {
		NeuronSourceActorPtr->GetBoneData(InBoneId, OutPosition, OutRotation);
		OutIsValid = true;
	}
	OutIsValid = false;
}

//------------------------------------------------------------------------
