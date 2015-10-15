#pragma once

#include "NeuronEditorPrivatePCH.h"


/** Neuron information track center
*	Used for display neuron link status, raw datas and show debug-skeleton.
*/
class SNeuronTrackWidget
	: public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SNeuronTrackWidget)
	{ }
	SLATE_END_ARGS()

	~SNeuronTrackWidget();

	/** Widget constructor
	*/
	void Construct(const FArguments& Args);

private:

	/** Tracking source
	*/
	FNeuronSourceSharePtr TrackingSource;

	/** Tracking source actor
	*/
	FNeuronSourceActorSharePtr TrackingSourceActor;

	// delegate instances
	/** raw - this::_OnTrackSourceDisconnect */
	FDelegateHandle SourceDisconnectDelegate;
	/** raw - this::__OnTrackSourceActorSuspend */
	FDelegateHandle SourceActorSuspendDelegate;
	/** raw - this::__OnTrackSourceActorResumed */
	FDelegateHandle SourceActorResumeDelegate;

	/** Information text block
	*/
	TSharedPtr<STextBlock> InfoTextBlock;

public:

	/** Change tracking source and actor.
	*/
	void SetTracking(FNeuronSourceSharePtr InSource, FNeuronSourceActorSharePtr InSourceActor);

	// Begin SWidget interfaces
	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;
	// End SWidget interfaces

private:

	/** Track source invalidate
	*	All informations in this tracker will be invalid.
	*/
	void _OnTrackSourceDisconnect(FNeuronSourceSharePtr InSource);

	/** Track source actor suspend
	*/
	void _OnTrackSourceActorSuspend(FNeuronSourceActorSharePtr InSourceActor);

	/** Track source actor new or resumed
	*/
	void _OnTrackSourceActorResumed(FNeuronSourceActorSharePtr InSourceActor);

};

