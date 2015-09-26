#pragma once

// predefines
class FNeuronSource;
class FNeuronSourceActor;

typedef TSharedPtr<FNeuronSource> FNeuronSourceSharePtr;
typedef TSharedPtr<FNeuronSourceActor> FNeuronSourceActorSharePtr;

/** UNeuronSource delegate declare */
DECLARE_MULTICAST_DELEGATE_OneParam(FNeuronSourceSignature, FNeuronSourceSharePtr);

/** UNeuronSourceActor delegate declare */
DECLARE_MULTICAST_DELEGATE_OneParam(FNeuronSourceActorSignature, FNeuronSourceActorSharePtr);

/** Neuron Socket Connection Type
*	match NeuronSDK's SocketType.
*/
UENUM()
namespace ENeuronSocketType
{
	enum Type
	{
		None,
		TCP,
		UDP,
	};
}

/** Neuron Socket status.
*	match NeuronSDK's SocketStatus.
*/
UENUM()
namespace ENeuronSocketStatus
{
	enum Type
	{
		Running,              // Socket is working correctly
		Starting,             // Is trying to start service
		OffWork,              // Not working
	};
}

/** Neuron Bones
*	match NeuronSDK's 
*/
UENUM()
namespace ENeuronBones
{
	enum Type
	{
		Hips = 0,
		RightUpLeg = 1,
		RightLeg = 2,
		RightFoot = 3,
		LeftUpLeg = 4,
		LeftLeg = 5,
		LeftFoot = 6,
		Spine = 7,
		Spine1 = 8,
		Spine2 = 9,
		Spine3 = 10,
		Neck = 11,
		Head = 12,
		RightShoulder = 13,
		RightArm = 14,
		RightForeArm = 15,
		RightHand = 16,
		RightHandThumb1 = 17,
		RightHandThumb2 = 18,
		RightHandThumb3 = 19,
		RightInHandIndex = 20,
		RightHandIndex1 = 21,
		RightHandIndex2 = 22,
		RightHandIndex3 = 23,
		RightInHandMiddle = 24,
		RightHandMiddle1 = 25,
		RightHandMiddle2 = 26,
		RightHandMiddle3 = 27,
		RightInHandRing = 28,
		RightHandRing1 = 29,
		RightHandRing2 = 30,
		RightHandRing3 = 31,
		RightInHandPinky = 32,
		RightHandPinky1 = 33,
		RightHandPinky2 = 34,
		RightHandPinky3 = 35,
		LeftShoulder = 36,
		LeftArm = 37,
		LeftForeArm = 38,
		LeftHand = 39,
		LeftHandThumb1 = 40,
		LeftHandThumb2 = 41,
		LeftHandThumb3 = 42,
		LeftInHandIndex = 43,
		LeftHandIndex1 = 44,
		LeftHandIndex2 = 45,
		LeftHandIndex3 = 46,
		LeftInHandMiddle = 47,
		LeftHandMiddle1 = 48,
		LeftHandMiddle2 = 49,
		LeftHandMiddle3 = 50,
		LeftInHandRing = 51,
		LeftHandRing1 = 52,
		LeftHandRing2 = 53,
		LeftHandRing3 = 54,
		LeftInHandPinky = 55,
		LeftHandPinky1 = 56,
		LeftHandPinky2 = 57,
		LeftHandPinky3 = 58,

		NumOfBones,
	};
}


