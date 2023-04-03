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

bool Handle_S2C_EnterIdentityServer(ANetworkController* controller, Protocol::S2C_EnterIdentityServer& pkt)
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

bool Handle_S2C_LeaveIdentityServer(ANetworkController* controller, Protocol::S2C_LeaveIdentityServer& pkt)
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

	clientHUD->CollapsedWidgetFromName(TEXT("LoadingServer"));

	int32 error = pkt.error();
	if (error != 0)
	{
		UW_Notification* notification = Cast<UW_Notification>(clientHUD->GetWidgetFromName(TEXT("Notification")));
		notification->SetTitle(TEXT("로그인 실패"));
		notification->SetNotification(UNetworkUtils::GetNetworkErrorToString(error));
		notification->SetButtonText(TEXT("확인"));

		notification->mNotificationDelegate.BindLambda([=]()
			{
				clientHUD->AllSelfHitTestInvisibleButOneWidget(TEXT("Notification"));
			});

		clientHUD->SelfHitTestInvisibleWidgetFromName(TEXT("Notification"));
	}
	else
	{
		FString token = UNetworkUtils::ConvertFString(pkt.token());
		gameInstance->mToken = token;

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

	clientHUD->CollapsedWidgetFromName(TEXT("LoadingServer"));

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

		clientHUD->SelfHitTestInvisibleWidgetFromName(TEXT("Notification"));
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
				emailVerifiedPacket.set_verified_code(verfiedStr);
				SendBufferPtr pakcetBuffer = FIdentityPacketHandler::MakeSendBuffer(controller, emailVerifiedPacket);
				controller->Send(pakcetBuffer);
			});

		clientHUD->SelfHitTestInvisibleWidgetFromName(TEXT("EditBox"));
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

	clientHUD->CollapsedWidgetFromName(TEXT("LoadingServer"));

	int32 error = pkt.error();
	if (error != 0)
	{
		UW_Notification* notification = Cast<UW_Notification>(clientHUD->GetWidgetFromName(TEXT("Notification")));
		notification->SetTitle(TEXT("이메일 인증 실패"));
		notification->SetNotification(TEXT("인증번호가 일치하지 않습니다"));
		notification->SetButtonText(TEXT("다시 인증하기"));

		notification->mNotificationDelegate.BindLambda([=]()
			{
				clientHUD->CollapsedWidgetFromName(TEXT("Notification"));
			});

		clientHUD->SelfHitTestInvisibleWidgetFromName(TEXT("Notification"));
	}
	else
	{
		UW_Notification* notification = Cast<UW_Notification>(clientHUD->GetWidgetFromName(TEXT("Notification")));
		notification->SetTitle(TEXT("회원 가입 성공"));
		notification->SetNotification(TEXT("회원 가입에 성공하였습니다"));
		notification->SetButtonText(TEXT("로그인 하기"));

		notification->mNotificationDelegate.BindLambda([=]()
			{
				clientHUD->AllCollapsedButOneWidget(TEXT("Singin"));
				clientHUD->SelfHitTestInvisibleWidgetFromName(TEXT("LoginScreen"));
			});

		clientHUD->CollapsedWidgetFromName(TEXT("Notification"));
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

	for (int index = 0; index < pkt.appearance_size(); ++index)
	{
		FString name = UNetworkUtils::ConvertFString(pkt.name().Get(index));
		
		const Protocol::SCharacterAppearance& appearance = pkt.appearance(index);
		FCharacterAppearance characterAppearance;
		characterAppearance.UpdateAppearance(appearance);

		const Protocol::SCharacterEqipment& eqipment = pkt.eqipment(index);
		FCharacterEquipment characterEquipment;
		characterEquipment.UpdateEquipments(eqipment);

		selectCharacterWidget->LoadCharacterInfo(name, characterAppearance, characterEquipment);
	}

	clientHUD->CollapsedWidgetFromName(TEXT("LoadingServer"));
	clientHUD->SelfHitTestInvisibleWidgetFromName(TEXT("SelectCharacter"));

	return true;
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

	clientHUD->CollapsedWidgetFromName(TEXT("LoadingServer"));

	int32 error = pkt.error();
	if (error != 0)
	{
		UW_Notification* notification = Cast<UW_Notification>(clientHUD->GetWidgetFromName(TEXT("Notification")));
		notification->SetTitle(TEXT("닉네임 중복"));
		notification->SetNotification(TEXT("이미 사용중인 닉네임 입니다"));
		notification->SetButtonText(TEXT("확인"));

		notification->mNotificationDelegate.BindLambda([=]()
			{
				clientHUD->CollapsedWidgetFromName(TEXT("Notification"));
			});

		clientHUD->SelfHitTestInvisibleWidgetFromName("Notification");
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
				clientHUD->CollapsedWidgetFromName(TEXT("Notification"));
				networkGameMode->RequestTravelLevel(TEXT("L_SelectCharacter"));
			});

		clientHUD->SelfHitTestInvisibleWidgetFromName("Notification");
	}

	return true;
}

bool Handle_S2C_UpdateAppearance(ANetworkController* controller, Protocol::S2C_UpdateAppearance& pkt)
{
	return false;
}

bool Handle_S2C_DeleteCharacter(ANetworkController* controller, Protocol::S2C_DeleteCharacter& pkt)
{
	return false;
}

bool Handle_S2C_UpdateNickName(ANetworkController* controller, Protocol::S2C_UpdateNickName& pkt)
{
	return false;
}

bool Handle_S2C_TravelServer(ANetworkController* controller, Protocol::S2C_TravelServer& pkt)
{
	return false;
}