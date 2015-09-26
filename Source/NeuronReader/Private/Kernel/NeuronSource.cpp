#include "NeuronReaderModulePCH.h"
#include "Kernel/NeuronSource.h"
#include "Kernel/NeuronSourceActor.h"


// Neuron Data Reader Callbacks
class _NeuronDataReaderCallbacks
{
public:
	static void _FrameDataCB(void* customedObj, void* sender, BvhDataHeaderEx* header, float* data);
	static void _ConnectionStatusCB(void* customedObj, void* sender, SocketStatus status, char* message);
	static void _CommandDataCB(void* customedObj, void* sender, CommandPack* pack, void* data);
};


//------------------------------------------------------------------------
FNeuronSource::FNeuronSource(const FString& InAddress, int32 InPort, int32 InCommandPort, ENeuronSocketType::Type InSocketType, SOCKET_REF InSocketRef, SOCKET_REF InCommandSocketRef)
{
	SuspendTimeOut = 5000.0f;

	Address = InAddress;
	Port = InPort;
	CommandServerPort = InCommandPort;
	SocketType = InSocketType;

	SocketReference = InSocketRef;
	CommandSocketReference = InCommandSocketRef;
}

//------------------------------------------------------------------------
FNeuronSource::~FNeuronSource()
{
	// unregister callbacks
	::BRRegisterFrameDataCallback(this, nullptr);
	::BRRegisterSocketStatusCallback(this, nullptr);
	::BRRegisterCommandDataCallback(this, nullptr);

	// make sure all actors were cleaned.
	FScopeLock Lock(&CriticalSection);
	for (auto actor : SourceActors) {
		actor->_PostSourceDestroy();
	}
}

//------------------------------------------------------------------------
FNeuronSourceActorSharePtr FNeuronSource::AcquireActor(int32 InActorID)
{
	FNeuronSourceActorSharePtr ptr = FindActor(InActorID);
	if (ptr.IsValid()) {
		return ptr;
	}

	return _CreateSourceActor(InActorID);
}

//------------------------------------------------------------------------
FNeuronSourceActorSharePtr FNeuronSource::FindActor(int32 InActorID)
{
	FScopeLock lock(&CriticalSection);
	for (auto actor : SourceActors)
	{
		if (actor->GetActorID() == InActorID){
			return actor;
		}
	}
	return nullptr;
}

//------------------------------------------------------------------------
void FNeuronSource::_PostCreation()
{
	// register callbacks.
	::BRRegisterFrameDataCallback(this, _NeuronDataReaderCallbacks::_FrameDataCB);
	::BRRegisterSocketStatusCallback(this, _NeuronDataReaderCallbacks::_ConnectionStatusCB);
	::BRRegisterCommandDataCallback(this, _NeuronDataReaderCallbacks::_CommandDataCB);

	// tell events
	if (OnConnect.IsBound()) {
		OnConnect.Broadcast(this->AsShared());
	}

	if (INeuronReaderSingleton::OnSourceNew.IsBound()) {
		INeuronReaderSingleton::OnSourceNew.Broadcast(this->AsShared());
	}
}

//------------------------------------------------------------------------
void FNeuronSource::_PostDestroy()
{
	// tell events
	if (INeuronReaderSingleton::OnSourceRemove.IsBound()) {
		INeuronReaderSingleton::OnSourceRemove.Broadcast(this->AsShared());
	}
	if (OnDisconnect.IsBound()) {
		OnDisconnect.Broadcast(this->AsShared());
	}

	// unregister callbacks
	::BRRegisterFrameDataCallback(this, nullptr);
	::BRRegisterSocketStatusCallback(this, nullptr);
	::BRRegisterCommandDataCallback(this, nullptr);

	// cleanup source actors
	{
		FScopeLock Lock(&CriticalSection);
		for (auto actor : SourceActors) {
			actor->_PostSourceDestroy();
		}
		SourceActors.Empty();
	}
	// cleanup members
	CommandSocketReference = nullptr;
	SocketReference = nullptr;
	SocketType = ENeuronSocketType::None;
	Address = "";
	Port = -1;
	CommandServerPort = -1;
}

//------------------------------------------------------------------------
FNeuronSourceActorSharePtr FNeuronSource::_CreateSourceActor(int32 InActorID)
{
	FNeuronSourceActorSharePtr sourceActor = MakeShareable(new FNeuronSourceActor(this, InActorID));
	FScopeLock lock(&CriticalSection);
	SourceActors.Add(sourceActor);
	return sourceActor;
}

//------------------------------------------------------------------------
void FNeuronSource::_DoDataTransfer()
{
}

//------------------------------------------------------------------------
void _NeuronDataReaderCallbacks::_FrameDataCB(void* customedObj, SOCKET_REF sender, BvhDataHeaderEx* header, float* data)
{
	FNeuronSource* ThisObj = reinterpret_cast<FNeuronSource*>(customedObj);
	check(ThisObj == customedObj);

	int32 avatarIndex = header->AvatarIndex;

	// not find, try create.
	FNeuronSourceActorSharePtr actor = ThisObj->FindActor(avatarIndex);
	if (false == actor.IsValid()) {
		actor = ThisObj->_CreateSourceActor(avatarIndex);
	}

	// hey, data is coming :-).
	if (actor.IsValid()) {
		actor->_OnReceiveFrameData(data, header->DataCount, header->WithDisp == 1);
	}
}

//------------------------------------------------------------------------
void _NeuronDataReaderCallbacks::_ConnectionStatusCB(void* customedObj, SOCKET_REF sender, SocketStatus status, char* message)
{
	FNeuronSource* ThisObj = reinterpret_cast<FNeuronSource*>(customedObj);
	check(ThisObj == customedObj);
	UE_LOG(LogNeuron, Log, TEXT("Connection Status Changed : %d  status message %s")
		, (int32)status
		, *FString(message)
		);

	ThisObj->SocketStatus = (ENeuronSocketStatus::Type)(int32)status;
	ThisObj->SocketMsg = message;
}

//------------------------------------------------------------------------
void _NeuronDataReaderCallbacks::_CommandDataCB(void* customedObj, SOCKET_REF sender, CommandPack* pack, void* data)
{
	FNeuronSource* ThisObj = reinterpret_cast<FNeuronSource*>(customedObj);
	check(ThisObj == customedObj);
}

//------------------------------------------------------------------------
