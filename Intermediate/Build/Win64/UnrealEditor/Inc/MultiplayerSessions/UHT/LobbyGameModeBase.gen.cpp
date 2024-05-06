// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MultiplayerSessions/Public/LobbyGameModeBase.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLobbyGameModeBase() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	MULTIPLAYERSESSIONS_API UClass* Z_Construct_UClass_ALobbyGameModeBase();
	MULTIPLAYERSESSIONS_API UClass* Z_Construct_UClass_ALobbyGameModeBase_NoRegister();
	UPackage* Z_Construct_UPackage__Script_MultiplayerSessions();
// End Cross Module References
	void ALobbyGameModeBase::StaticRegisterNativesALobbyGameModeBase()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ALobbyGameModeBase);
	UClass* Z_Construct_UClass_ALobbyGameModeBase_NoRegister()
	{
		return ALobbyGameModeBase::StaticClass();
	}
	struct Z_Construct_UClass_ALobbyGameModeBase_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ALobbyGameModeBase_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_MultiplayerSessions,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ALobbyGameModeBase_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n *\n */" },
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "LobbyGameModeBase.h" },
		{ "ModuleRelativePath", "Public/LobbyGameModeBase.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ALobbyGameModeBase_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ALobbyGameModeBase>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ALobbyGameModeBase_Statics::ClassParams = {
		&ALobbyGameModeBase::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x009002ACu,
		METADATA_PARAMS(Z_Construct_UClass_ALobbyGameModeBase_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ALobbyGameModeBase_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ALobbyGameModeBase()
	{
		if (!Z_Registration_Info_UClass_ALobbyGameModeBase.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ALobbyGameModeBase.OuterSingleton, Z_Construct_UClass_ALobbyGameModeBase_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ALobbyGameModeBase.OuterSingleton;
	}
	template<> MULTIPLAYERSESSIONS_API UClass* StaticClass<ALobbyGameModeBase>()
	{
		return ALobbyGameModeBase::StaticClass();
	}
	ALobbyGameModeBase::ALobbyGameModeBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ALobbyGameModeBase);
	ALobbyGameModeBase::~ALobbyGameModeBase() {}
	struct Z_CompiledInDeferFile_FID_ue_porject_ue_project_game_Plugins_MultiplayerSessions_Source_MultiplayerSessions_Public_LobbyGameModeBase_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_ue_porject_ue_project_game_Plugins_MultiplayerSessions_Source_MultiplayerSessions_Public_LobbyGameModeBase_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ALobbyGameModeBase, ALobbyGameModeBase::StaticClass, TEXT("ALobbyGameModeBase"), &Z_Registration_Info_UClass_ALobbyGameModeBase, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ALobbyGameModeBase), 1634063055U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_ue_porject_ue_project_game_Plugins_MultiplayerSessions_Source_MultiplayerSessions_Public_LobbyGameModeBase_h_630180799(TEXT("/Script/MultiplayerSessions"),
		Z_CompiledInDeferFile_FID_ue_porject_ue_project_game_Plugins_MultiplayerSessions_Source_MultiplayerSessions_Public_LobbyGameModeBase_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_ue_porject_ue_project_game_Plugins_MultiplayerSessions_Source_MultiplayerSessions_Public_LobbyGameModeBase_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
