// (C) ToasterCat Studios 2024

using UnrealBuildTool;

public class TPS_Multiplayer : ModuleRules
{
	public TPS_Multiplayer(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", "CoreUObject", "Engine", "InputCore", "UMG", "GameplayAbilities"
		});

		PrivateDependencyModuleNames.AddRange(new string[] {
			"EnhancedInput",
			"GameplayAbilities", "GameplayTags", "GameplayTasks"
	//		"OnlineSybsystem"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
