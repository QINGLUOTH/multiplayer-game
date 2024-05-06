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
	// 初始化
	UFUNCTION(BlueprintCallable, Category = "Initialize Setup")
	void MenuSetup(int32 NumOfPublicConnections = 4, FString TypeOfMatch = TEXT("FreeForAll"), FString PathOfLobby = TEXT("/Game/NewMap1"));
protected:
	virtual bool Initialize() override;  // virtual表示在父引用指向子类型的对象在调用函数时, 使用子类型的函数
	UMyGameInstanceSubsystem* MyGameInstanceSubsystem;
	// 在ue5.1后, OnLevelRemovedFromWorld函数被NativeDestruct替代了
	//virtual void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld) override;
	virtual void NativeDestruct() override;

	// 在Session创建成功后调用
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

