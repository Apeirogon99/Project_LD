// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/WidgetUtils.h"
#include <Game/Main/W_MainGame.h>
#include <Game/Party/W_PartyPlayerInfoList.h>
#include <Game/Main/W_BottomUI.h>

bool UWidgetUtils::SetEditBox(AClientHUD* inHUD, const FString& inTitle, const FString& inHint, const FString& inButtonText, const FButtonDelegate& inDelegate)
{
    UW_EditBox* editBox = nullptr;
    UUserWidget* outWidget = inHUD->GetWidgetFromName(TEXT("EditBox"));
    if (outWidget == nullptr)
    {
        return false;
    }

    editBox = Cast<UW_EditBox>(outWidget);
    if (editBox == nullptr)
    {
        return false;
    }

    editBox->SetEditTitleText(inTitle);
    editBox->SetEditHint(inHint);
    editBox->SetConfrimButtonText(inButtonText);
    editBox->mConfirmDelegate = inDelegate;

    inHUD->ShowWidgetFromName(TEXT("EditBox"));
    return true;
}

bool UWidgetUtils::SetNotification(AClientHUD* inHUD, const FString& inTitle, const FString& inNotification, const FString& inButtonText, const FNotificationDelegate& inDelegate)
{
    UW_Notification* notification = nullptr;
    UUserWidget* outWidget = inHUD->GetWidgetFromName(TEXT("Notification"));
    if (outWidget == nullptr)
    {
        return false;
    }

    notification = Cast<UW_Notification>(outWidget);
    if (notification == nullptr)
    {
        return false;
    }

    notification->SetTitle(inTitle);
    notification->SetNotification(inNotification);
    notification->SetButtonText(inButtonText);
    notification->mNotificationDelegate = inDelegate;

    inHUD->ShowWidgetFromName(TEXT("Notification"));
    return true;
}

bool UWidgetUtils::SetReconfirm(AClientHUD* inHUD, const FString& inTitle, const FString& inText, const FString& inConfirm, const FString& inCancle, const FConfirmButtonDelegate& inConfirmDelegate, const FCancleButtonDelegate& inCancleDelegate)
{
    UW_Reconfirm* reconfirm = nullptr;
    UUserWidget* outWidget = inHUD->GetWidgetFromName(TEXT("Reconfirm"));
    if (outWidget == nullptr)
    {
        return false;
    }

    reconfirm = Cast<UW_Reconfirm>(outWidget);
    if (reconfirm == nullptr)
    {
        return false;
    }

    reconfirm->SetTitleText(inTitle);
    reconfirm->SetReconfirmText(inText);
    reconfirm->SetConfirmButtonText(inConfirm);
    reconfirm->SetCancleButtonText(inCancle);
    reconfirm->mReConfirmDelegate = inConfirmDelegate;
    reconfirm->mCancleDelegate = inCancleDelegate;

    inHUD->ShowWidgetFromName(TEXT("Reconfirm"));
    return true;
}

bool UWidgetUtils::SetChatWidget(AClientHUD* inHUD, const FString& inPlayerName, const FString& inMessage, const int32& inChatType)
{

    UW_Chat* chat = nullptr;
    UUserWidget* outWidget = inHUD->GetWidgetFromName(TEXT("Chat"));
    if (outWidget == nullptr)
    {
        return false;
    }

    chat = Cast<UW_Chat>(outWidget);
    if (chat == nullptr)
    {
        return false;

    }
    chat->AddMessage(inPlayerName, inMessage, StaticCast<EChat>(inChatType));

    //inHUD->ShowWidgetFromName(TEXT("BW_Chatting"));
    return true;
}

bool UWidgetUtils::SetLoadingPlayer(AClientHUD* inHUD, const int32& inMax, const int32& inLeast)
{
    UW_LoadingPlayer* loadingPlayer = nullptr;
    UUserWidget* outWidget = inHUD->GetWidgetFromName(TEXT("LoadingPlayer"));
    if (outWidget == nullptr)
    {
        return false;
    }

    loadingPlayer = Cast<UW_LoadingPlayer>(outWidget);
    if (loadingPlayer == nullptr)
    {
        return false;
    }
    loadingPlayer->UpdateLoadingPlayer(FString::FromInt(inMax), FString::FromInt(inLeast));

    inHUD->ShowWidgetFromName(TEXT("LoadingPlayer"));
    return true;
}

bool UWidgetUtils::SetWaiting(AClientHUD* inHUD, const FString& inTitle, const int64& inTime)
{
    UW_Waiting* waiting = nullptr;
    UUserWidget* outWidget = inHUD->GetWidgetFromName(TEXT("Waiting"));
    if (outWidget == nullptr)
    {
        return false;
    }

    waiting = Cast<UW_Waiting>(outWidget);
    if (waiting == nullptr)
    {
        return false;
    }
    waiting->SetTitle(inTitle);
    waiting->SetTime(StaticCast<int32>(inTime));

    inHUD->ShowWidgetFromName(TEXT("Waiting"));
    return true;
}

bool UWidgetUtils::SetSkipSequence(AClientHUD* inHUD, const int32& inMax, const int32& inLeast)
{
    UW_SkipSequence* skipSequence = nullptr;
    UUserWidget* outWidget = inHUD->GetWidgetFromName(TEXT("SkipSequence"));
    if (outWidget == nullptr)
    {
        return false;
    }

    skipSequence = Cast<UW_SkipSequence>(outWidget);
    if (skipSequence == nullptr)
    {
        return false;
    }
    skipSequence->UpdateSkipSequence(FString::FromInt(inMax), FString::FromInt(inLeast));

    inHUD->ShowWidgetFromName(TEXT("SkipSequence"));
    return true;
}

bool UWidgetUtils::SetResponseUseKeyAction(AClientHUD* inHUD, const int32& inKey, const FString& inError)
{
    UW_ResponseUseKeyAction* responseUseKeyAction = nullptr;
    UUserWidget* outWidget = inHUD->GetWidgetFromName(TEXT("ResponseUseKeyAction"));
    if (outWidget == nullptr)
    {
        return false;
    }

    responseUseKeyAction = Cast<UW_ResponseUseKeyAction>(outWidget);
    if (responseUseKeyAction == nullptr)
    {
        return false;
    }
    //responseUseKeyAction->SetResponseUseKeyAction(inKey, inError);
    responseUseKeyAction->OnActiveAnimation();

    inHUD->ShowWidgetFromName(TEXT("ResponseUseKeyAction"));
    return true;
}

bool UWidgetUtils::SetSkillCoolTime(AClientHUD* inHUD, const TArray<int32>& inSkillID, const TArray<int64>& inSkillDuration)
{
    UW_MainGame* mainwidget = Cast<UW_MainGame>(inHUD->GetWidgetFromName(TEXT("MainGame")));
    if (nullptr == mainwidget)
    {
        return false;
    }

    UW_BottomUI* bottomUI = Cast<UW_BottomUI>(mainwidget->mBottomUI);
    if (nullptr == bottomUI)
    {
        return false;
    }

    bottomUI->SetWidgetCoolTime(inSkillID, inSkillDuration);

    return true;
}

bool UWidgetUtils::SetPushBuff(AClientHUD* inHUD, const int64& inRemoteID, const int32& inBuffID, const int64& inBuffDuration)
{
    UW_MainGame* widget = Cast<UW_MainGame>(inHUD->GetWidgetFromName(TEXT("MainGame")));
    if (nullptr == widget)
    {
        return false;
    }

    UW_PartyPlayerInfoList* partyPlayerInfoList = Cast<UW_PartyPlayerInfoList>(widget->GetPartyPlayerInfoList());
    if (nullptr == partyPlayerInfoList)
    {
        return false;
    }

    partyPlayerInfoList->RequestPushBuff(inRemoteID, inBuffID, inBuffDuration);

    return true;
}

bool UWidgetUtils::SetReleaseBuff(AClientHUD* inHUD, const int64& inRemoteID, const int32& inBuffID)
{
    UW_MainGame* widget = Cast<UW_MainGame>(inHUD->GetWidgetFromName(TEXT("MainGame")));
    if (nullptr == widget)
    {
        return false;
    }

    UW_PartyPlayerInfoList* partyPlayerInfoList = Cast<UW_PartyPlayerInfoList>(widget->GetPartyPlayerInfoList());
    if (nullptr == partyPlayerInfoList)
    {
        return false;
    }

    partyPlayerInfoList->RequestReleaseBuff(inRemoteID, inBuffID);

    return true;
}
