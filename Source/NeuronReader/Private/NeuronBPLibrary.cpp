#include "NeuronReaderModulePCH.h"
#include "NeuronBPLibrary.h"
#include "NeuronInteraction.h"


//------------------------------------------------------------------------
UNeuronBPLibrary::UNeuronBPLibrary(const FObjectInitializer& PCIP)
	: Super(PCIP)
{
}

//------------------------------------------------------------------------
class USkeleton* UNeuronBPLibrary::GetNeuronStandardSkeleton()
{
	return ::LoadObject<USkeleton>(nullptr, TEXT("/NeuronForUnreal/Meshes/Skel_NeuronStandard.Skel_NeuronStandard"));
}

//------------------------------------------------------------------------
