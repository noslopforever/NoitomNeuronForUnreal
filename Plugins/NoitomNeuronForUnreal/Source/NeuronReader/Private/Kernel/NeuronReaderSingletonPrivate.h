#pragma once

#include "NeuronGlobal.h"


class FNeuronReaderSingleton
	: public INeuronReaderSingleton
	, FTickableGameObject
{
public:
	FNeuronReaderSingleton();
	virtual ~FNeuronReaderSingleton();

private:

	/** source that already connected */
	TArray<FNeuronSourceSharePtr> ConnectedSources;

	/** critical section for ConnectedSources */
	FCriticalSection CriticalSection;

public:

	// Begin INeuronReaderSingleton interfaces
	virtual void GetSources(TArray<FNeuronSourceSharePtr>& OutSources) override;
	virtual FNeuronSourceSharePtr GetConnectToSource(const FString& InAddress, int32 InPort, int32 InCommandPort, ENeuronSocketType::Type InSocketType) override;
	virtual void DisconnectSource(FNeuronSourceSharePtr InSource) override;
	// End INeuronReaderSingleton interfaces

	// Begin FTickableGameObject interfaces
	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override;
	virtual bool IsTickable() const override {
		return true;
	}
	virtual bool IsTickableWhenPaused() const override {
		return true;
	}
	virtual bool IsTickableInEditor() const override {
		return true;
	}
	// End FTickableGameObject interfaces

private:

	/** real create connection
	*/
	FNeuronSourceSharePtr _CreateConnection(const FString& InAddress, int32 InPort, int32 InCommandPort, ENeuronSocketType::Type InSocketType);

	/** find exist connection
	*/
	FNeuronSourceSharePtr _FindConnection(const FString& InAddress, int32 InPort, ENeuronSocketType::Type InSocketType);

};
