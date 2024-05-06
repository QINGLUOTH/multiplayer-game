// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "MyGameInstanceSubsystem.h"
#include "Menu.generated.h"

/**
 *
 */
UCLASS()
class MULTIPLAYERSESSIONS_API UMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	// ��ʼ��
	UFUNCTION(BlueprintCallable, Category = "Initialize Setup")
	void MenuSetup(int32 NumOfPublicConnections = 4, FString TypeOfMatch = TEXT("FreeForAll"), FString PathOfLobby = TEXT("/Game/NewMap1"));
protected:
	virtual bool Initialize() override;  // virtual��ʾ�ڸ�����ָ�������͵Ķ����ڵ��ú���ʱ, ʹ�������͵ĺ���
	UMyGameInstanceSubsystem* MyGameInstanceSubsystem;
	// ��ue5.1��, OnLevelRemovedFromWorld������NativeDestruct�����
	//virtual void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld) override;
	virtual void NativeDestruct() override;

	// ��Session�����ɹ������
	UFUNCTION()
	void OnStartSession(bool bWasSuccessful);
	UFUNCTION()
	void OnCreateSession(bool bWasSuccessful);

	void OnFindSession(const TArray<FOnlineSessionSearchResult>& SessionResult, bool bWasSuccessful);
	void OnJoinSession(EOnJoinSessionCompleteResult::Type Result);

	UFUNCTION()
	void OnDestroySession(bool bWasSuccessful);

private:
	UPROPERTY()
	UButton* HostButton;
	UPROPERTY()
	UButton* JoinButton;
	UFUNCTION()
	void HostButtonClicked();
	UFUNCTION()
	void JoinButtonClicked();

	void MenuTearDown();
	int32 NumPublicConnections;
	FString MatchType;
	FString PathLobby;
};

