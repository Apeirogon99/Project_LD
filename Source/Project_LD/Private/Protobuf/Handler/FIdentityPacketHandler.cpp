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
#include <PacketUtils.h>
#include <Network/NetworkSession.h>

#include <Widget/WidgetUtils.h>
#include <Widget/Identity/W_SelectCharacter.h>
#include <Widget/Test/W_Test.h>

#include <DatabaseErrorTypes.h>

bool Handle_S2C_EnterIdentityServer(ANetworkController* controller, Protocol::S2C_EnterIdentityServer& pkt)
{
	//
	AGameModeBase* gameMode = controller->GetWorld()->GetAuthGameMode();
	ANetworkGameMode* networkGameMode = Cast<ANetworkGameMode>(gameMode);
	if (nullptr == networkGameMode)
	{
		return false;
	}

	AClientHUD* clientHUD = Cast<AClientHUD>(controller->GetHUD());
	if (nullptr == clientHUD)
	{
		return false;
	}

	clientHUD->ShowWidgetFromName(TEXT("LoginScreen"));
	clientHUD->ShowWidgetFromName(TEXT("Singin"));

	UNetworkUtils::NetworkConsoleLog("Welcome LD_Project", ELogLevel::Warning);

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

	clientHUD->CleanWidgetFromName(TEXT("LoadingServer"));

	int32 error = pkt.error();
	if (error != GetDatabaseErrorToInt(EDBErrorType::SUCCESS))
	{
		FNotificationDelegate notificationDelegate;
		notificationDelegate.BindLambda([=]()
			{
				clientHUD->CleanWidgetFromName(TEXT("Notification"));
			});

		const FString description = UNetworkUtils::GetNetworkErrorToString(error);
		bool ret = UWidgetUtils::SetNotification(clientHUD, TEXT("로그인 실패"), description, TEXT("확인"), notificationDelegate);
		if (ret == false)
		{
			return false;
		}
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

	clientHUD->CleanWidgetFromName(TEXT("LoadingServer"));

	int32 error = pkt.error();
	if (error != GetDatabaseErrorToInt(EDBErrorType::SUCCESS))
	{
		FNotificationDelegate notificationDelegate;
		notificationDelegate.BindLambda([=]()
			{
				clientHUD->CleanWidgetFromName(TEXT("Notification"));
			});

		bool ret = UWidgetUtils::SetNotification(clientHUD, TEXT("회원가입 실패"), UNetworkUtils::GetNetworkErrorToString(error), TEXT("확인"), notificationDelegate);
		if (ret == false)
		{
			return false;
		}
	}
	else
	{
		FButtonDelegate editBoxDelegate;
		editBoxDelegate.BindLambda([=](const FString& inCertifiedEmail)
			{
				clientHUD->ShowWidgetFromName(TEXT("LoadingServer"));

				Protocol::C2S_EmailVerified emailVerifiedPacket;
				std::string verfiedStr = UNetworkUtils::ConvertString(inCertifiedEmail);
				emailVerifiedPacket.set_verified_code(verfiedStr);
				SendBufferPtr pakcetBuffer = FIdentityPacketHandler::MakeSendBuffer(controller, emailVerifiedPacket);
				controller->Send(pakcetBuffer);
			});

		bool ret = UWidgetUtils::SetEditBox(clientHUD, TEXT("이메일 인증"), TEXT("이메일 인증번호"), TEXT("인증하기"), editBoxDelegate);
		if (ret == false)
		{
			return false;
		}
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

	int32 result = pkt.error();
	if (result != GetDatabaseErrorToInt(EDBErrorType::SUCCESS))
	{
		FNotificationDelegate notificationDelegate;
		notificationDelegate.BindLambda([=]()
			{
				clientHUD->CleanWidgetFromName(TEXT("Notification"));
			});

		bool error = UWidgetUtils::SetNotification(clientHUD, TEXT("이메일 인증 실패"), UNetworkUtils::GetNetworkErrorToString(result), TEXT("다시 인증하기"), notificationDelegate);
		if (error == false)
		{
			return false;
		}
	}
	else
	{
		FNotificationDelegate notificationDelegate;
		notificationDelegate.BindLambda([=]()
			{
				clientHUD->CleanWidgetFromName(TEXT("Notification"));
				clientHUD->ShowWidgetFromName(TEXT("LoginScreen"));
			});

		bool error = UWidgetUtils::SetNotification(clientHUD, TEXT("회원 가입 성공"), UNetworkUtils::GetNetworkErrorToString(result), TEXT("로그인 하기"), notificationDelegate);
		if (error == false)
		{
			return false;
		}
	}

	return true;
}

bool Handle_S2C_LoadServer(ANetworkController* controller, Protocol::S2C_LoadServer& pkt)
{
	return true;
}

bool Handle_S2C_SelectServer(ANetworkController* controller, Protocol::S2C_SelectServer& pkt)
{
	return true;
}

bool Handle_S2C_StartGame(ANetworkController* controller, Protocol::S2C_StartGame& pkt)
{
	return true;
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

	UW_SelectCharacter* selectCharacterWidget = nullptr;
	UUserWidget* outWidget = clientHUD->GetWidgetFromName(TEXT("SelectCharacter"));
	if (outWidget == nullptr)
	{
		return false;
	}

	selectCharacterWidget = Cast<UW_SelectCharacter>(outWidget);
	if (selectCharacterWidget == nullptr)
	{
		return false;
	}

	const int32 maxCharacterDataSize = pkt.character_data().size();
	for (int index = 0; index < maxCharacterDataSize; ++index)
	{
		const Protocol::SCharacterData& curCharacterData = pkt.character_data(index);
		FCharacterData newCharacterData;
		newCharacterData.UpdateCharacterData(curCharacterData);

		FString name = UNetworkUtils::ConvertFString(curCharacterData.name());
		int32 level = curCharacterData.level();
		ECharacterClass characterClass = StaticCast<ECharacterClass>(curCharacterData.character_class());
		
		const Protocol::SCharacterAppearance& appearance = curCharacterData.appearance();
		FCharacterAppearance characterAppearance;
		characterAppearance.UpdateAppearance(appearance);

		const Protocol::SCharacterEqipment& eqipment = curCharacterData.eqipment();
		FCharacterEquipment characterEquipment;
		characterEquipment.UpdateEquipments(eqipment);

		FCharacterData characterData;
		characterData.mName = name;
		characterData.mLevel = level;
		characterData.mClass = characterClass;
		characterData.mAppearance = characterAppearance;
		characterData.mEquipment = characterEquipment;

		selectCharacterWidget->CreateCharacter(characterData);
	}

	clientHUD->CleanWidgetFromName(TEXT("LoadingServer"));
	clientHUD->ShowWidgetFromName(TEXT("SelectCharacter"));

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

	clientHUD->CleanWidgetFromName(TEXT("LoadingServer"));

	int32 result = pkt.error();
	if (result != GetDatabaseErrorToInt(EDBErrorType::SUCCESS))
	{
		FNotificationDelegate notificationDelegate;
		notificationDelegate.BindLambda([=]()
			{
				clientHUD->CleanWidgetFromName(TEXT("Notification"));
			});

		bool error = UWidgetUtils::SetNotification(clientHUD, TEXT("닉네임 중복"), UNetworkUtils::GetNetworkErrorToString(result), TEXT("확인"), notificationDelegate);
		if (error == false)
		{
			return false;
		}
	}
	else
	{
		AGameModeBase* gameMode = controller->GetWorld()->GetAuthGameMode();
		ANetworkGameMode* networkGameMode = Cast<ANetworkGameMode>(gameMode);
		if (nullptr == networkGameMode)
		{
			return false;
		}

		FNotificationDelegate notificationDelegate;
		notificationDelegate.BindLambda([=]()
			{
				clientHUD->CleanWidgetFromName(TEXT("Notification"));
				networkGameMode->RequestTravelLevel(TEXT("L_SelectCharacter"));
			});

		bool error = UWidgetUtils::SetNotification(clientHUD, TEXT("생성 완료"), UNetworkUtils::GetNetworkErrorToString(result), TEXT("확인"), notificationDelegate);
		if (error == false)
		{
			return false;
		}
	}

	return true;
}

bool Handle_S2C_DeleteCharacter(ANetworkController* controller, Protocol::S2C_DeleteCharacter& pkt)
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
	if (error != GetDatabaseErrorToInt(EDBErrorType::SUCCESS))
	{
		FNotificationDelegate notificationDelegate;
		notificationDelegate.BindLambda([=]()
			{
				clientHUD->CleanWidgetFromName(TEXT("Notification"));
			});

		const FString description = UNetworkUtils::GetNetworkErrorToString(error);
		bool ret = UWidgetUtils::SetNotification(clientHUD, TEXT("캐릭터 삭제 실패"), description, TEXT("확인"), notificationDelegate);
		if (ret == false)
		{
			return false;
		}
	}
	else
	{
		AGameModeBase* gameMode = controller->GetWorld()->GetAuthGameMode();
		ANetworkGameMode* networkGameMode = Cast<ANetworkGameMode>(gameMode);
		if (nullptr == networkGameMode)
		{
			return false;
		}

		networkGameMode->RequestTravelLevel(TEXT("L_SelectCharacter"));
	}

	return true;
}

bool Handle_S2C_TravelServer(ANetworkController* controller, Protocol::S2C_TravelServer& pkt)
{
	return false;
}