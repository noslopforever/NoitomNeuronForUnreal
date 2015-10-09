#pragma once

#include "NeuronBPLibrary.generated.h"


/** Neuron Blueprint Library
*/
UCLASS()
class UNeuronBPLibrary :public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()
public:

	/** Neuron standard skeleton resource
	*/
	static class USkeleton* GetNeuronStandardSkeleton();

};