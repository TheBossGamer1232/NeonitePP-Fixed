#pragma once

#include "mods.h"
#include "server.h"

inline std::vector<std::wstring> gWeapons;
inline std::vector<std::wstring> gBlueprints;
inline std::vector<std::wstring> gMeshes;
inline std::vector<Player> Bots;

namespace NeoRoyale
{
	inline bool bIsInit;
	inline bool bIsStarted;
	inline bool bIsPlayerInit;

	inline bool bHasJumped;
	inline bool bHasShowedPickaxe;

	inline bool bWantsToJump;
	inline bool bWantsToSkydive;
	inline bool bWantsToOpenGlider;
	inline bool bWantsToShowPickaxe;

	inline Player NeoPlayer;

	inline void Start(const wchar_t* MapToPlayOn)
	{
		UFunctions::Travel(MapToPlayOn);
		bIsStarted = !bIsStarted;
	}

	inline void Stop()
	{
		UFunctions::Travel(FRONTEND);
		bIsStarted = false;
		bIsInit = false;
		NeoPlayer.Controller = nullptr;
		NeoPlayer.Pawn = nullptr;
		NeoPlayer.Mesh = nullptr;
		NeoPlayer.AnimInstance = nullptr;
		Bots.clear();
		gPlaylist = nullptr;
		gNeoniteLogoTexture = nullptr;
	}

	DWORD WINAPI StartKiwiThread(LPVOID) // Skyfire Event
	{
		bool bSkyfireLoaded = false;
		bool bSkyfireEnding = false;

		if (!bSkyfireLoaded)
		{
			UFunctions::LoadLevelInstance(L"/Kiwi/Levels/Kiwi_P.Kiwi_P", FVector{ 50009.137f, 49958.379f, 100026.398f }, FRotator{});
			UFunctions::LoadLevelInstance(L"/Kiwi/Levels/Kiwi_Hangar.Kiwi_Hangar", FVector{ 50009.137f, 49958.379f, 100026.398f }, FRotator{});
			UFunctions::LoadLevelInstance(L"/Kiwi/Levels/Kiwi_KevinRoom.Kiwi_KevinRoom", FVector{ 50009.137f, 49958.379f, 100026.398f }, FRotator{});
			UFunctions::LoadLevelInstance(L"/Kiwi/Levels/Kiwi_ObservationHallway.Kiwi_ObservationHallway", FVector{ 50009.137f, 49958.379f, 100026.398f }, FRotator{});
			UFunctions::LoadLevelInstance(L"/Kiwi/Levels/Kiwi_PrisonJunction.Kiwi_PrisonJunction", FVector{ 50009.137f, 49958.379f, 100026.398f }, FRotator{});
			UFunctions::LoadLevelInstance(L"/Kiwi/Levels/Kiwi_Space.Kiwi_Space", FVector{ 50009.137f, 49958.379f, 100026.398f }, FRotator{});
			UFunctions::LoadLevelInstance(L"/Kiwi/Levels/Kiwi_Tubes.Kiwi_Tubes", FVector{ 50009.137f, 49958.379f, 100026.398f }, FRotator{});
			bSkyfireLoaded = true;

			if (bSkyfireLoaded)
			{
				Sleep(5000);
				NeoPlayer.TeleportTo(FVector{ 34640.0f, 32350.0f, 100600.0f }, FRotator{ 0.0f, 270.0f, 0.0f });
				UFunctions::Play(L"LevelSequencePlayer /Kiwi/Levels/Kiwi_P.Kiwi_P.PersistentLevel.Kiwi_Master.AnimationPlayer");
				UFunctions::DestroyAllTODM();
				NeoPlayer.Summon(L"TODM_BR_Kiwi_Interior_C");
				NeoPlayer.SetLoadedApolloTerrain(false);
				Sleep(450000);
				UFunctions::UnloadStreamLevel(L"Kiwi_ObservationHallway");
				UFunctions::UnloadStreamLevel(L"Kiwi_PrisonJunction");
				UFunctions::UnloadStreamLevel(L"Kiwi_Space");
				UFunctions::UnloadStreamLevel(L"Kiwi_Tubes");
				UFunctions::UnloadStreamLevel(L"Kiwi_Lobby");
				Sleep(160000);
				bSkyfireEnding = true;
				UFunctions::UnloadStreamLevel(L"Kiwi_Hangar");
				UFunctions::UnloadStreamLevel(L"Kiwi_KevinRoom");
				NeoPlayer.SetLoadedApolloTerrain(true);
				NeoPlayer.TeleportTo(FVector{ -157521.352f, 24902.775f, 99510.869f }, FRotator{ -5.0f, -27.0f, 0.0f });
				NeoPlayer.StartSkydiving(0.0f);
				NeoPlayer.TeleportTo(FVector{ -157521.352f, 24902.775f, 99510.869f }, FRotator{ -5.0f, -27.0f, 0.0f });
				Sleep(2000);
				NeoPlayer.TeleportTo(FVector{ -157521.352f, 24902.775f, 99510.869f }, FRotator{ -5.0f, -27.0f, 0.0f });
			}
		}
		return 0;
	}

	DWORD WINAPI GiveKiwiComponents(LPVOID)
	{
		/*
		ObjectFinder EngineFinder = ObjectFinder::EntryPoint(uintptr_t(GEngine));
		ObjectFinder LocalPlayer = EngineFinder.Find(XOR(L"GameInstance")).Find(XOR(L"LocalPlayers"));
		ObjectFinder PlayerControllerFinder = LocalPlayer.Find(XOR(L"PlayerController"));
		*/

		NeoPlayer.AddComponentByClass(NeoPlayer.Controller, FindObject<UClass*>(XOR(L"BlueprintGeneratedClass /KiwiPlaylist/Gameplay/Kiwi_ControllerComponent.Kiwi_ControllerComponent_C")));
		NeoPlayer.AddComponentByClass(NeoPlayer.Controller, FindObject<UClass*>(XOR(L"BlueprintGeneratedClass /Kiwi/Gameplay/Blueprints/BP_Kiwi_Prison_ControllerComponent.BP_Kiwi_Prison_ControllerComponent_C")));
		NeoPlayer.AddComponentByClass(NeoPlayer.Controller, FindObject<UClass*>(XOR(L"BlueprintGeneratedClass /Kiwi/Gameplay/Blueprints/BP_Kiwi_PhaseSpecificControllerComponent.BP_Kiwi_PhaseSpecificControllerComponent_C")));
		NeoPlayer.AddComponentByClass(NeoPlayer.Controller, FindObject<UClass*>(XOR(L"BlueprintGeneratedClass /Kiwi/Gameplay/Blueprints/Hangar/BP_Kiwi_Hangar_ControllerComponent.BP_Kiwi_Hangar_ControllerComponent_C")));
		return 0;
	}

	inline void LoadMoreClasses()
	{
		const auto BPGClass = FindObject<UClass*>(XOR(L"Class /Script/Engine.BlueprintGeneratedClass"));

		//Mech
		UFunctions::StaticLoadObjectEasy(BPGClass,XOR(L"/Game/Athena/DrivableVehicles/Mech/TestMechVehicle.TestMechVehicle_C"));

		//Husks
		UFunctions::StaticLoadObjectEasy(BPGClass,XOR(L"/Game/Characters/Enemies/Husk/Blueprints/HuskPawn.HuskPawn_C"));
		UFunctions::StaticLoadObjectEasy(BPGClass,XOR(L"/Game/Characters/Enemies/DudeBro/Blueprints/DUDEBRO_Pawn.DUDEBRO_Pawn_C"));
		

		//CameraFilters
		UFunctions::StaticLoadObjectEasy(BPGClass, XOR(L"/Game/Creative/PostProcess/PP_FilmNoir.PP_FilmNoir_C"));
		UFunctions::StaticLoadObjectEasy(BPGClass, XOR(L"/Game/Creative/PostProcess/PP_Crazy.PP_Crazy_C"));
		UFunctions::StaticLoadObjectEasy(BPGClass, XOR(L"/Game/Creative/PostProcess/PP_Dark.PP_Dark_C"));
		UFunctions::StaticLoadObjectEasy(BPGClass, XOR(L"/Game/Creative/PostProcess/PP_HappyPlace.PP_HappyPlace_C"));
		UFunctions::StaticLoadObjectEasy(BPGClass, XOR(L"/Game/Creative/PostProcess/PP_Oak.PP_Oak_C"));
		UFunctions::StaticLoadObjectEasy(BPGClass, XOR(L"/Game/Creative/PostProcess/PP_Pixelizer.PP_Pixelizer_C"));
		UFunctions::StaticLoadObjectEasy(BPGClass, XOR(L"/Game/Creative/PostProcess/PP_Red.PP_Red_C"));
		UFunctions::StaticLoadObjectEasy(BPGClass, XOR(L"/Game/Creative/PostProcess/PP_Retro.PP_Retro_C"));
		UFunctions::StaticLoadObjectEasy(BPGClass, XOR(L"/Game/Creative/PostProcess/PP_Sepia.PP_Sepia_C"));
		UFunctions::StaticLoadObjectEasy(BPGClass, XOR(L"/Game/Creative/PostProcess/PP_Spooky.PP_Spooky_C"));
	}

	inline void InitCombos()
	{
		for (auto i = 0x0; i < GObjs->NumElements; ++i)
		{
			auto object = GObjs->GetByIndex(i);
			if (object == nullptr)
			{
				continue;
			}

			if (!Util::IsBadReadPtr(object))
			{
				auto objectFullName = GetObjectFullName(object);
				auto objectFirstName = GetObjectFirstName(object);

				if ((objectFullName.starts_with(L"AthenaGadget") || objectFirstName.starts_with(L"WID_")) && !objectFirstName.starts_with(L"Default__"))
				{
					gWeapons.push_back(objectFirstName);
				}
				else if (objectFirstName.ends_with(L"_C") && !objectFirstName.starts_with(L"Default__"))
				{
					gBlueprints.push_back(objectFirstName);
				}
				else if (objectFullName.starts_with(L"SkeletalMesh ") && !objectFirstName.starts_with(L"Default__"))
				{
					gMeshes.push_back(objectFirstName);
				}
			}
		}
	}

	inline void Thread()
	{
		//NOTE (kemo): i know this isn't the best practice but it does the job on another thread so it's not a frezzing call
		while (true)
		{
			/*
			if (NeoPlayer.Pawn && GetAsyncKeyState(0x31) // 1 key )
			{
				if (!NeoPlayer.IsInAircraft())
				{
					if (!bHasShowedPickaxe)
					{
						bHasShowedPickaxe = !bHasShowedPickaxe;
						NeoPlayer.StopMontageIfEmote();
						bWantsToShowPickaxe = true;
					}
				}
			}
			else bHasShowedPickaxe = false;
			*/
			//	void OpenLevel(struct UObject* WorldContextObject, struct FName LevelName, bool bAbsolute, struct FString Options); // Function Engine.GameplayStatics.OpenLevel // (Final|Native|Static|Public|BlueprintCallable) // @ game+0x638115c

			if (NeoPlayer.Pawn && GetAsyncKeyState(VK_F6))
			{

				ObjectFinder EngineFinder = ObjectFinder::EntryPoint(uintptr_t(GEngine));
				ObjectFinder GameViewPortClientFinder = EngineFinder.Find(XOR(L"GameViewport"));
				ObjectFinder WorldFinder = GameViewPortClientFinder.Find(XOR(L"World"));
				
				auto Default__GameplayStatics = FindObject<UObject*>(L"GameplayStatics /Script/Engine.Default__GameplayStatics");
				auto fn = FindObject<UFunction*>(XOR(L"Function /Script/Engine.GameplayStatics.LoadStreamLevel"));
				
				FName map = KismetFunctions::GetFName(RIFT_TOUR_BUBBLES_MAP);

				FLatentActionInfo LatentInfo{};
				
				UGameplayStatics_LoadStreamLevel_Params params;
				params.WorldContextObject = WorldFinder.GetObj();
				params.LevelName = map;
				params.bMakeVisibleAfterLoad = true;
				params.bShouldBlockOnLoad = true;
				params.LatentInfo = LatentInfo;
				//MessageBoxA(nullptr, XOR("Called a special function!"), XOR("Carbon"), MB_OK);
				
				ProcessEvent(Default__GameplayStatics, fn, &params);
			}
			
			if (NeoPlayer.Pawn && GetAsyncKeyState(VK_F7))
			{

			}
			
			if (NeoPlayer.Pawn && GetAsyncKeyState(VK_F9))
			{
				NeoPlayer.ExecuteConsoleCommand(XOR(L"camera firstperson"));
			}
			
			if (NeoPlayer.Pawn && GetAsyncKeyState(VK_F3))
			{
				Stop();
				break;
			}

			Sleep(1000 / 30);
		}
	}

	/*inline void StartBuffet()
	{
		auto BP_Buffet_Master_Scripting_C = FindObject<UObject*>(XOR(L"BP_Buffet_Master_Scripting_C /Buffet/Levels/Buffet_P.Buffet_P.PersistentLevel.BP_Event_Master_Scripting_2"));
		auto startevent = FindObject<UFunction*>(XOR(L"Function /Buffet/Gameplay/Blueprints/BP_Buffet_Master_Scripting.BP_Buffet_Master_Scripting_C.startevent"));

		ProcessEvent(BP_Buffet_Master_Scripting_C, startevent, nullptr);
	}*/

	inline void Init()
	{
		Console::CheatManager();

		UFunctions::DestroyAllHLODs();

		NeoPlayer.Summon(XOR(L"PlayerPawn_Athena_C"));

		NeoPlayer.Pawn = ObjectFinder::FindActor(XOR(L"PlayerPawn_Athena_C"));

		NeoPlayer.Authorize();

		if (NeoPlayer.Pawn)
		{
			NeoPlayer.Possess();

			NeoPlayer.ShowSkin();

			//NeoPlayer.ShowPickaxe();

			NeoPlayer.ToggleInfiniteAmmo();

			//NeoPlayer.ApplyOverride();

			//LOL
			NeoPlayer.ExecuteConsoleCommand(XOR(L"god"));
			NeoPlayer.SetMovementSpeed(1.1);
			UFunctions::SetPlaylist();

			UFunctions::SetGamePhase();
			
			//InitCombos();

			UFunctions::StartMatch();

			UFunctions::ServerReadyToStartMatch();

			CreateThread(nullptr, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(&Thread), nullptr, NULL, nullptr);

			UFunctions::ConsoleLog(XOR(L"\n\nWelcome to Carbon V1.4\nMade with ♥ By Kemo (@xkem0x), Timmy(@mawmet) and PeQu(ImPeQu)")); //feel free to add your credits when you do something

			//ConnectServer();

			bIsInit = !bIsInit;
		}
	}
}
