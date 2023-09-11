// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/WidgetTree.h"
#include "Blueprint/UserWidget.h"
#include <Protobuf/Handler/FClientPacketHandler.h>
#include <Protobuf/Handler/FGamePacketHandler.h>
#include "W_MainGame.generated.h"

/**
 * 
 */
class UButton;
class UBorder;

UCLASS()
class PROJECT_LD_API UW_MainGame : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY()
	UWidget* mBottomUI;

	UPROPERTY()
	UWidget* mMainPlayerInfo;

public:
	UBorder* GetPlayerSightBorder() const { return PlayerSightBorder; }

public:
	UFUNCTION()
	void ChatOpen();

	UFUNCTION()
	void FocusChat();

	UFUNCTION()
	void FriendOpenRequest();

	void FriendOpenResponse(const google::protobuf::RepeatedPtrField<Protocol::SFriend>& inFriends, const int32& inListType);

	UFUNCTION()
	void PartyOpenRequest();

	UFUNCTION()
	void ClearPartyPlayerInfo();

	UFUNCTION()
	void PushPartyPlayerInfo(const int64& inRemoteID, const int64& inLeaderRemoteID, const int32& inLevel, const int32& inClass, const FString& inPlayerName, const bool& inIsSelf);

	UFUNCTION()
	void ReleasePartyPlayerInfo(const int64& inRemoteID);

	UFUNCTION()
	void FriendNotifyGame(const FString& inPlayerName, const bool& inConnect);

	UFUNCTION()
	void PartyNotifyGame(const FString& inPlayerName, const int32& inAction);

	UFUNCTION()
	void InventoryOpenRequest();

	UFUNCTION()
	void InventoryOpenResponse();

	UFUNCTION()
	void SkillTreeOpenRequest();

	UFUNCTION()
	void SkillTreeOpenResponse();

public:
	void Init();

protected:
	virtual void NativeConstruct() override;

private:
	bool misInventoryOpen;
	bool misSkillTreeOpen;
	bool misChatOpen;
	bool misFriendOpen;
	bool misPartyOpen;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	UBorder* PlayerSightBorder;

	UPROPERTY(meta = (BindWidget))
	UButton* Btn_Chat;

	UPROPERTY(meta = (BindWidget))
	UButton* Btn_Inventory;

	UPROPERTY(meta = (BindWidget))
	UButton* Btn_Friend;

	UPROPERTY(meta = (BindWidget))
	UButton* Btn_Party;

	UPROPERTY(meta = (BindWidget))
	UWidget* mNotifyFriend;

	UPROPERTY(meta = (BindWidget))
	UWidget* mNotifyParty;
	
	UPROPERTY(meta = (BindWidget))
	UWidget* mPartyPlayerInfoList;
};
