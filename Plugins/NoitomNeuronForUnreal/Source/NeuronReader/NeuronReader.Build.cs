//
// Neuron Reader module
//
// Used for :
// -   Link to Neuron Axis, and get notifications from it.
// -   Gain and process data from Neuron Axis.
// -   Manager links, input-sources, and other conception from Neuron.
//

namespace UnrealBuildTool.Rules
{

    // Neuron Reader Module
    public class NeuronReader : ModuleRules
    {
        public NeuronReader(TargetInfo Target)
        {
            PrivateIncludePaths.Add("NeuronReader/Private");

            PublicDependencyModuleNames.AddRange(
                new string[] { 
                    "Core", 
                    "CoreUObject",
                    "Engine",
                    "InputCore"
                }
            );

            // if Editor, include Editor module
            if (Target.Type == TargetRules.TargetType.Editor)
            {
                PublicDependencyModuleNames.Add("BlueprintGraph");
                PublicDependencyModuleNames.Add("AnimGraph");
            }

            // SDK integration
            AddThirdPartyPrivateStaticDependencies(Target, "NeuronDataReaderSDK");
        }
    }

}