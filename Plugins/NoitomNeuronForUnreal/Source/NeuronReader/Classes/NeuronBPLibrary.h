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

	/** get NeuronActor hip movement and convert it to unreal skeletal component space (always face to +Y and left is +X).
	*/
	UFUNCTION(BlueprintPure, Category = "Noitom|Neuron")
	static FVector GetNeuronActorHipMoveCS(class UNeuronActorProxy* InActorProxy);

	/** get NeuronActor hip movement and convert it to unreal skeletal component space (always face to +Y and left is +X).
	*/
	UFUNCTION(BlueprintPure, Category = "Noitom|Neuron")
	static FVector GetNeuronBonePosCS(class UNeuronActorProxy* InActorProxy, ENeuronBones::Type InBone);

};