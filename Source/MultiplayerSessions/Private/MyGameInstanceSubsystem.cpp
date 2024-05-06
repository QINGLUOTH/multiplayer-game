// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstanceSubsystem.h"

UMyGameInstanceSubsystem::UMyGameInstanceSubsystem() :
	CreateSessionCompleteDelegate(FOnCreateSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnCreateSessionComplete)),
	FindSessionsCompleteDelegate(FOnFindSessionsCompleteDelegate::CreateUObject(this, &ThisClass::OnFindSessionsComplete)),
	JoinSessionCompleteDelegate(FOnJoinSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnJoinSessionComplete)),
	DestroySessionCompleteDelegate(FOnDestroySessionCompleteDelegate::CreateUObject(this, &ThisClass::OnDestroySessionComplete)),
	StartSessionCompleteDelegate(FOnStartSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnStartSessionComplete))
{
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if (Subsystem)
	{
		SessionInterface = Subsystem->GetSessionInterface();
	}
}

void UMyGameInstanceSubsystem::CreateSession(int32 NumPublicConnections, FString MatchType)
{
	// 创建session
	// 判断  SessionInterface是否可用
	if (!SessionInterface.IsValid()) {
		return;
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("CreateSession")));

	//  判断是否已经创建session, 如果创建销毁   
	auto ExitstingSession = SessionInterface->GetNamedSession(NAME_GameSession);
	if (ExitstingSession != NULL) {
		// 销毁session
		this->NumOfPublicConnections = NumPublicConnections;
		this->TypeOfMatch = MatchType;
		this->bCreateSessionOnDestroy = true;
		DestroySession();
	}
	// 设置委托
	CreateSessionCompleteDelegateHandle = SessionInterface->AddOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegate);
	// 设置
	TSharedPtr<FOnlineSessionSettings> SessionSettings = MakeShareable(new FOnlineSessionSettings());
	SessionSettings->Set(FName("MatchType"), MatchType, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
	ULocalPlayer* player = GetWorld()->GetFirstLocalPlayerFromController();
	// 如果名字为steam表示不使用局域网连接
	SessionSettings->bIsLANMatch = true;
	SessionSettings->NumPublicConnections = 4;  // 可同时4个进行连接
	SessionSettings->bAllowJoinInProgress = true;  // 是否可以加入(在会话运行中, 玩家是否可以加入)
	SessionSettings->bAllowJoinViaPresence = true;  // 允许通过状态加入(可以根据地区搜索对话)
	SessionSettings->bShouldAdvertise = true;  // 是否允许steam发布会话
	SessionSettings->bUsesPresence = true;  // 是否显示用户状态
	SessionSettings->bUseLobbiesIfAvailable = true;  // 如果有大厅，使用大厅
	SessionSettings->BuildUniqueId = 1;  //用于防止不同的构建在搜索期间看到彼此
	// player->GetPreferredUniqueNetId()是session网络的唯一id, NAME_GameSession是session名, SessionSettings是session的设置
	if (!SessionInterface->CreateSession(*player->GetPreferredUniqueNetId(), NAME_GameSession, *SessionSettings)) {
		// 清除委托
		SessionInterface->ClearOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegateHandle);

		// 失败
		multiplayerOnCreateSessionCompleteDelegate.Broadcast(false);
	}
}

void UMyGameInstanceSubsystem::FindSessions(int32 MaxSearchResults)
{
	// 先查找可加入的session
	if (!SessionInterface.IsValid()) {
		// 判断SessionInterface是否可用
		return;
	}

	if (!this->SessionInterface) {
		this->OnFindSessionCompleteDelegate.Broadcast(TArray<FOnlineSessionSearchResult>(), false);
		return;
	}

	// 绑定delegate
	FindSessionsCompleteDelegateHandle = SessionInterface->AddOnFindSessionsCompleteDelegate_Handle(FindSessionsCompleteDelegate);
	// 创建SessionSearch
	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	SessionSearch->bIsLanQuery = false;  // 是否局域网查找
	SessionSearch->MaxSearchResults = MaxSearchResults;  // 最大搜索结果
	// SEARCH_PRESENCE仅搜索存在的会话(值为true or false), 用于查找匹配服务器的查询
	SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
	const ULocalPlayer* player = GetWorld()->GetFirstLocalPlayerFromController();
	if (!SessionInterface->FindSessions(*player->GetPreferredUniqueNetId(), SessionSearch.ToSharedRef())) {
		SessionInterface->ClearOnFindSessionsCompleteDelegate_Handle(FindSessionsCompleteDelegateHandle);

		OnFindSessionCompleteDelegate.Broadcast(TArray<FOnlineSessionSearchResult>(), false);
	}
}

void UMyGameInstanceSubsystem::JoinSession(const FOnlineSessionSearchResult& SessionResult)
{
	if (!SessionInterface.IsValid()) {
		OnJoinSessionCompleteDelegate.Broadcast(EOnJoinSessionCompleteResult::UnknownError);
		return;
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("JoinSession")));
	const ULocalPlayer* localPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	JoinSessionCompleteDelegateHandle = SessionInterface->AddOnJoinSessionCompleteDelegate_Handle(JoinSessionCompleteDelegate);
	if (!SessionInterface->JoinSession(*localPlayer->GetPreferredUniqueNetId(), NAME_GameSession, SessionResult)) {
		SessionInterface->ClearOnJoinSessionCompleteDelegate_Handle(JoinSessionCompleteDelegateHandle);
		OnJoinSessionCompleteDelegate.Broadcast(EOnJoinSessionCompleteResult::UnknownError);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("JoinSession false")));
	}
}

void UMyGameInstanceSubsystem::DestroySession()
{
	if (!SessionInterface.IsValid()) {
		this->MultiplayerOnDestroySessionCompleteDelegate.Broadcast(false);
		return;
	}

	this->DestroySessionCompleteDelegateHandle = this->SessionInterface->AddOnDestroySessionCompleteDelegate_Handle(this->DestroySessionCompleteDelegate);

	if (!this->SessionInterface->DestroySession(NAME_GameSession)) {
		this->SessionInterface->ClearOnDestroySessionCompleteDelegate_Handle(this->DestroySessionCompleteDelegateHandle);
		this->MultiplayerOnDestroySessionCompleteDelegate.Broadcast(false);
	}
}

void UMyGameInstanceSubsystem::StartSession()
{
}

void UMyGameInstanceSubsystem::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	if (this->SessionInterface) {
		this->SessionInterface->ClearOnCreateSessionCompleteDelegate_Handle(this->CreateSessionCompleteDelegateHandle);
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("OnCreateSessionComplete")));

	multiplayerOnCreateSessionCompleteDelegate.Broadcast(bWasSuccessful);
}

void UMyGameInstanceSubsystem::OnFindSessionsComplete(bool bWasSuccessful)
{

	if (SessionInterface) {
		SessionInterface->ClearOnFindSessionsCompleteDelegate_Handle(this->FindSessionsCompleteDelegateHandle);
	}
	OnFindSessionCompleteDelegate.Broadcast(SessionSearch->SearchResults, bWasSuccessful);

}

void UMyGameInstanceSubsystem::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if (SessionInterface) {
		SessionInterface->ClearOnJoinSessionCompleteDelegate_Handle(JoinSessionCompleteDelegateHandle);
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("OnJoinSessionComplete")));
	OnJoinSessionCompleteDelegate.Broadcast(Result);
}

void UMyGameInstanceSubsystem::OnDestroySessionComplete(FName SessionName, bool bWasSuccessful)
{
	if (SessionInterface) {
		this->SessionInterface->ClearOnDestroySessionCompleteDelegate_Handle(this->DestroySessionCompleteDelegateHandle);
	}

	if (bWasSuccessful || this->bCreateSessionOnDestroy) {
		this->bCreateSessionOnDestroy = false;
		this->CreateSession(NumOfPublicConnections, TypeOfMatch);
	}

	MultiplayerOnDestroySessionCompleteDelegate.Broadcast(bWasSuccessful);
}

void UMyGameInstanceSubsystem::OnStartSessionComplete(FName SessionName, bool bWasSuccessful)
{
}

