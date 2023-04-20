// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/WidgetUtils.h"

bool UWidgetUtils::SetEditBox(AClientHUD* inHUD, const FString& inTitle, const FString& inHint, const FString& inButtonText, const FButtonDelegate& inDelegate)
{
    UUserWidget* outWidget = nullptr;
    UW_EditBox* editBox = nullptr;
    int32 number = 0;
    
    bool ret = inHUD->GetWidgetFromName(TEXT("EditBox"), outWidget, number);
    if (ret == false)
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
    UUserWidget* outWidget = nullptr;
    UW_Notification* notification = nullptr;
    int32 number = 0;

    bool ret = inHUD->GetWidgetFromName(TEXT("Notification"), outWidget, number);
    if (ret == false)
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
    UUserWidget* outWidget = nullptr;
    UW_Reconfirm* reconfirm = nullptr;
    int32 number = 0;

    bool ret = inHUD->GetWidgetFromName(TEXT("Reconfirm"), outWidget, number);
    if (ret == false)
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
