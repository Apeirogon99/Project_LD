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

#include <Widget/Identity/W_SelectCharacter.h>

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
	AGameModeBase* gameMode = controller->GetWorld()->GetAuthGameMode();
	ANetworkGameMode* networkGameMode = Cast<ANetworkGameMode>(gameMode);
	if (nullptr == networkGameMode)
	{
		return false;
	}

	networkGameMode->RequestExitGame();

	return true;
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
		FString ticket = UNetworkUtils::ConvertFString(pkt.ticket());
		gameInstance->mTicket = ticket;

		AGameModeBase* gameMode = controller->GetWorld()->GetAuthGameMode();
		ANetworkGameMode* networkGameMode = Cast<ANetworkGameMode>(gameMode);
		if (nullptr == networkGameMode)
		{
			return false;
		}

		networkGameMode->RequestTravelLevel(TEXT("L_SelectCharacter"));

		//서버 선택창
		//clientHUD->ShowWidgetFromName(TEXT("SelectServer"));
		//clientHUD->AllSelfHitTestInvisibleButOneWidget(TEXT("Singin"));
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
				clientHUD->CleanWidgetFromName(TEXT("Singup"));
				clientHUD->CleanWidgetFromName(TEXT("EditBox"));
				clientHUD->AllSelfHitTestInvisibleButOneWidget(TEXT("Notification"));
				clientHUD->ShowWidgetFromName(TEXT("Singin"));
			});

		clientHUD->ShowWidgetFromName("Notification");
	}

	return true;
}

bool Handle_S2C_LoadServer(ANetworkController* controller, Protocol::S2C_LoadServer& pkt)
{
	return false;
}

bool Handle_S2C_LoadCharacters(ANetworkController* controller, Protocol::S2C_LoadCharacters& pkt)
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

	UW_SelectCharacter* selectCharacterWidget = Cast<UW_SelectCharacter>(clientHUD->GetWidgetFromName(TEXT("SelectCharacter")));
	if (nullptr == selectCharacterWidget) return false;

	for (int i = 0; i < pkt.character_size(); ++i)
	{
		const Protocol::SCharacterData& character = pkt.character(i);

		FCharacterDatas characterDatas;

		characterDatas.mName		= UNetworkUtils::ConvertFString(character.name());
		characterDatas.mClass		= character.job();
		characterDatas.mTribe		= character.tribe();
		characterDatas.mLevel		= character.level();
		characterDatas.mPosition	= character.position();

		characterDatas.mSkin		= character.skin();
		characterDatas.mHair		= character.hair();
		characterDatas.mEye			= character.eye();
		characterDatas.mEyebrow		= character.eyebrow();

		selectCharacterWidget->LoadCharacterInfo(characterDatas);
	}

	clientHUD->CleanWidgetFromName(TEXT("LoadingServer"));
	clientHUD->ShowWidgetFromName(TEXT("SelectCharacter"));

	return true;
}

bool Handle_S2C_SelectServer(ANetworkController* controller, Protocol::S2C_SelectServer& pkt)
{
	return false;
}

bool Handle_S2C_CreateCharacter(ANetworkController* controller, Protocol::S2C_CreateCharacter& pkt)
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
		notification->SetTitle(TEXT("닉네임 중복"));
		notification->SetNotification(TEXT("이미 사용중인 닉네임 입니다"));
		notification->SetButtonText(TEXT("확인"));

		notification->mNotificationDelegate.BindLambda([=]()
			{
				clientHUD->CleanWidgetFromName(TEXT("Notification"));
			});

		clientHUD->ShowWidgetFromName("Notification");
	}
	else
	{
		UW_Notification* notification = Cast<UW_Notification>(clientHUD->GetWidgetFromName(TEXT("Notification")));
		notification->SetTitle(TEXT("생성 완료"));
		notification->SetNotification(TEXT("축하합니다 캐릭터를 생성하셨습니다"));
		notification->SetButtonText(TEXT("생성하기"));


		AGameModeBase* gameMode = controller->GetWorld()->GetAuthGameMode();
		ANetworkGameMode* networkGameMode = Cast<ANetworkGameMode>(gameMode);
		if (nullptr == networkGameMode)
		{
			return false;
		}

		notification->mNotificationDelegate.BindLambda([=]()
			{
				clientHUD->CleanWidgetFromName(TEXT("Notification"));
				networkGameMode->RequestTravelLevel(TEXT("L_SelectCharacter"));
			});

		clientHUD->ShowWidgetFromName("Notification");
	}

	return true;
}

bool Handle_S2C_TravelServer(ANetworkController* controller, Protocol::S2C_TravelServer& pkt)
{
	return false;
}