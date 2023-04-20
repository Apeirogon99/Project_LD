// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Common/W_ExitButton.h"
#include <Components/Button.h>
#include <Components/TextBlock.h>
#include <Network/NetworkGameMode.h>
#include <Widget/WidgetUtils.h>
#include <Widget/Handler/ClientHUD.h>

#include <Protobuf/Handler/FIdentityPacketHandler.h>

void UW_ExitButton::NativeConstruct()
{
	Super::NativeConstruct();

	mExitButton = Cast<UButton>(GetWidgetFromName(TEXT("mExitButton")));

	mExitText = Cast<UTextBlock>(GetWidgetFromName(TEXT("mExitText")));

	if (mExitButton != nullptr)
	{
		mExitButton->OnClicked.AddUniqueDynamic(this, &UW_ExitButton::Click_Exit);
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
	
	FConfirmButtonDelegate confirmDelegate;
	confirmDelegate.BindUFunction(this, FName("ExitGame"));

	FCancleButtonDelegate cancleDelegate;
	cancleDelegate.BindUFunction(this, FName("CancleExitGame"));

	bool error = UWidgetUtils::SetReconfirm(clientHUD, TEXT("생성 완료"), TEXT("정말 게임을 종료하시겠습니까?"), TEXT("게임 종료"), TEXT("취소"), confirmDelegate, cancleDelegate);
	if (error == false)
	{
		return;
	}
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

	clientHUD->CleanWidgetFromName(TEXT("Reconfirm"));
}
