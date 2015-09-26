#include "NeuronReaderModulePCH.h"
#include "Kernel/NeuronReaderSingletonPrivate.h"
#include "Kernel/NeuronSource.h"
#include "Kernel/NeuronSourceActor.h"


//------------------------------------------------------------------------
// implement of global callbacks
FNeuronSourceSignature INeuronReaderSingleton::OnSourceNew;
FNeuronSourceSignature INeuronReaderSingleton::OnSourceRemove;
FNeuronSourceActorSignature INeuronReaderSingleton::OnSourceActorEnter;
FNeuronSourceActorSignature INeuronReaderSingleton::OnSourceActorSuspend;
FNeuronSourceActorSignature INeuronReaderSingleton::OnSourceActorResume;
FNeuronSourceActorSignature INeuronReaderSingleton::OnSourceActorLeave;
//------------------------------------------------------------------------
FNeuronReaderSingleton::FNeuronReaderSingleton()
{
}

//------------------------------------------------------------------------
FNeuronReaderSingleton::~FNeuronReaderSingleton()
{
	FScopeLock Lock(&CriticalSection);

	// tell sources to close.
	for (FNeuronSourceSharePtr source : ConnectedSources) {
		DisconnectSource(source);
	}

}

//------------------------------------------------------------------------
void FNeuronReaderSingleton::GetSources(TArray<FNeuronSourceSharePtr> OutSources)
{
	FScopeLock Lock(&CriticalSection);
	OutSources = ConnectedSources;
}

//------------------------------------------------------------------------
FNeuronSourceSharePtr FNeuronReaderSingleton::GetConnectToSource(const FString& InAddress, int32 InPort, int32 InCommandPort, ENeuronSocketType::Type InSocketType)
{
	// has exist source?
	FNeuronSourceSharePtr existSource = _FindConnection(InAddress, InPort, InSocketType);
	if (existSource.IsValid()) {
		return existSource;
	}

	// try create new source
	FNeuronSourceSharePtr newSource = _CreateConnection(InAddress, InPort, InCommandPort, InSocketType);
	return newSource;
}

//------------------------------------------------------------------------
void FNeuronReaderSingleton::DisconnectSource(FNeuronSourceSharePtr InSource)
{
	if (InSource.IsValid()) {
		return;
	}

	// try disconnect
	UE_LOG(LogNeuron, Log, TEXT("Try disconnect to Axis: addr=%s, port=%d")
		, *InSource->Address
		, InSource->Port
		);

	check(InSource->SocketReference != nullptr);

	// remove from array
	{
		FScopeLock Lock(&CriticalSection);
		ConnectedSources.Remove(InSource);
	}

	// close socket
	/// TODO how to resolve CommandSocketReference?
	::BRCloseSocket(InSource->SocketReference);

	// source post destroy
	InSource->_PostDestroy();

	UE_LOG(LogNeuron, Log, TEXT("Source connection successfully destroyed!"));
}

//------------------------------------------------------------------------
FNeuronSourceSharePtr FNeuronReaderSingleton::_CreateConnection(const FString& InAddress, int32 InPort, int32 InCommandServerPort, ENeuronSocketType::Type InSocketType)
{
	// create connection and add it to Sources

	{
		// TODO noslopforever @ 2015-9-13 v0.1 : it smells bad...
		static UEnum *e = FindObject<UEnum>(ANY_PACKAGE, TEXT("ENeuronSocketType"));
		UE_LOG(LogNeuron, Log, TEXT("Try create connection to Axis: addr=%s, port=%d, cmdport=%d, linktype=%s")
			, *InAddress
			, InPort
			, InCommandServerPort
			, *e->GetEnumName(InSocketType)
			);
	}

	// convert address to Ansi char
	TArray<ANSICHAR> strAddr = StringToArray<ANSICHAR>(*InAddress, InAddress.Len());

	SOCKET_REF refSocket = nullptr;
	// try connect
	if (InSocketType == ENeuronSocketType::TCP)
	{
		// connect to InAddress:InPort and get socket
		refSocket = ::BRConnectTo(strAddr.GetData(), InPort);
		if (refSocket == nullptr)
		{
			FString errMsg = ::BRGetLastErrorMessage();
			UE_LOG(LogNeuron, Error, TEXT("Cannot link to server: %s"), *errMsg);
		}
	}
	else if (InSocketType == ENeuronSocketType::UDP)
	{
		// start listen at InPort
		refSocket = ::BRStartUDPServiceAt(InPort);
		if (refSocket == nullptr)
		{
			FString errMsg = ::BRGetLastErrorMessage();
			UE_LOG(LogNeuron, Error, TEXT("Cannot link to server: %s"), *errMsg);
		}
	}

	// link failure, return nullptr
	if (refSocket == nullptr) {
		return nullptr;
	}

	// try link to command server
	SOCKET_REF commandRefSocket = nullptr;
	if (InCommandServerPort > 0)
	{
		UE_LOG(LogNeuron, Log, TEXT("Try create connection to Command Server"));

		// connect to command server
		commandRefSocket = ::BRConnectTo(strAddr.GetData(), InCommandServerPort);
		if (commandRefSocket == nullptr)
		{
			FString errMsg = ::BRGetLastErrorMessage();
			UE_LOG(LogNeuron, Error, TEXT("Cannot link to command server: %s"), *errMsg);
		}
	}

	// new UNeuronSource and bind registers
	FNeuronSourceSharePtr newSource = MakeShareable(new FNeuronSource(InAddress, InPort, InCommandServerPort, InSocketType, refSocket, commandRefSocket));
	newSource->_PostCreation();
	// add to ConnectedSources
	{
		FScopeLock Lock(&CriticalSection);
		ConnectedSources.Add(newSource);
	}

	UE_LOG(LogNeuron, Log, TEXT("Source connection successfully established!"));

	return newSource;
}

//------------------------------------------------------------------------
FNeuronSourceSharePtr FNeuronReaderSingleton::_FindConnection(const FString& InAddress, int32 InPort, ENeuronSocketType::Type InSocketType)
{
	FScopeLock Lock(&CriticalSection);

	//
	// For-each FNeuronSource to find out some matched one.
	//
	for (FNeuronSourceSharePtr source : ConnectedSources)
	{
		if (source->Address == InAddress
			&& source->Port == InPort
			&& source->SocketType == InSocketType
			)
		{
			return source;
		}
	}
	return nullptr;
}

//------------------------------------------------------------------------

