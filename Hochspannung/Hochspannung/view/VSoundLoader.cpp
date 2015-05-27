#include "VSoundLoader.h"

NAMESPACE_VIEW_B


CScene* VSoundLoader::scene = nullptr;
DEBUG_EXPRESSION(bool VSoundLoader::initDone = false);
DEBUG_EXPRESSION(static const char* const assertMsg = "SoundLoader is not initialized");

CAudio VSoundLoader::backgroundMusicIngameStart;
std::unordered_map<VSoundLoader::SoundEffect, CAudio> VSoundLoader::soundeffects;
std::unordered_map<VSoundLoader::SoundEffect, CPlacement*> VSoundLoader::soundeffectsLastPlacements;


void VSoundLoader::setSoundEffectHelper(const SoundEffect soundEffect, const std::string& filename)
{
	soundeffects[soundEffect].Init(&(std::string("sounds/") + filename + std::string(".wav"))[0]);
	soundeffects[soundEffect].SetVolume(1.0f);
	scene->AddAudio(&soundeffects[soundEffect]);
	soundeffectsLastPlacements[soundEffect] = nullptr;
}

void VSoundLoader::init(CScene* scene)
{
	VSoundLoader::scene = scene;

	backgroundMusicIngameStart.Init("sounds/ambient-02-vip.wav");
	backgroundMusicIngameStart.SetVolume(1.0f);
	scene->AddAudio(&backgroundMusicIngameStart);

	setSoundEffectHelper(BUILDING_PLACED, "createObject");
	setSoundEffectHelper(TRASSE_PLACED, "createTrasse");
	setSoundEffectHelper(OBJECT_REMOVED, "delObject");
	setSoundEffectHelper(OPERATION_CANCELED, "click");
	setSoundEffectHelper(POWERPLANT_SWITCH_ON, "gui_switch");
	setSoundEffectHelper(POWERPLANT_SWITCH_OFF, "gui_switch");
	setSoundEffectHelper(SABOTAGE_RECEIVED, "sabotage_received");
	setSoundEffectHelper(SABOTAGE_EMITTED, "click");
	setSoundEffectHelper(ENERGY_LOW, "lowEnergy");
	setSoundEffectHelper(GAME_OVER, "click");
	setSoundEffectHelper(GAME_WON, "game_won");

	DEBUG_EXPRESSION(initDone = true);
}

void VSoundLoader::playBackgroundMusicIngame()
{
	ASSERT(initDone, assertMsg);

	backgroundMusicIngameStart.Loop();
}

void VSoundLoader::playSoundeffect(const SoundEffect soundEffect, CPlacement* placement)
{
	ASSERT(initDone, assertMsg);

	//If no placement is given, add to scene
	if (placement == nullptr)
	{
		static SoundEffect previousSoundEffect = CASTS<SoundEffect>(-1);

		//Sub previous soundeffect from scene
		if (previousSoundEffect != -1)
		{
			scene->SubAudio(&soundeffects[previousSoundEffect]);
		}

		scene->AddAudio(&soundeffects[soundEffect]);
		soundeffects[soundEffect].Start();
		previousSoundEffect = soundEffect;
	}
	else
	{
		//Sub Audio from previous placement
		if (soundeffectsLastPlacements[soundEffect] != nullptr)
		{
			soundeffectsLastPlacements[soundEffect]->SubAudio(&soundeffects[soundEffect]);
		}

		placement->AddAudio(&soundeffects[soundEffect]);
		soundeffects[soundEffect].Start();
		soundeffectsLastPlacements[soundEffect] = placement;
	}
}

NAMESPACE_VIEW_E
