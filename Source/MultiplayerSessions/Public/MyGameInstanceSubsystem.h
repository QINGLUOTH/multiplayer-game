// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "OnlineSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"  // �Ự�ӿ�ͷ�ļ�
#include "Public\OnlineSessionSettings.h"  // FOnlineSessionSettings

#include "MyGameInstanceSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMultiplayerOnStartSessionCompleteDelegate, bool, bWasSuccessful);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMultiplayerOnCreateSessionCompleteDelegate, bool, bWasSuccessful);
DECLARE_MULTICAST_DELEGATE_TwoParams(MultiplayerOnFindSessionCompleteDelegate, const TArray<FOnlineSessionSearchResult>& SessionResult, bool bWasSuccessful);
DECLARE_MULTICAST_DELEGATE_OneParam(MultiplayerOnJoinSessionCompleteDelegate, EOnJoinSessionCompleteResult::Type Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMultiplayerOnDestroySessionCompleteDelegate, bool, bWasSuccessful);

/**
 *
 */
UCLASS()
class MULTIPLAYERSESSIONS_API UMyGameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	UMyGameInstanceSubsystem();

	//
	// To handle session functionality. The Menu class will call these
	// NumPublicConnections���������
	// MatchType���ӵ�����, ����
	//
	void CreateSession(int32 NumPublicConnections, FString MatchType);
	void FindSessions(int32 MaxSearchResults);
	void JoinSession(const FOnlineSessionSearchResult& SessionResult);
	void DestroySession();
	void StartSession();

	FMultiplayerOnStartSessionCompleteDelegate  MultiplayerOnStartSessionCompleteDelegate;
	FMultiplayerOnCreateSessionCompleteDelegate multiplayerOnCreateSessionCompleteDelegate;
	MultiplayerOnFindSessionCompleteDelegate OnFindSessionCompleteDelegate;
	MultiplayerOnJoinSessionCompleteDelegate OnJoinSessionCompleteDelegate;
	FMultiplayerOnDestroySessionCompleteDelegate MultiplayerOnDestroySessionCompleteDelegate;

protected:

	//
	// Internal callbacks for the delegates we'll add to the Online Session Interface delegate list.
	// Thise don't need to be called outside this class.
	//
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	void OnFindSessionsComplete(bool bWasSuccessful);
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
	void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);
	void OnStartSessionComplete(FName SessionName, bool bWasSuccessful);

private:
	//
	// To add to the Online Session Interface delegate list.
	// We'll bind our MultiplayerSessionsSubsystem internal callbacks to these.
	//
	FOnCreateSessionCompleteDelegate CreateSessionCompleteDelegate;
	FDelegateHandle CreateSessionCompleteDelegateHandle;
	FOnFindSessionsCompleteDelegate FindSessionsCompleteDelegate;
	FDelegateHandle FindSessionsCompleteDelegateHandle;
	FOnJoinSessionCompleteDelegate JoinSessionCompleteDelegate;
	FDelegateHandle JoinSessionCompleteDelegateHandle;
	FOnDestroySessionCompleteDelegate DestroySessionCompleteDelegate;
	FDelegateHandle DestroySessionCompleteDelegateHandle;
	FOnStartSessionCompleteDelegate StartSessionCompleteDelegate;
	FDelegateHandle StartSessionCompleteDelegateHandle;

	IOnlineSessionPtr SessionInterface;
	//TSharedPtr<FOnlineSessionSettings> SessionSettings;
	// ��find session���ҽ�������Զ�ע��
	TSharedPtr<FOnlineSessionSearch> SessionSearch;

	int32 NumOfPublicConnections{ 4 };
	FString TypeOfMatch{ TEXT("FreeForAll") };
	bool bCreateSessionOnDestroy = false;
};

