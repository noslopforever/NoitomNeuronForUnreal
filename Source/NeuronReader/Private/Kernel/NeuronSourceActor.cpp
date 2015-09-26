#include "NeuronReaderModulePCH.h"
#include "Kernel/NeuronSourceActor.h"


//------------------------------------------------------------------------
const int32 GMaxBoneDataBuffer = 512;
//------------------------------------------------------------------------
FNeuronSourceActor::FNeuronSourceActor(FNeuronSource* InSource, int32 InActorID)
	: Source(InSource)
	, ActorID(InActorID)
{
	BoneBuffer1.AddZeroed(ENeuronBones::Type::NumOfBones);
	BoneBuffer2.AddZeroed(ENeuronBones::Type::NumOfBones);
	UsingBuffer	= &BoneBuffer1;
	ShadowBuffer= &BoneBuffer2;
}

//------------------------------------------------------------------------
FNeuronSourceActor::~FNeuronSourceActor()
{
}

//------------------------------------------------------------------------
void FNeuronSourceActor::GetBoneData(ENeuronBones::Type InBoneType, FVector& OutPosition, FRotator& OutRotation)
{
	CriticalSection.Lock();
	FNeuronBoneInfo& bone = (*UsingBuffer)[(int32)InBoneType];
	CriticalSection.Unlock();

	OutPosition = bone.Position;
	OutRotation = bone.Rotation;
}

//------------------------------------------------------------------------
void FNeuronSourceActor::_Suspend()
{
}

//------------------------------------------------------------------------
void FNeuronSourceActor::_Resume()
{
}

//------------------------------------------------------------------------
void FNeuronSourceActor::_PostSourceDestroy()
{
	ActorID = -1;

	// kill data buffers
	FScopeLock Lock(&CriticalSection);
	UsingBuffer = nullptr;
	ShadowBuffer = nullptr;
}

//------------------------------------------------------------------------
FORCEINLINE FVector PosFromNeuronToUE(float InData0, float InData1, float InData2) {
	return FVector(InData0, -InData1, InData2);
}
FORCEINLINE FRotator RotFromNeuronToUE(float InData0, float InData1, float InData2) {
	// if Neuron's output format is ZYX, it will be perfectly matched with rotator's -Yaw -Pitch Roll.
	// TODO by noslopforever @ 2015-9-26£ºIf output is ZYX, use this rotator, otherwise use 3 rotation-matrices' compose (and take care of +- sign).
	return FRotator(-InData1, -InData0, InData2);
}
//------------------------------------------------------------------------
void FNeuronSourceActor::_OnReceiveFrameData(float* InData, int32 InDataCount, bool InDisplacement)
{
	if (ShadowBuffer == nullptr) {
		return;
	}

	// write to shadow buffer
	int32 dataIndex = 0;
	// special handle bone-0, for it contains root motion.
	(*ShadowBuffer)[0].Position = PosFromNeuronToUE(InData[0], InData[1], InData[2]);
	(*ShadowBuffer)[0].Rotation = RotFromNeuronToUE(InData[3], InData[4], InData[5]);
	dataIndex = 6;
	// load all other bones.
	for (int32 i = 1; i < ENeuronBones::Type::NumOfBones; ++i)
	{
		if (InDisplacement) {
			(*ShadowBuffer)[i].Position = PosFromNeuronToUE(InData[dataIndex + 0], InData[dataIndex + 1], InData[dataIndex + 2]);
			dataIndex += 3;
		}
		else{
			(*ShadowBuffer)[i].Position = FVector::ZeroVector;
		}
		(*ShadowBuffer)[i].Rotation = RotFromNeuronToUE(InData[dataIndex + 0], InData[dataIndex + 1], InData[dataIndex + 2]);
		dataIndex += 3;
	}

	// swap to using buffer
	{
		FScopeLock Lock(&CriticalSection);

		// time of last data frame
		LastFrameTime = FDateTime::Now();
		// swap buffers
		TArray<FNeuronBoneInfo>* swapBuffer = UsingBuffer;
		UsingBuffer = ShadowBuffer;
		ShadowBuffer = swapBuffer;
	}
}

//------------------------------------------------------------------------
