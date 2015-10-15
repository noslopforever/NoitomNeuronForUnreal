#pragma once

#include "ModuleManager.h"

#include "Kernel/NeuronGlobal.h"


/** NeuronReaderModule interface
*/
class INeuronReaderModule : public IModuleInterface
{
public:
	/**
	* Get or load the Neuron Reader Module
	*
	* @return The loaded module
	*
	*/
	static inline INeuronReaderModule& Get()
	{
		return FModuleManager::LoadModuleChecked< INeuronReaderModule >("NeuronReader");
	}

	/**
	* Get the Neuron Reader Singleton
	*
	* @return The Neuron Reader Singleton
	*
	*/
	virtual INeuronReaderSingleton* GetSingleton() = 0;

};