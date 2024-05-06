// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameModeBase.h"

// 成功登录后调用。这是第一个可以安全地在PlayerController上调用复制函数的地方。(用户join session success后执行)
void ALobbyGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	// NewPlayer加入session成功后的用户
	Super::PostLogin(NewPlayer);

	if (GameState)
	{
		//玩家数量
		int32 NumberOfPlayers = GameState.Get()->PlayerArray.Num();
		if (GEngine) {
			// 1只允许一个消息, 如果有新的消息, 替换原先的消息
			GEngine->AddOnScreenDebugMessage(1, 600.f, FColor::Yellow, FString::Printf(TEXT("Players Number %d"), NumberOfPlayers));
			APlayerState* playerState = NewPlayer->GetPlayerState<APlayerState>();
			if (playerState) {
				// 2只允许二个消息, 如果有新的消息, 替换原先的消息
				GEngine->AddOnScreenDebugMessage(2, 60.f, FColor::Yellow, FString::Printf(TEXT("Players Name %s"), *playerState->GetName()));
			}
			if (NumberOfPlayers == 2) {
				UWorld* world = GetWorld();
				if (world) {
					GEngine->AddOnScreenDebugMessage(2, 60.f, FColor::Yellow, TEXT("GetWorld"));
					world->ServerTravel("/Game/MyProject/Maps/LobbyGame?listen");
				}
			}
		}
	}
}

// 当带有PlayerState的控制器离开游戏或被销毁时调用(用户退出游戏后执行)
void ALobbyGameModeBase::Logout(AController* Exiting)
{
	// Exiting退出的控制器
	Super::Logout(Exiting);

	if (GameState)
	{
		//玩家数量
		int32 NumberOfPlayers = GameState.Get()->PlayerArray.Num();
		if (GEngine) {
			// 1只允许一个消息, 如果有新的消息, 替换原先的消息
			GEngine->AddOnScreenDebugMessage(1, 600.f, FColor::Yellow, FString::Printf(TEXT("Players Number %d"), NumberOfPlayers));
			APlayerState* playerState = Exiting->GetPlayerState<APlayerState>();
			if (playerState) {
				// 2只允许二个消息, 如果有新的消息, 替换原先的消息
				GEngine->AddOnScreenDebugMessage(2, 60.f, FColor::Yellow, FString::Printf(TEXT("Players Name %s"), *playerState->GetName()));
			}
		}
	}
}

