#pragma once

#include "ModuleManager.h"


/** NeuronEditorModule interface
*/
class INeuronEditorModule : public IModuleInterface
{
public:
	/**
	* Get or load the Neuron Editor Module
	*
	* @return The loaded module
	*
	*/
	static inline INeuronEditorModule& Get()
	{
		return FModuleManager::LoadModuleChecked< INeuronEditorModule >("NeuronEditor");
	}

};