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

	// 
	// current running configurations
	//
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Noitom|Neuron")
	FString UsingAddress;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Noitom|Neuron")
	int32 UsingPort;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Noitom|Neuron")
	int32 UsingCmdPort;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Noitom|Neuron")
	int32 UsingActorID;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Noitom|Neuron")
	TEnumAsByte<ENeuronSocketType::Type> UsingSocketType;

	/** Neuron source
	*/
	FNeuronSourceSharePtr NeuronSourcePtr;

	/** Neuron source actor
	*/
	FNeuronSourceActorSharePtr NeuronSourceActorPtr;

public:

	/** Is connect
	*/
	UFUNCTION(BlueprintPure, Category = "Noitom|Neuron")
	bool IsConnect();

	/** connect to source
	*/
	UFUNCTION(BlueprintCallable, Category = "Noitom|Neuron")
	void Connect(FString InAddress, int32 InPort, int32 InActorID, ENeuronSocketType::Type InSocketType);

	/** Get bone data
	*/
	UFUNCTION(BlueprintPure, Category = "Noitom|Neuron")
	void GetBoneData(ENeuronBones::Type InBoneId, bool& OutIsValid, FVector& OutPosition, FRotator& OutRotation);

};
