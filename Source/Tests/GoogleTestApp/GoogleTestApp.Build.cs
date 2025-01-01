// (C) ToasterCat Studios 2024

namespace UnrealBuildTool.Rules
{
	public class GoogleTestApp : ModuleRules
	{
		public GoogleTestApp(ReadOnlyTargetRules Target) : base(Target)
		{
			PrivateDependencyModuleNames.AddRange(new string[]
			{
				"GoogleTest",
				"TPS_Multiplayer"
			});

			PrivatePCHHeaderFile = "Private/GoogleTestApp.h";
		}
	}
}