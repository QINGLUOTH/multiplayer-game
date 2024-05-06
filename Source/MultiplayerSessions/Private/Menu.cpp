// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu.h"

void UMenu::MenuSetup(int32 NumOfPublicConnections, FString TypeOfMatch, FString PathOfLobby)
{
	// 初始化Menu
	this->PathLobby = FString::Printf(TEXT("%s?listen"), *PathOfLobby);
	this->NumPublicConnections = NumOfPublicConnections;
	this->MatchType = TypeOfMatch;
	// 将该Menu添加到屏幕上
	this->AddToViewport();
	// 设置可视
	this->SetVisibility(ESlateVisibility::Visible);
	// bIsFocusable = true表示允许点击时是否受到焦点, 可以在蓝图中设置
	this->bIsFocusable = true;
	UWorld* world = GetWorld();
	if (world) {
		APlayerController* playerController = world->GetFirstPlayerController();  // 获得第一个玩家控制器
		//world->GetFirstLocalPlayerFromController();  // 从控制器获取第一个本地玩家
		if (playerController) {
			//FInputModeUIOnly 用于设置只允许ui响应用户输入的输入模式的数据结构
			FInputModeUIOnly inputModeUIOnly;
			// SetWidgetToFocus设置焦距
			// TakeWidget()获取底层的slate部件，不存在则构造它
			inputModeUIOnly.SetWidgetToFocus(TakeWidget());
			//设置鼠标在视口的行为，这里是不锁定
			inputModeUIOnly.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			//设置inputModeUIOnly
			playerController->SetInputMode(inputModeUIOnly);
			//显示鼠标
			playerController->SetShowMouseCursor(true);
		}
	}

	UGameInstance* gameInstance = GetGameInstance();
	if (gameInstance) {
		MyGameInstanceSubsystem = gameInstance->GetSubsystem<UMyGameInstanceSubsystem>();
		MyGameInstanceSubsystem->multiplayerOnCreateSessionCompleteDelegate.AddDynamic(this, &ThisClass::OnCreateSession);
		MyGameInstanceSubsystem->MultiplayerOnStartSessionCompleteDelegate.AddDynamic(this, &ThisClass::OnStartSession);
		MyGameInstanceSubsystem->MultiplayerOnDestroySessionCompleteDelegate.AddDynamic(this, &ThisClass::OnDestroySession);
		MyGameInstanceSubsystem->OnFindSessionCompleteDelegate.AddUObject(this, &ThisClass::OnFindSession);
		MyGameInstanceSubsystem->OnJoinSessionCompleteDelegate.AddUObject(this, &ThisClass::OnJoinSession);
	}
}

bool UMenu::Initialize()
{
	if (!Super::Initialize()) {
		return false;
	}

	// 函数绑定事件
	if (this->HostButton) {
		this->HostButton->OnClicked.AddDynamic(this, &ThisClass::HostButtonClicked);
	}

	if (this->JoinButton) {
		this->JoinButton->OnClicked.AddDynamic(this, &ThisClass::JoinButtonClicked);
	}


	return true;
}

void UMenu::NativeDestruct()
{
	MenuTearDown();
	Super::NativeDestruct();
}

void UMenu::OnStartSession(bool bWasSuccessful)
{
}

void UMenu::OnCreateSession(bool bWasSuccessful)
{
	if (bWasSuccessful) {
		GEngine->AddOnScreenDebugMessage(
			-1,
			5.f,
			FColor::Red,
			TEXT("OnCreateSession")
		);

		UWorld* world = GetWorld();
		if (world) {
			world->ServerTravel(PathLobby);
		}
	}
	else {
		this->HostButton->SetIsEnabled(true);
	}
}

void UMenu::OnFindSession(const TArray<FOnlineSessionSearchResult>& SessionResult, bool bWasSuccessful)
{
	if (bWasSuccessful) {
		for (auto Result : SessionResult) {
			FString Id = Result.GetSessionIdStr();
			FString UserName = Result.Session.OwningUserName;
			FString MyMatchType;
			Result.Session.SessionSettings.Get(FName("MatchType"), MyMatchType);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Session id %s, Session User Name %s"), *Id, *UserName));

			if (MyMatchType == this->MatchType) {
				// 表示找到session, join
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Session MatchType %s"), *MyMatchType));

				MyGameInstanceSubsystem->JoinSession(Result);
				return;
			}
		}
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("print session over")));
	}

	if (!bWasSuccessful || SessionResult.Num() == 0) {
		this->JoinButton->SetIsEnabled(true);
	}
}

void UMenu::OnJoinSession(EOnJoinSessionCompleteResult::Type Result)
{
	if (EOnJoinSessionCompleteResult::UnknownError == Result) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Join error"));
		return;
	}

	IOnlineSubsystem* subsystem = IOnlineSubsystem::Get();
	if (!subsystem) {
		return;
	}

	IOnlineSessionPtr SessionInterface = subsystem->GetSessionInterface();

	if (SessionInterface.IsValid()) {
		FString Address;
		APlayerController* aplayerController = GetGameInstance()->GetFirstLocalPlayerController();
		SessionInterface->GetResolvedConnectString(NAME_GameSession, Address);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, FString::Printf(TEXT("Connection string %s"), *Address));
		if (aplayerController) {
			aplayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
		}
	}

	if (Result != EOnJoinSessionCompleteResult::Success) {
		this->JoinButton->SetIsEnabled(true);
	}
}

void UMenu::OnDestroySession(bool bWasSuccessful)
{
}

void UMenu::HostButtonClicked()
{
	GEngine->AddOnScreenDebugMessage(
		-1,
		5.f,
		FColor::Red,
		TEXT("HostButtonClicked")
	);

	if (MyGameInstanceSubsystem) {
		MyGameInstanceSubsystem->CreateSession(NumPublicConnections, MatchType);
	}

	this->HostButton->SetIsEnabled(false);
}

void UMenu::JoinButtonClicked()
{
	GEngine->AddOnScreenDebugMessage(
		-1,
		5.f,
		FColor::Red,
		TEXT("JoinButtonClicked")
	);
	if (MyGameInstanceSubsystem) {
		MyGameInstanceSubsystem->FindSessions(10000);
	}
	this->HostButton->SetIsEnabled(false);
}

void UMenu::MenuTearDown()
{
	// 将组件删除, 开始游戏
	// 删除当前的所有组件
	this->RemoveFromParent();
	UWorld* world = GetWorld();
	if (world) {
		APlayerController* playerController = world->GetFirstPlayerController();
		if (playerController) {
			FInputModeGameOnly inputModeGameOnly;
			playerController->SetInputMode(inputModeGameOnly);
			// 不显示鼠标
			playerController->SetShowMouseCursor(false);
		}
	}
}

