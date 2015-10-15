#include "NeuronReaderModulePCH.h"
#include "NeuronReaderModule.h"
#include "Kernel/NeuronReaderSingletonPrivate.h"


//------------------------------------------------------------------------
DEFINE_LOG_CATEGORY(LogNeuron);
//------------------------------------------------------------------------
static FNeuronReaderSingleton* NeuronReaderSingleton = nullptr;
//------------------------------------------------------------------------
class FNeuronReaderModule : public INeuronReaderModule
{
private:

	/** Delay-load dynamic link library */
	void* DllHandle;

	// Begin IModuleInterface Interface
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	virtual INeuronReaderSingleton* GetSingleton() override {
		return NeuronReaderSingleton;
	}
	// End IModuleInterface Interface

};

//------------------------------------------------------------------------
IMPLEMENT_MODULE(FNeuronReaderModule, NeuronReader);
//------------------------------------------------------------------------
void FNeuronReaderModule::StartupModule()
{
	// load dynamic libraries
#if PLATFORM_WINDOWS
#if PLATFORM_64BITS
	FString DllPath(FPaths::Combine(*FPaths::EngineDir(), TEXT("Binaries/ThirdParty/NeuronDataReaderSDK/Windows/x64")));
#else
	FString DllPath(FPaths::Combine(*FPaths::EngineDir(), TEXT("Binaries/ThirdParty/NeuronDataReaderSDK/Windows/x86")));
#endif
	DllHandle = FPlatformProcess::GetDllHandle(*FPaths::Combine(*DllPath, TEXT("NeuronDataReader.dll")));
#elif PLATFORM_MAC
	DllHandle = FPlatformProcess::GetDllHandle(TEXT("NeuronDataReader.dylib"));
#endif

	// not found in engine binaries, try it in game binaries.
	if (DllHandle == nullptr)
	{
#if PLATFORM_WINDOWS
#if PLATFORM_64BITS
		FString DllPath(FPaths::Combine(*FPaths::GameDir(), TEXT("Binaries/ThirdParty/NeuronDataReaderSDK/Windows/x64")));
#else
		FString DllPath(FPaths::Combine(*FPaths::GameDir(), TEXT("Binaries/ThirdParty/NeuronDataReaderSDK/Windows/x86")));
#endif
		DllHandle = FPlatformProcess::GetDllHandle(*FPaths::Combine(*DllPath, TEXT("NeuronDataReader.dll")));
#elif PLATFORM_MAC
		DllHandle = FPlatformProcess::GetDllHandle(TEXT("NeuronDataReader.dylib"));
#endif
	}

	// TODO noslopforever : if dll is not valid, disable all functional and error output!
	if (DllHandle == nullptr)
	{
		return;
	}

	// Create singleton
	NeuronReaderSingleton = new FNeuronReaderSingleton();
}

//------------------------------------------------------------------------
void FNeuronReaderModule::ShutdownModule()
{
	// kill singleton
	delete NeuronReaderSingleton;

	// Free dynamic libraries
	if (DllHandle != nullptr)
	{
		FPlatformProcess::FreeDllHandle(DllHandle);
		DllHandle = nullptr;
	}
}

//------------------------------------------------------------------------
static void NeuronTestTCPLink(const TArray<FString>& Args)
{
	if (Args.Num() < 2)
	{
		UE_LOG(LogNeuron, Log, TEXT("Parameters not matched : NeuronTestTCPLink 'addr' 'port' '[cmdPort]' "));
		return;
	}
	FString addr = *Args[0];
	int32 port = FCString::Atoi(*Args[1]);

	int32 cmdPort = 0;
	if (Args.Num() >= 3) {
		cmdPort = FCString::Atoi(*Args[2]);
	}

	INeuronReaderSingleton* singleton = INeuronReaderModule::Get().GetSingleton();
	FNeuronSourceSharePtr source = singleton->GetConnectToSource(addr, port, cmdPort, ENeuronSocketType::TCP);
	singleton->DisconnectSource(source);
}
FAutoConsoleCommand GNeuronTestTCPLinkCmd(TEXT("NeuronTestTCPLink"), TEXT("Test Neuron TCP link : 'addr' 'port' '[cmdPort]'"), FConsoleCommandWithArgsDelegate::CreateStatic(&NeuronTestTCPLink));
//------------------------------------------------------------------------
static void NeuronTestUDPLink(const TArray<FString>& Args)
{
	if (Args.Num() < 1)
	{
		UE_LOG(LogNeuron, Log, TEXT("Parameters not matched : NeuronTestUDPLink 'port' '[cmdPort]' "));
		return;
	}
	int32 port = FCString::Atoi(*Args[0]);

	int32 cmdPort = 0;
	if (Args.Num() >= 2) {
		cmdPort = FCString::Atoi(*Args[1]);
	}

	INeuronReaderSingleton* singleton = INeuronReaderModule::Get().GetSingleton();
	FNeuronSourceSharePtr source = singleton->GetConnectToSource(TEXT(""), port, cmdPort, ENeuronSocketType::UDP);
	singleton->DisconnectSource(source);
}
FAutoConsoleCommand GNeuronTestUDPLinkCmd(TEXT("NeuronTestUDPLink"), TEXT("Test Neuron UDP link : 'port' '[cmdPort]'"), FConsoleCommandWithArgsDelegate::CreateStatic(&NeuronTestUDPLink));
//------------------------------------------------------------------------
