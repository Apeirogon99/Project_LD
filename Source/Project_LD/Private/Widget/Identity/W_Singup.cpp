// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Identity/W_Singup.h"
#include <Components/EditableTextBox.h>
#include <Components/Button.h>
#include <Network/NetworkUtils.h>
#include <Network/NetworkController.h>
#include <Protobuf/Handler/FIdentityPacketHandler.h>
#include <Widget/Handler/ClientHUD.h>

void UW_Singup::NativeConstruct()
{
	Super::NativeConstruct();

	mEditId				= Cast<UEditableTextBox>(GetWidgetFromName(TEXT("mEditId")));
	mEditEmail			= Cast<UEditableTextBox>(GetWidgetFromName(TEXT("mEditEmail")));
	mEditPassword		= Cast<UEditableTextBox>(GetWidgetFromName(TEXT("mEditPassword")));

	mSingupButton		= Cast<UButton>(GetWidgetFromName(TEXT("mSingupButton")));
	mExitButton			= Cast<UButton>(GetWidgetFromName(TEXT("mExitButton")));

	if (mEditId != nullptr)
	{
		mEditId->OnTextChanged.AddUniqueDynamic(this, &UW_Singup::Committed_ID);
	}

	if (mEditEmail != nullptr)
	{
		mEditEmail->OnTextChanged.AddUniqueDynamic(this, &UW_Singup::Committed_Email);
	}

	if (mEditPassword != nullptr)
	{
		mEditPassword->SetIsPassword(true);
		mEditPassword->OnTextChanged.AddUniqueDynamic(this, &UW_Singup::Committed_Password);
	}

	if (mSingupButton != nullptr)
	{
		mSingupButton->SetIsEnabled(false);
		mSingupButton->SetBackgroundColor(mButtonDeactivationColor);
		mSingupButton->OnClicked.AddUniqueDynamic(this, &UW_Singup::Click_Singup);
	}

	if (mExitButton != nullptr)
	{
		mExitButton->SetBackgroundColor(mButtonActiveColor);
		mExitButton->OnClicked.AddUniqueDynamic(this, &UW_Singup::Click_Exit);
	}
}

void UW_Singup::Click_Singup()
{
	if (true == mID.IsEmpty())				return;
	if (true == mEmail.IsEmpty())			return;
	if (true == mPassword.IsEmpty())		return;

	APlayerController* owningController = GetOwningPlayer();
	ANetworkController* networkController = Cast<ANetworkController>(owningController);

	AClientHUD* clientHUD = Cast<AClientHUD>(owningController->GetHUD());
	clientHUD->AllCollapsedButOneWidget(TEXT("LoadingServer"));

	std::string id = UNetworkUtils::ConvertString(mID);
	std::string email = UNetworkUtils::ConvertString(mEmail);
	std::string password = UNetworkUtils::ConvertString(mPassword);

	Protocol::C2S_Singup singupPacket;
	singupPacket.set_id(id);
	singupPacket.set_email(email);
	singupPacket.set_password(password);

	SendBufferPtr sendBuffer = FIdentityPacketHandler::MakeSendBuffer(networkController, singupPacket);

	networkController->Send(sendBuffer);
	
}

void UW_Singup::Click_Exit()
{
	APlayerController* owningController = GetOwningPlayer();

	AClientHUD* HUD = Cast<AClientHUD>(owningController->GetHUD());

	HUD->ShowWidgetFromName("Singin");

	HUD->CleanWidgetFromName("Singup");
}

void UW_Singup::Committed_ID(const FText& inId)
{
	mID = inId.ToString();
	EnableSingupButton();
}

void UW_Singup::Committed_Email(const FText& inEmail)
{
	FString emailTemp = inEmail.ToString();
	int32 find = emailTemp.Find("@");
	if (find == INDEX_NONE)
	{
		mEmail = "";
		mEmailDomain = "";
	}
	else
	{
		mEmail = inEmail.ToString();
		//mEmail = emailTemp.Mid(0, find);
		//mEmailDomain = emailTemp.Mid(find + 1, emailTemp.Len());
	}

	EnableSingupButton();
}

void UW_Singup::Committed_Password(const FText& inPassword)
{
	mPassword = inPassword.ToString();
	EnableSingupButton();
}

void UW_Singup::EnableSingupButton()
{
	if (false == mID.IsEmpty() && false == mPassword.IsEmpty() && false == mEmail.IsEmpty())
	{
		mSingupButton->SetBackgroundColor(mButtonActiveColor);
		mSingupButton->SetIsEnabled(true);
	}
	else
	{
		mSingupButton->SetBackgroundColor(mButtonDeactivationColor);
		mSingupButton->SetIsEnabled(false);
	}
}
