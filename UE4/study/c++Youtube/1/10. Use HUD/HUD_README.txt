Go Source file and open file witch name is same as folder

in my case titorial_of_c.h, cpp 
and add #include "Engine.h" in .h file.

after that, open Build.cs, and add
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay","UMG" });

		PrivateDependencyModuleNames.AddRange(new string[] { "Slate","SlateCore" });

. 
than, search the folder (u can open easily with folder open, than 
click the unreal file => right click => generate ~~~~







======================================================


We will make HP bar

