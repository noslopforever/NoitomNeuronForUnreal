# NoitomNeuronForUnreal
Noitom Neuron Perception Neuron data integration plugin for UnrealEngine4. It's unofficial so please use it carefully. Thanks for Noitom's excellent work.
Please select rotation output 'ZYX' type in NeuronAxis. We only support this output type now(v0.1), for other types will spend more time for calculation at runtime.

Versions:
v0.1 2015-9-26
Based on NeuronAxis version 3.5.19.1225 and SDK Version beta 11 (@Realease Date: 2015-4-30).
I have already packed this SDK to a zip, so you could unzip NN4UDependencies.zip and copy Binaries to Engine's (or your project's) Binaries and Source to Engine's (or your project's) Source.
Or you should try migrate SDK yourself, please read "NeuronDataReaderSDK.Build.this_is_a_module_config.cs" and make pathes like which shown in it.

The first step of data integration.
Test contents were placed in %This_Plugin_Root%/Content/Meshes.
Open your NeuronAxis(I use version 3.5.19.1225), Make it broadcasting BVH (not Advanced BVH) at 7001. And open %This_Plugin_Root%/Content/Meshes/AnimBP_NeuronStandard, then play animation in NeuronAxis to see the result.
You shall connect to NeuronAxis with FNeuronReaderSingleton::GetConnectToSource, and then datas will be read to FNeuronSourceActor's buffers automaticly.
Next you should use UNeuronAnimInstance to access these FNeuronSourceActors (by index in NeuronAxis) and draw them by Animation Blueprint.

