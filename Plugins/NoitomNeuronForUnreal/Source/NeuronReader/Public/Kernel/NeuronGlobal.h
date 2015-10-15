#pragma once

#include "NeuronCommon.h"


/**
* A singleton class that takes care of kernel NeuronReader integrations
*/
class NEURONREADER_API INeuronReaderSingleton
{
public:

	/**
	* Virtual Destructor
	*/
	virtual ~INeuronReaderSingleton() {};

	/** Get all sources
	*/
	virtual void GetSources(TArray<FNeuronSourceSharePtr>& OutSources) = 0;

	/** return instantly if exist, or create a new one.
	*	\remarks MUST called at GameThread
	*/
	virtual FNeuronSourceSharePtr GetConnectToSource(const FString& InAddress, int32 InPort, int32 InCommandPort, ENeuronSocketType::Type InSocketType) = 0;

	/** disconnect source
	*	\remarks MUST called at GameThread
	*/
	virtual void DisconnectSource(FNeuronSourceSharePtr InSource) = 0;

	// TODO by noslopforever @ 2015-9-13 v0.1 : get source info blablabla...



	//
	// Global Callbacks
	//
	/** Called when source create
	*/
	static FNeuronSourceSignature OnSourceNew;
	/** Called when source removed
	*/
	static FNeuronSourceSignature OnSourceRemove;
	/** 
	*/
	static FNeuronSourceActorSignature OnSourceActorEnter;
	/** 
	*/
	static FNeuronSourceActorSignature OnSourceActorSuspend;
	/** 
	*/
	static FNeuronSourceActorSignature OnSourceActorResume;
	/** 
	*/
	static FNeuronSourceActorSignature OnSourceActorLeave;

};
