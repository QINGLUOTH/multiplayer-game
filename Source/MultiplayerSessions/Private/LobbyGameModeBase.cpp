// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameModeBase.h"

// �ɹ���¼����á����ǵ�һ�����԰�ȫ����PlayerController�ϵ��ø��ƺ����ĵط���(�û�join session success��ִ��)
void ALobbyGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	// NewPlayer����session�ɹ�����û�
	Super::PostLogin(NewPlayer);

	if (GameState)
	{
		//�������
		int32 NumberOfPlayers = GameState.Get()->PlayerArray.Num();
		if (GEngine) {
			// 1ֻ����һ����Ϣ, ������µ���Ϣ, �滻ԭ�ȵ���Ϣ
			GEngine->AddOnScreenDebugMessage(1, 600.f, FColor::Yellow, FString::Printf(TEXT("Players Number %d"), NumberOfPlayers));
			APlayerState* playerState = NewPlayer->GetPlayerState<APlayerState>();
			if (playerState) {
				// 2ֻ���������Ϣ, ������µ���Ϣ, �滻ԭ�ȵ���Ϣ
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

// ������PlayerState�Ŀ������뿪��Ϸ������ʱ����(�û��˳���Ϸ��ִ��)
void ALobbyGameModeBase::Logout(AController* Exiting)
{
	// Exiting�˳��Ŀ�����
	Super::Logout(Exiting);

	if (GameState)
	{
		//�������
		int32 NumberOfPlayers = GameState.Get()->PlayerArray.Num();
		if (GEngine) {
			// 1ֻ����һ����Ϣ, ������µ���Ϣ, �滻ԭ�ȵ���Ϣ
			GEngine->AddOnScreenDebugMessage(1, 600.f, FColor::Yellow, FString::Printf(TEXT("Players Number %d"), NumberOfPlayers));
			APlayerState* playerState = Exiting->GetPlayerState<APlayerState>();
			if (playerState) {
				// 2ֻ���������Ϣ, ������µ���Ϣ, �滻ԭ�ȵ���Ϣ
				GEngine->AddOnScreenDebugMessage(2, 60.f, FColor::Yellow, FString::Printf(TEXT("Players Name %s"), *playerState->GetName()));
			}
		}
	}
}

