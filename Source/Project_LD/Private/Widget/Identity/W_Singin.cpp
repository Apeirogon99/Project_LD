// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Identity/W_Singin.h"
#include <Components/EditableTextBox.h>
#include <Components/Button.h>
#include <Components/CheckBox.h>
#include <Network/NetworkUtils.h>
#include <Network/NetworkController.h>
#include <Protobuf/Handler/FIdentityPacketHandler.h>
#include <Widget/Handler/ClientHUD.h>
#include <Widget/Common/W_Notification.h>

void UW_Singin::NativeConstruct()
{
	Super::NativeConstruct();

	mEditId			= Cast<UEditableTextBox>(GetWidgetFromName(TEXT("mEditId")));
	mEditPassword	= Cast<UEditableTextBox>(GetWidgetFromName(TEXT("mEditPassword")));

	mSinginButton	= Cast<UButton>(GetWidgetFromName(TEXT("mSinginButton")));
	mSingupButton	= Cast<UButton>(GetWidgetFromName(TEXT("mSingupButton")));

	mAutoSingin		= Cast<UCheckBox>(GetWidgetFromName(TEXT("mAutoSingin")));

	if (mEditId != nullptr)
	{
		mEditId->OnTextChanged.AddUniqueDynamic(this, &UW_Singin::Committed_ID);
	}

	if (mEditPassword != nullptr)
	{
		mEditPassword->SetIsPassword(true);
		mEditPassword->OnTextChanged.AddUniqueDynamic(this, &UW_Singin::Committed_Password);
	}

	if (mSinginButton != nullptr)
	{
		mSinginButton->SetIsEnabled(false);
		mSinginButton->SetBackgroundColor(mButtonDeactivationColor);
		mSinginButton->OnClicked.AddUniqueDynamic(this, &UW_Singin::Click_Singin);
	}

	if (mSingupButton != nullptr)
	{
		mSingupButton->SetBackgroundColor(mButtonActiveColor);
		mSingupButton->OnClicked.AddUniqueDynamic(this, &UW_Singin::Click_Singup);
	}

	if (mAutoSingin != nullptr)
	{
		mAutoSingin->OnCheckStateChanged.AddUniqueDynamic(this, &UW_Singin::Check_AutoSingin);
	}
}

void UW_Singin::Click_Singin()
{
	if (true == mID.IsEmpty())				return;
	if (true == mPassword.IsEmpty())		return;

	APlayerController* owningController = GetOwningPlayer();
	ANetworkController* networkController = Cast<ANetworkController>(owningController);

	AClientHUD* clientHUD = Cast<AClientHUD>(owningController->GetHUD());
	clientHUD->AllCollapsedButOneWidget(TEXT("LoadingServer"));

	std::string id = UNetworkUtils::ConvertString(mID);
	std::string password = UNetworkUtils::ConvertString(mPassword);

	Protocol::C2S_Singin singinPacket;
	singinPacket.set_user_id(id);
	singinPacket.set_user_password(password);

	SendBufferPtr sendBuffer = FIdentityPacketHandler::MakeSendBuffer(networkController, singinPacket);

	networkController->Send(sendBuffer);
}

void UW_Singin::Click_Singup()
{
	APlayerController* owningController = GetOwningPlayer();

	AClientHUD* HUD = Cast<AClientHUD>(owningController->GetHUD());

	HUD->SelfHitTestInvisibleWidgetFromName("Singup");

	HUD->CollapsedWidgetFromName("Singin");
}

void UW_Singin::Committed_ID(const FText& inId)
{
	mID = inId.ToString();
	EnableSinginButton();
}

void UW_Singin::Committed_Password(const FText& inPassword)
{
	mPassword = inPassword.ToString();
	EnableSinginButton();
}

void UW_Singin::Check_AutoSingin(bool bIsChecked)
{
	mIsAutoSingin = bIsChecked;
}

void UW_Singin::EnableSinginButton()
{
	if (false == mID.IsEmpty() && false == mPassword.IsEmpty())
	{
		mSinginButton->SetBackgroundColor(mButtonActiveColor);
		mSinginButton->SetIsEnabled(true);
	}
	else
	{
		mSinginButton->SetBackgroundColor(mButtonDeactivationColor);
		mSinginButton->SetIsEnabled(false);
	}
}