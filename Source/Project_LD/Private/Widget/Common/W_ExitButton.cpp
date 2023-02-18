// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Common/W_ExitButton.h"
#include <Components/Button.h>
#include <Components/TextBlock.h>
#include <Network/NetworkGameMode.h>
#include <Widget/Common/W_Reconfirm.h>
#include <Widget/Handler/ClientHUD.h>

#include <Protobuf/Handler/FIdentityPacketHandler.h>

void UW_ExitButton::NativeConstruct()
{
	Super::NativeConstruct();

	mExitButton = Cast<UButton>(GetWidgetFromName(TEXT("mExitButton")));

	mExitText = Cast<UTextBlock>(GetWidgetFromName(TEXT("mExitText")));

	if (mExitButton != nullptr)
	{
		mExitButton->OnClicked.AddDynamic(this, &UW_ExitButton::Click_Exit);
	}	
}

void UW_ExitButton::SetExitText(const FString& inText)
{
	FText text = FText::FromString(inText);
	mExitText->SetText(text);
}

void UW_ExitButton::Click_Exit()
{
	APlayerController* playerControll = GetOwningPlayer();
	AClientHUD* clientHUD = Cast<AClientHUD>(playerControll->GetHUD());
	
	UW_Reconfirm* reconfirm = Cast<UW_Reconfirm>(clientHUD->GetWidgetFromName(TEXT("Reconfirm")));
	reconfirm->SetTitleText(TEXT("게임 종료"));
	reconfirm->SetReconfirmText(TEXT("정말 게임을 종료하시겠습니까?"));
	reconfirm->SetConfirmButtonText(TEXT("게임 종료"));
	reconfirm->SetCancleButtonText(TEXT("취소"));
	reconfirm->mReConfirmDelegate.BindUFunction(this, FName("ExitGame"));
	reconfirm->mCancleDelegate.BindUFunction(this, FName("CancleExitGame"));
	clientHUD->AllCollapsedButOneWidget(TEXT("Reconfirm"));
}

void UW_ExitButton::ExitGame()
{
	//LeaveServer
	//Protocol::C2S_LeaveServer levalPacket;
}

void UW_ExitButton::CancleExitGame()
{
	APlayerController* playerControll = GetOwningPlayer();
	AClientHUD* clientHUD = Cast<AClientHUD>(playerControll->GetHUD());

	clientHUD->AllSelfHitTestInvisibleButOneWidget(TEXT("Reconfirm"));
}
