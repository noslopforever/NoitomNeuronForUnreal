using UnrealBuildTool;

// NeuronDataReaderSDK integration
//
// We need these paths match Noitom's NeuronDataReader SDK.
//
// The UnrealEngine's directory will be like this after our modifications.
// /Engine
//      /Binaries
//          /ThirdParty
//              /NeuronDataReaderSDK ** (copy from NeuronDataReaderSDK)
//                  /Windows
//                      /x86
//                      /x64
//                  /Mac
//      /Source
//          /ThirdParty
//              /NeuronDataReaderSDK ** (NeuronSDK)
//                  /NeuronDataReader_Mac
//                      /include
//                      /dylib
//                      /bundle
//                  /NeuronDataReader_Windows
//                      /include
//                      /lib
//                          /x86
//                          /x64
//

//
// NOTE by noslopforever @ 2015-9-11 v0.1
//     - current NeuronDataReader SDK version is 'beta 11' (Release date: 30.4.2015)
//

public class NeuronDataReaderSDK : ModuleRules
{
    public NeuronDataReaderSDK(TargetInfo Target)
    {
        Type = ModuleType.External;

        // TODO by noslopforever @ 2015-9-11 v0.1 : Add Mac support

        // base path of runtime library
        string dllPath = "$(EngineDir)/Binaries/ThirdParty/NeuronDataReaderSDK/";
        // base path of this Module
        string sdkDir = UEBuildConfiguration.UEThirdPartySourceDirectory + "NeuronDataReaderSDK/";

        // add platform modifier to the paths
        if (Target.Platform == UnrealTargetPlatform.Win64
            || Target.Platform == UnrealTargetPlatform.Win32)
        {
            sdkDir += "NeuronDataReader_Windows/";
            dllPath += "Windows/";
        }
        PublicIncludePaths.Add(sdkDir + "include");

        // add x86/x64 modifier to the paths
        string libraryPath = sdkDir + "/lib/";
        if ((Target.Platform == UnrealTargetPlatform.Win64))
        {
            libraryPath += "x64/";
            dllPath += "x64/";
        }
        else if ((Target.Platform == UnrealTargetPlatform.Win32))
        {
            libraryPath += "x86/";
            dllPath += "x86/";
        }

        // add paths to UE build environment
        const string libraryName = "NeuronDataReader.lib";
        const string dllName = "NeuronDataReader.dll";

        PublicLibraryPaths.Add(libraryPath);
        PublicAdditionalLibraries.Add(libraryName);

        PublicDelayLoadDLLs.Add(dllName);
        RuntimeDependencies.Add(new RuntimeDependency(dllPath + dllName));
    }
}