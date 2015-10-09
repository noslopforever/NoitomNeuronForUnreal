#pragma once

#include "NeuronCommon.h"
#include "NeuronInteraction.generated.h"

/** Data accessor
*/
UCLASS()
class UNeuronActorProxy
	: public UObject
{
	GENERATED_UCLASS_BODY()
public:

	/** Neuron source shared ptr.
	*/
	FNeuronSourceSharePtr NeuronSourcePtr;
	/** Neuron source actor
	*/
	FNeuronSourceActorSharePtr NeuronSourceActorPtr;

public:

	/** Connect to Data Reader.
	*/
	UFUNCTION(BlueprintCallable, Category = "Noitom|Neuron")
	static class UNeuronActorProxy* ConnectUDP(int32 InPort, int32 InActorID);

	/** Get bone data from source.
	*/
	UFUNCTION(BlueprintCallable, Category = "Noitom|Neuron")
	void GetBoneData(ENeuronBones::Type InBoneId, bool& OutIsValid, FVector& OutPosition, FRotator& OutRotation);

};

