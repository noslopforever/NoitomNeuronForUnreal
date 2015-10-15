//
// Neuron Editor module
//
// Used for :
// -   Provide Neuron Debugger Window in editor mode.
//

namespace UnrealBuildTool.Rules
{

    // Neuron Reader Module
    public class NeuronEditor : ModuleRules
    {
        public NeuronEditor(TargetInfo Target)
        {
            PrivateIncludePaths.Add("NeuronEditor/Private");

            PublicDependencyModuleNames.AddRange(
                new string[] { 
                    "Core", 
                    "CoreUObject",
                    "Engine",
                    "InputCore",
                    "NeuronReader"
                }
            );

        PrivateDependencyModuleNames.AddRange(
            new string[]
				{
		    		"Slate",
			    	"SlateCore",
                    "InputCore",
				    "AssetTools",
				    "UnrealEd",
				    "PropertyEditor",
				    "WorkspaceMenuStructure",
				    "EditorStyle"
				}
            );
        }
    }

}