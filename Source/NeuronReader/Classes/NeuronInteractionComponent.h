#pragma once

#include "NeuronCommon.h"
#include "NeuronInteractionComponent.generated.h"


/** Neuron interaction component that could attach to other.
*/
UCLASS(ClassGroup = Neuron, BlueprintType, Blueprintable, meta = (BlueprintSpawnableComponent))
class UNeuronInteractionComponent : public UActorComponent
{
	GENERATED_UCLASS_BODY()
public:

	/** Axis address
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Noitom|Neuron")
	FString AxisAddress;

	/** Axis port
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Noitom|Neuron")
	int32 AxisPort;

	/** Command Axis port
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Noitom|Neuron")
	int32 AxisCommandPort;

	/** Axis actor id
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Noitom|Neuron")
	int32 AxisActorID;

	/** Axis socket type
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Noitom|Neuron")
	TEnumAsByte<ENeuronSocketType::Type> AxisSocketType;

	// 
	// current running configurations
	//
	UPROPERTY()
	FString UsingAddress;
	UPROPERTY()
	int32 UsingPort;
	UPROPERTY()
	int32 UsingCmdPort;
	UPROPERTY()
	int32 UsingActorID;
	UPROPERTY()
	TEnumAsByte<ENeuronSocketType::Type> UsingSocketType;

	/** Neuron source shared ptr.
	*/
	FNeuronSourceSharePtr NeuronSourcePtr;
	/** Neuron actor shared ptr.
	*/
	FNeuronSourceActorSharePtr NeuronSourceActorPtr;

public:

	UFUNCTION(BlueprintCallable, Category = "Noitom|Neuron")
	void UpdateLink();

	UFUNCTION(BlueprintCallable, Category = "Noitom|Neuron")
	void GetBoneData(ENeuronBones::Type InBoneId, bool& OutIsValid, FVector& OutPosition, FRotator& OutRotation);


private:

};