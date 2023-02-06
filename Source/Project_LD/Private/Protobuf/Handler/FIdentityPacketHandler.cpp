// Fill out your copyright notice in the Description page of Project Settings.


#include "Protobuf/Handler/FIdentityPacketHandler.h"
#include <Framework/Gameinstance/LDGameInstance.h>
#include <Network/NetworkCharacter.h>
#include <Network/NetworkGameMode.h>
#include <Network/NetworkGameState.h>
#include <Network/NetworkPawn.h>
#include <Network/NetworkPlayerState.h>
#include <Network/NetworkService.h>
#include <Network/NetworkUtils.h>
#include <Network/NetworkSession.h>

#include <Widget/Handler/ClientHUD.h>
#include <Widget/Common/W_Notification.h>
#include <Widget/Common/W_EditBox.h>

bool Handle_S2C_EnterServer(ANetworkController* controller, Protocol::S2C_EnterServer& pkt)
{
	AGameModeBase* gameMode = controller->GetWorld()->GetAuthGameMode();
	ANetworkGameMode* networkGameMode = Cast<ANetworkGameMode>(gameMode);
	if (nullptr == networkGameMode)
	{
		return false;
	}

	UNetworkUtils::NetworkConsoleLog("Handle_S2C_EnterServer", ELogLevel::Warning);

	return true;
}

bool Handle_S2C_LeaveServer(ANetworkController* controller, Protocol::S2C_LeaveServer& pkt)
{
	return false;
}

bool Handle_S2C_Singin(ANetworkController* controller, Protocol::S2C_Singin& pkt)
{
	ULDGameInstance* gameInstance = Cast<ULDGameInstance>(controller->GetGameInstance());
	if (nullptr == gameInstance)
	{
		return false;
	}

	AClientHUD* clientHUD = Cast<AClientHUD>(controller->GetHUD());
	if (nullptr == clientHUD)
	{
		return false;
	}

	clientHUD->CleanWidgetFromName(TEXT("LoadingServer"));

	int32 error = pkt.error();
	if (error != 0)
	{
		UW_Notification* notification = Cast<UW_Notification>(clientHUD->GetWidgetFromName(TEXT("Notification")));
		notification->SetTitle(TEXT("로그인 실패"));
		notification->SetNotification(TEXT("아이디 혹은 패스워드가 틀렸습니다"));
		notification->SetButtonText(TEXT("확인"));

		notification->mNotificationDelegate.BindLambda([=]()
			{
				clientHUD->AllSelfHitTestInvisibleButOneWidget(TEXT("Notification"));
			});

		clientHUD->ShowWidgetFromName(TEXT("Notification"));
	}
	else
	{
		FString ticket = UNetworkUtils::ConvertFString(pkt.id_token());
		gameInstance->mTicket = ticket;

		clientHUD->ShowWidgetFromName(TEXT("SelectServer"));
		clientHUD->AllSelfHitTestInvisibleButOneWidget(TEXT("Singin"));
	}

	return true;
}

bool Handle_S2C_Singup(ANetworkController* controller, Protocol::S2C_Singup& pkt)
{
	ULDGameInstance* gameInstance = Cast<ULDGameInstance>(controller->GetGameInstance());
	if (nullptr == gameInstance)
	{
		return false;
	}

	AClientHUD* clientHUD = Cast<AClientHUD>(controller->GetHUD());
	if (nullptr == clientHUD)
	{
		return false;
	}

	clientHUD->CleanWidgetFromName(TEXT("LoadingServer"));

	int32 error = pkt.error();
	if (error != 0)
	{
		UW_Notification* notification = Cast<UW_Notification>(clientHUD->GetWidgetFromName(TEXT("Notification")));
		notification->SetTitle(TEXT("회원가입 실패"));
		notification->SetNotification(TEXT("이미 아이디 또는 이메일이 존재합니다"));
		notification->SetButtonText(TEXT("확인"));

		notification->mNotificationDelegate.BindLambda([=]()
			{
				clientHUD->AllSelfHitTestInvisibleButOneWidget(TEXT("Notification"));
			});

		clientHUD->ShowWidgetFromName(TEXT("Notification"));
	}
	else
	{
		UW_EditBox* editBox = Cast<UW_EditBox>(clientHUD->GetWidgetFromName(TEXT("EditBox")));
		editBox->SetEditTitleText(TEXT("이메일 인증"));
		editBox->SetEditHint(TEXT("이메일 인증번호"));
		editBox->SetConfrimButtonText(TEXT("인증하기"));

		editBox->mConfirmDelegate.BindLambda([=](const FString& inCertifiedEmail)
			{
				clientHUD->AllCollapsedButOneWidget(TEXT("LoadingServer"));

				Protocol::C2S_EmailVerified emailVerifiedPacket;
				std::string verfiedStr = UNetworkUtils::ConvertString(inCertifiedEmail);
				emailVerifiedPacket.set_verified(verfiedStr);
				SendBufferPtr pakcetBuffer = FIdentityPacketHandler::MakeSendBuffer(controller, emailVerifiedPacket);
				controller->Send(pakcetBuffer);
			});

		clientHUD->ShowWidgetFromName(TEXT("EditBox"));
	}

	return true;
}

bool Handle_S2C_EmailVerified(ANetworkController* controller, Protocol::S2C_EmailVerified& pkt)
{
	ULDGameInstance* gameInstance = Cast<ULDGameInstance>(controller->GetGameInstance());
	if (nullptr == gameInstance)
	{
		return false;
	}

	AClientHUD* clientHUD = Cast<AClientHUD>(controller->GetHUD());
	if (nullptr == clientHUD)
	{
		return false;
	}

	clientHUD->CleanWidgetFromName(TEXT("LoadingServer"));

	int32 error = pkt.error();
	if (error != 0)
	{
		UW_Notification* notification = Cast<UW_Notification>(clientHUD->GetWidgetFromName(TEXT("Notification")));
		notification->SetTitle(TEXT("이메일 인증 실패"));
		notification->SetNotification(TEXT("인증번호가 일치하지 않습니다"));
		notification->SetButtonText(TEXT("다시 인증하기"));

		notification->mNotificationDelegate.BindLambda([=]()
			{
				clientHUD->CleanWidgetFromName(TEXT("Notification"));
				clientHUD->CleanWidgetFromName(TEXT("EditBox"));
			});

		clientHUD->ShowWidgetFromName("Notification");
	}
	else
	{
		UW_Notification* notification = Cast<UW_Notification>(clientHUD->GetWidgetFromName(TEXT("Notification")));
		notification->SetTitle(TEXT("회원 가입 성공"));
		notification->SetNotification(TEXT("회원 가입에 성공하였습니다"));
		notification->SetButtonText(TEXT("로그인 하기"));

		notification->mNotificationDelegate.BindLambda([=]()
			{
				clientHUD->CleanWidgetFromName(TEXT("Notification"));
				clientHUD->CleanWidgetFromName(TEXT("Singup"));
				clientHUD->CleanWidgetFromName(TEXT("EditBox"));
				clientHUD->ShowWidgetFromName(TEXT("Singin"));
			});

		clientHUD->ShowWidgetFromName("Notification");
	}

	return true;
}

bool Handle_S2C_Nickname(ANetworkController* controller, Protocol::S2C_Nickname& pkt)
{
	return false;
}