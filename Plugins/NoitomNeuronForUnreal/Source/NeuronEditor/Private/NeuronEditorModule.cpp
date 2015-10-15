#include "NeuronEditorPrivatePCH.h"

#include "NeuronEditorModule.h"

#include "Slates/SNeuronTrackWidget.h"


//------------------------------------------------------------------------
class FNeuronEditorModule : public INeuronEditorModule
{
private:
	// Begin IModuleInterface Interface
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	// End IModuleInterface Interface

};

//------------------------------------------------------------------------
IMPLEMENT_MODULE(FNeuronEditorModule, NeuronEditor);
//------------------------------------------------------------------------
void FNeuronEditorModule::StartupModule()
{
	// register editor and browsers
}

//------------------------------------------------------------------------
void FNeuronEditorModule::ShutdownModule()
{
	// unregister editor and browsers
}

//------------------------------------------------------------------------
static void NeuronTestOpenTrackerWindow(const TArray<FString>& Args)
{
	if (Args.Num() <= 0) {
		return;
	}
	TSharedRef<SNeuronTrackWidget> trackWidget = SNew(SNeuronTrackWidget);
	TSharedRef<SWindow> NewWindow = SNew(SWindow)
		.ClientSize(FVector2D(720, 768))
		.Title(FText::FromString(TEXT("Test Tracker Window")));
	NewWindow->SetContent(trackWidget);

	int32 port = FCString::Atoi(*Args[0]);

	// get singleton
	INeuronReaderSingleton* singleton = INeuronReaderModule::Get().GetSingleton();
	if (singleton == nullptr) {
		return;
	}

	// set tracking objects
	FNeuronSourceSharePtr source = singleton->GetConnectToSource(TEXT(""), port, 0, ENeuronSocketType::UDP);
	trackWidget->SetTracking(source, FNeuronSourceActorSharePtr());

	FSlateApplication::Get().AddWindow(NewWindow);
}
FAutoConsoleCommand GNeuronTestUDPLinkCmd(TEXT("NeuronTestOpenTrackerWindow"), TEXT("Open Tracker Window : [ip] [port]"), FConsoleCommandWithArgsDelegate::CreateStatic(&NeuronTestOpenTrackerWindow));
//------------------------------------------------------------------------
