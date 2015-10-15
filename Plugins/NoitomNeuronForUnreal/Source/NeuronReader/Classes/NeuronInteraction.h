#pragma once

#include "NeuronCommon.h"
#include "NeuronInteraction.generated.h"

/** Data accessor
*/
UCLASS(BlueprintType)
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

	/** current linked address.
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Noitom|Neuron")
	FString UsingAddress;

	/** current linked port. 0 if invalid.
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Noitom|Neuron")
	int32 UsingPort;

	/** current linked port. 0 if invalid
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Noitom|Neuron")
	int32 UsingCmdPort;

	/** current linked port. -1 if invalid
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Noitom|Neuron")
	int32 UsingActorID;

	/** current linked socket type.
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Noitom|Neuron")
	TEnumAsByte<ENeuronSocketType::Type> UsingSocketType;


public:

	/** Connect to Data Reader.
	*/
	UFUNCTION(BlueprintCallable, Category = "Noitom|Neuron", meta = (DisplayName = "Neuron Connect UDP"))
	static class UNeuronActorProxy* ConnectUDP(int32 InPort, int32 InActorID);

	/** Is link valid.
	*/
	UFUNCTION(BlueprintPure, Category = "Noitom|Neuron")
	bool IsValid();

	/** Get bone data from source. In Neuron space.
	*/
	UFUNCTION(BlueprintPure, Category = "Noitom|Neuron")
	void GetBoneData(ENeuronBones::Type InBoneId, bool& OutIsValid, FVector& OutPosition, FRotator& OutRotation);

};

