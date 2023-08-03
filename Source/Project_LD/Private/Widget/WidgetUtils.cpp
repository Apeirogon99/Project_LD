// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/WidgetUtils.h"

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
