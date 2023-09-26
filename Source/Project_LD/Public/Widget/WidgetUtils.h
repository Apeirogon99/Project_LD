// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <Widget/Handler/ClientHUD.h>
#include <Widget/Common/W_Notification.h>
#include <Widget/Common/W_BackButton.h>
#include <Widget/Common/W_EditBox.h>
#include <Widget/Common/W_Reconfirm.h>
#include <Widget/Game/Chat/W_Chat.h>
#include <Widget/Common/W_LoadingPlayer.h>
#include <Widget/Common/W_Waiting.h>
#include <Widget/Common/W_SkipSequence.h>
#include <Widget/Common/W_ResponseUseKeyAction.h>
#include "WidgetUtils.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_LD_API UWidgetUtils : public UObject
{
	GENERATED_BODY()
	
public:
	static bool SetEditBox(AClientHUD* inHUD, const FString& inTitle, const FString& inHint, const FString& inButtonText, const FButtonDelegate& inDelegate);
	static bool SetNotification(AClientHUD* inHUD, const FString& inTitle, const FString& inNotification, const FString& inButtonText, const FNotificationDelegate& inDelegate);
	static bool SetReconfirm(AClientHUD* inHUD, const FString& inTitle, const FString& inText, const FString& inConfirm, const FString& inCancle, const FConfirmButtonDelegate& inConfirmDelegate, const FCancleButtonDelegate& inCancleDelegate);
	static bool SetChatWidget(AClientHUD* inHUD, const FString& inPlayerName, const FString& inMessage, const int32& inChatType);
	static bool SetLoadingPlayer(AClientHUD* inHUD, const int32& inMax, const int32& inLeast);
	static bool SetWaiting(AClientHUD* inHUD, const FString& inTitle, const int64& inTime);
	static bool SetSkipSequence(AClientHUD* inHUD, const int32& inMax, const int32& inLeast);
	static bool SetResponseUseKeyAction(AClientHUD* inHUD, const int32& inKey, const FString& inError);
	static bool SetSkillCoolTime(AClientHUD* inHUD, const TArray<int32>& inSkillID, const TArray<int64>& inSkillDuration);
	static bool SetPushBuff(AClientHUD* inHUD, const int32& inBuffID, const int64& inBuffDuration);
	static bool SetReleaseBuff(AClientHUD* inHUD, const int32& inBuffID);
};