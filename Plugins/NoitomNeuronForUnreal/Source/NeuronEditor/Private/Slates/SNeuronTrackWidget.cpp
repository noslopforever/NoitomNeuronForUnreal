#include "NeuronEditorPrivatePCH.h"
#include "SNeuronTrackWidget.h"


//------------------------------------------------------------------------
SNeuronTrackWidget::~SNeuronTrackWidget()
{
	// reset to default
	SetTracking(FNeuronSourceSharePtr(), FNeuronSourceActorSharePtr());
}

//------------------------------------------------------------------------
void SNeuronTrackWidget::Construct(const FArguments& Args)
{
	const float PaddingAmount = 2.0f;

	/*
	+-----------+-------------------+
	|			|					|
	| Link Stat	|					|
	|			|					|
	+-----------+	Skeletal		|
	|			|	View			|
	|	Track	|					|
	|	Datas	|					|
	|			|					|
	+-----------+-------------------+
	*/
	this->ChildSlot
		[
			SNew(SHorizontalBox)
			// information slot
			+ SHorizontalBox::Slot()
			.Padding(PaddingAmount)
			.FillWidth(0.4f)
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Top)
			[
				SNew(SVerticalBox)
				// link status
				+ SVerticalBox::Slot()
				.Padding(PaddingAmount)
				.AutoHeight()
				.HAlign(HAlign_Left)
				.VAlign(VAlign_Top)
				[
					SAssignNew(InfoTextBlock, STextBlock)
				]
				// raw datas
				+ SVerticalBox::Slot()
				.Padding(PaddingAmount)
				.AutoHeight()
				.HAlign(HAlign_Left)
				.VAlign(VAlign_Top)
				//[
				//]
			]
			// skeletal view
			+ SHorizontalBox::Slot()
			.Padding(PaddingAmount)
			.FillWidth(1.f)
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Top)
			//[
			//]
		];



}

//------------------------------------------------------------------------
void SNeuronTrackWidget::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	SWidget::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);

	//// try got reader module
	//INeuronReaderModule* readerModule = FModuleManager::GetModulePtr<INeuronReaderModule>("NeuronReader");
	//if (readerModule == nullptr) {
	//	return;
	//}
	//// try get singleton
	//INeuronReaderSingleton* singleton = readerModule->GetSingleton();
	//if (singleton == nullptr) {
	//	return;
	//}

	//// try get all links
	//TArray<FNeuronSourceSharePtr> sources;
	//singleton->GetSources(sources);

	// Fill informations
	if (TrackingSource.IsValid())
	{
		FString sourceInfo = FString::Printf(TEXT("Address %s, Port %d, Type %d")
			, *TrackingSource->GetAddress()
			, TrackingSource->GetPort()
			, (int32)TrackingSource->GetSocketType()
			);

		InfoTextBlock->SetText(FText::FromString(sourceInfo));
	}

	// TODO Fill actor raw
	// TODO Fill actor skeletal
}

//------------------------------------------------------------------------
void SNeuronTrackWidget::SetTracking(FNeuronSourceSharePtr InSource, FNeuronSourceActorSharePtr InSourceActor)
{
	// unregister old notifications
	if (TrackingSource.IsValid()) {
		TrackingSource->OnDisconnect.Remove(SourceDisconnectDelegate);
	}
	if (TrackingSourceActor.IsValid()) {
		TrackingSourceActor->OnSuspend.Remove(SourceActorSuspendDelegate);
		TrackingSourceActor->OnResume.Remove(SourceActorResumeDelegate);
	}

	// set new targets
	TrackingSource = InSource;
	TrackingSourceActor = InSourceActor;

	// register new notifications
	// These notifications may called at another thread.
	if (TrackingSource.IsValid()) {
		SourceDisconnectDelegate = TrackingSource->OnDisconnect.AddSP(this, &SNeuronTrackWidget::_OnTrackSourceDisconnect);
	}
	if (TrackingSourceActor.IsValid()) {
		SourceActorSuspendDelegate = TrackingSourceActor->OnSuspend.AddSP(this, &SNeuronTrackWidget::_OnTrackSourceActorSuspend);
		SourceActorResumeDelegate = TrackingSourceActor->OnResume.AddSP(this, &SNeuronTrackWidget::_OnTrackSourceActorResumed);
	}

}

//------------------------------------------------------------------------
void SNeuronTrackWidget::_OnTrackSourceDisconnect(FNeuronSourceSharePtr InSource)
{
}

//------------------------------------------------------------------------
void SNeuronTrackWidget::_OnTrackSourceActorSuspend(FNeuronSourceActorSharePtr InSourceActor)
{
}

//------------------------------------------------------------------------
void SNeuronTrackWidget::_OnTrackSourceActorResumed(FNeuronSourceActorSharePtr InSourceActor)
{
}

//------------------------------------------------------------------------
