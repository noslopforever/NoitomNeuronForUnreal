#pragma once

#include "NeuronCommon.h"

/** Neuron source
*	Managed by NeuronReaderSingleton.
*	Use NeuronReaderSingleton::Connect to establish a new FNeuronSource.
*	Handle communications with NeuronAxis.
*/
class FNeuronSource
	: public TSharedFromThis<FNeuronSource>
{
private:
	/** ctor
	*	Initialize some read-only values.
	*	ctor is only called by FNeuronReaderSingleton::_CreateConnection.
	*/
	FNeuronSource(const FString& InAddress, int32 InPort, int32 InCommandPort, ENeuronSocketType::Type InSocketType, void* InSocketRef, void* InCommandSocketRef);
	friend class FNeuronReaderSingleton;
public:
	/** dtor
	*	dtor is only called by FNeuronReaderSingleton::Disconnect.
	*	Don't try delete it by yourself. Please use FNeuronReaderSingleton::Disconnect instead.
	*/
	~FNeuronSource();

private:
	//
	// native properties
	//

	/** Source Actors link to this source
	*/
	TArray<FNeuronSourceActorSharePtr> SourceActors;

	/** Suspend Timeout settings */
	float SuspendTimeOut;

	/** Socket Reference
	*/
	void* SocketReference;

	/** Command Socket Reference
	*/
	void* CommandSocketReference;

	/** Critical section for data sync
	*/
	FCriticalSection CriticalSection;

private:
	//
	// pre-init settings and read only properties
	//
	/** Connect Address
	*/
	FString Address;
	/** Connect Port
	*/
	int32 Port;
	/** Command Server Port
	*/
	int32 CommandServerPort;
	/** Socket type
	*/
	ENeuronSocketType::Type SocketType;

	//
	// data syncing with Neuron
	//

	/** Socket Status
	*/
	ENeuronSocketStatus::Type SocketStatus;
	/** Socket Connection status message
	*/
	FString SocketMsg;

public:

	/** On Connect
	*/
	FNeuronSourceSignature OnConnect;

	/** On Disconnect
	*/
	FNeuronSourceSignature OnDisconnect;

	/** On Actor New
	*/
	FNeuronSourceActorSignature OnActorNew;
	/** On Actor Resumed
	*/
	FNeuronSourceActorSignature OnActorResumed;
	/** On Actor Suspended
	*/
	FNeuronSourceActorSignature OnActorSuspended;

public:

	FORCEINLINE const FString& GetAddress() const {
		return Address;
	}
	FORCEINLINE int32 GetPort() const {
		return Port;
	}
	FORCEINLINE ENeuronSocketType::Type GetSocketType() const {
		return SocketType;
	}
	FORCEINLINE ENeuronSocketStatus::Type GetSocketStatus() const {
		return SocketStatus;
	}
	FORCEINLINE const FString& GetSocketMessage() const {
		return SocketMsg;
	}
public:
	/** Register a actor datapool externally
	*/
	FNeuronSourceActorSharePtr AcquireActor(int32 InActorID);

	/** Find a actor datapool externally
	*/
	FNeuronSourceActorSharePtr FindActor(int32 InActorID);

private:

	/** Called by UNeuronGlobal when successfully created.
	*	this function is friend to UNeuronGlobal and should not be called at any other place.
	*
	*	Register all Neuron callbacks.
	*	Broadcast OnSourceNew(static) Event.
	*/
	void _PostCreation();
	friend class FNeuronReaderSingleton;

	/** Disconnect it from NeuronAxis
	*/
	void _Disconnect();

	/** Called when finish destroy.
	*
	*	Unregister all Neuron callbacks.
	*	Broadcast OnSourceRemove(static) Event.
	*/
	void _PostDestroy();

	/** if acquire or get from NeuronAxis, create Actor.
	*	Will not check exist actors. So you need to check it before call this function.
	*/
	FNeuronSourceActorSharePtr _CreateSourceActor(int32 InActorID);

	/** try data transfer each tick
	*/
	void _DoDataTransfer();


	// callbacks will access all private members of this class.
	friend class _NeuronDataReaderCallbacks;

};
