#include "MiniginPCH.h"

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include <steam_api.h>




int main(int, char*[]) {
	//initialize and run steam api
	// Initialize Steam
	bool bRet = SteamAPI_Init();
	 //Create the SteamAchievements object if Steam was successfully initialized
	if (bRet)
	{
		std::cout << "Successfully initialized steam." << std::endl;
		//g_SteamAchievements = new Achievements(g_Achievements, 4);
	}
	else 
	{
		std::cerr << "Fatal Error - Steam must be running to play this game (SteamAPI_Init() failed)." << std::endl;
		return 1;
	}
	/*else
		std::cout << "Successfully initialized steam." << std::endl;*/

	dae::Minigin engine;
	engine.Run();

	//SteamAPI_Shutdown();
    return 0;
}
