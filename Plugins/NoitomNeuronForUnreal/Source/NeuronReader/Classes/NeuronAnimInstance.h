#pragma once

#include "NeuronCommon.h"
#include "Animation/AnimInstance.h"
#include "NeuronAnimInstance.generated.h"


/** Neuron animation instance
*/
UCLASS(transient)
class UNeuronAnimInstance : public UAnimInstance
{
	GENERATED_UCLASS_BODY()
public:

	/** Listenning Actor Proxy
	*/
	class UNeuronActorProxy* NeuronActorProxy;

public:

	/** Is connect
	*/
	UFUNCTION(BlueprintPure, Category = "Noitom|Neuron")
	bool IsConnect();

	/** connect to source
	*/
	UFUNCTION(BlueprintCallable, Category = "Noitom|Neuron")
	void SetNeuronProxy(UNeuronActorProxy* InNeuronActorProxy);

	/** Get bone data
	*/
	UFUNCTION(BlueprintPure, Category = "Noitom|Neuron")
	void GetBoneData(ENeuronBones::Type InBoneId, bool& OutIsValid, FVector& OutPosition, FRotator& OutRotation);

};
