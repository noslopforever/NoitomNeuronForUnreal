# NoitomNeuronForUnreal
Noitom Neuron Perception Neuron data integration plugin for UnrealEngine4. It's unofficial so please use it carefully. Thanks for Noitom's excellent work.
Please select rotation output 'ZYX' type in NeuronAxis. We only support this output type now(v0.1), for other types will spend more time for calculation at runtime.

Versions:
v 0.1 2015-9-26
The first step of data integration.
You shall connect to NeuronAxis with FNeuronReaderSingleton::GetConnectToSource, and then datas will be read to FNeuronSourceActor's buffers automaticly.
Next we should use UNeuronAnimInstance to access these FNeuronSourceActors (by index in NeuronAxis) and draw them by Animation Blueprint.
