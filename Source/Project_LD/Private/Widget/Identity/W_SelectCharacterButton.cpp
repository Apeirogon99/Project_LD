// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Identity/W_SelectCharacterButton.h"
#include <Components/Button.h>
#include <Components/TextBlock.h>
#include <Components/Image.h>

#include <Widget/Handler/ClientHUD.h>
#include <Widget/WidgetUtils.h>

#include <Network/NetworkGameMode.h>
#include <Network/NetworkCharacter.h>
#include <Network/NetworkUtils.h>
#include <Framework/Character/AppearanceCharacter.h>

#include <Framework/Gameinstance/LDGameInstance.h>
#include <Protobuf/Handler/FClientPacketHandler.h>
#include <Protobuf/Handler/FIdentityPacketHandler.h>

void UW_SelectCharacterButton::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	SetClickMode(EClickMode::Create);
}

void UW_SelectCharacterButton::NativeConstruct()
{
	Super::NativeConstruct();

	mCharacterButton	= Cast<UButton>(GetWidgetFromName(TEXT("mCharacterButton")));
	mCharacterInfoText	= Cast<UTextBlock>(GetWidgetFromName(TEXT("mCharacterInfoText")));
	mButtonImage		= Cast<UImage>(GetWidgetFromName(TEXT("mButtonImage")));

	if (mCharacterButton != nullptr)
	{
		mCharacterButton->OnClicked.AddDynamic(this, &UW_SelectCharacterButton::Click_Character);
	}
}

void UW_SelectCharacterButton::Click_Character()
{
	APlayerController* playerControll = GetOwningPlayer();
	AClientHUD* clientHUD = Cast<AClientHUD>(playerControll->GetHUD());

	FString titleText;
	FString reconfirmText;
	FString confrimText;
	FString cancleText;
	FConfirmButtonDelegate confirmDelegate;

	FCancleButtonDelegate cancleDelegate;
	cancleDelegate.BindUFunction(this, FName("CancleButton"));

	if (mClickMode == EClickMode::Start)
	{
		titleText		= (TEXT("게임 시작"));
		reconfirmText	= (TEXT("해당 캐릭터로 시작하시겠습니까?"));
		confrimText		= (TEXT("시작"));
		cancleText		= (TEXT("취소"));
		confirmDelegate.BindUFunction(this, FName("StartCharacter"));
	}
	else if (mClickMode == EClickMode::Create)
	{
		titleText		= (TEXT("캐릭터 생성"));
		reconfirmText	= (TEXT("캐릭터를 생성하시겠습니까?"));
		confrimText		= (TEXT("생성"));
		cancleText		= (TEXT("취소"));
		confirmDelegate.BindUFunction(this, FName("CreateCharacter"));
	}
	else if (mClickMode == EClickMode::Appearance)
	{
		titleText		= (TEXT("외형 변경"));
		reconfirmText	= (TEXT("외형 변경을 하시겠습니까?"));
		confrimText		= (TEXT("변경"));
		cancleText		= (TEXT("취소"));
		confirmDelegate.BindUFunction(this, FName("AppearanceCharacter"));
	}
	else if (mClickMode == EClickMode::Delete)
	{
		titleText		= (TEXT("캐릭터 삭제"));
		reconfirmText	= (TEXT("해당 캐릭터를 삭제하겠습니까?"));
		confrimText		= (TEXT("삭제"));
		cancleText		= (TEXT("취소"));
		confirmDelegate.BindUFunction(this, FName("DeleteCharacter"));
	}
	else if (mClickMode == EClickMode::ReviseName)
	{
		titleText		= (TEXT("닉네임 변경"));
		reconfirmText	= (TEXT("닉네임을 변경하시겠습니까?"));
		confrimText		= (TEXT("변경"));
		cancleText		= (TEXT("취소"));
		confirmDelegate.BindUFunction(this, FName("ReviseNameCharacter"));
	}

	if (mCharacter)
	{
		mCharacter->UpdateCharacterPose(ECharacterPose::StandUp, false);
	}

	bool error = UWidgetUtils::SetReconfirm(clientHUD, titleText, reconfirmText, confrimText, cancleText, confirmDelegate, cancleDelegate);
	if (error == false)
	{
		return;
	}

}

void UW_SelectCharacterButton::SetCharacterInfo(const FCharacterData& inCharacterData)
{

	mCharacterData = inCharacterData;

	FText characterTitle = FText::FromString(FString::Printf(TEXT("LV.%d - %s"), mCharacterData.GetLevel(), *mCharacterData.GetName()));
	mCharacterInfoText->SetText(characterTitle);

	AAppearanceCharacter* NewDummyCharacter = nullptr;
	TSubclassOf<AAppearanceCharacter> raceClass = mDummyCharacterClass[StaticCast<int32>(mCharacterData.GetAppearance().GetRace())];
	if (raceClass)
	{
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = GetOwningPlayer();
		spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		mCharacter = GetWorld()->SpawnActor<AAppearanceCharacter>(raceClass, mCharacterLocation, mCharacterRotation, spawnParams);
		mCharacter->UpdateCharacterVisual(mCharacterData.GetAppearance(), mCharacterData.GetEquipment());
	}

	if (mCharacter)
	{
		mCharacter->UpdateCharacterPose(ECharacterPose::Seat, false);
	}

	SetClickMode(EClickMode::Start);
}

void UW_SelectCharacterButton::SetClickMode(EClickMode inClickMode)
{
	mClickMode = inClickMode;
	
	UTexture2D* texture = nullptr;

	if (mCharacter)
	{
		switch (mClickMode)
		{
		case EClickMode::None:
			texture = nullptr;
			break;
		case EClickMode::Start:
			texture = nullptr;
			break;
		case EClickMode::Appearance:
			texture = mCheckTexture;
			break;
		case EClickMode::Delete:
			texture = mCheckTexture;
			break;
		case EClickMode::ReviseName:
			texture = mCheckTexture;
			break;
		default:
			texture = nullptr;
			break;
		}
	}
	else
	{
		mClickMode = EClickMode::Create;
		texture = mAddTexture;
	}

	if (texture == nullptr)
	{
		mButtonImage->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		mButtonImage->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		mButtonImage->SetBrushFromTexture(texture);
	}

}

void UW_SelectCharacterButton::PreviousClickMode()
{
	EClickMode previousClickMode = EClickMode::None;
	if (mCharacter)
	{
		previousClickMode = EClickMode::Start;
	}
	else
	{
		previousClickMode = EClickMode::Create;
	}

	SetClickMode(previousClickMode);
}

void UW_SelectCharacterButton::StartCharacter()
{
	APlayerController* playerControll = GetOwningPlayer();
	AClientHUD* clientHUD = Cast<AClientHUD>(playerControll->GetHUD());
	if (nullptr == clientHUD)
	{
		return;
	}
	
	clientHUD->CleanWidgetFromName(TEXT("Reconfirm"));

	ANetworkController* networkController = Cast<ANetworkController>(playerControll);
	if (nullptr == networkController)
	{
		return;
	}
	const int64& timeStamp = networkController->GetServerTimeStamp();

	ULDGameInstance* gameInstance = Cast<ULDGameInstance>(networkController->GetGameInstance());
	if (nullptr == gameInstance)
	{
		return;
	}

	std::string token = UNetworkUtils::ConvertString(gameInstance->GetToken());

	Protocol::C2S_StartGame startGamePacket;
	startGamePacket.set_character_id(mCharacterData.GetID());
	startGamePacket.set_time_stamp(timeStamp);

	SendBufferPtr pakcetBuffer = FIdentityPacketHandler::MakeSendBuffer(networkController, startGamePacket);
	networkController->Send(pakcetBuffer);
}

void UW_SelectCharacterButton::CreateCharacter()
{
	//커스텀 쪽으로 레벨이동
	APlayerController* playerControll = GetOwningPlayer();
	AClientHUD* clientHUD = Cast<AClientHUD>(playerControll->GetHUD());
	clientHUD->CleanWidgetFromName(TEXT("Reconfirm"));

	ULDGameInstance* gameinstance = Cast<ULDGameInstance>(GetWorld()->GetGameInstance());
	if (gameinstance)
	{
		gameinstance->mCharacterData.GetAppearance().SetSeat(mCharacterButtonNumber);
	}

	ANetworkGameMode* networkGameMode = Cast<ANetworkGameMode>(GetWorld()->GetAuthGameMode());
	networkGameMode->RequestTravelLevel(TEXT("L_SelectClass"));
	
}

void UW_SelectCharacterButton::AppearanceCharacter()
{

}

void UW_SelectCharacterButton::DeleteCharacter()
{
	APlayerController* playerControll = GetOwningPlayer();

	ANetworkController* networkController = Cast<ANetworkController>(playerControll);
	if (nullptr == networkController)
	{
		return;
	}
	const int64& timeStamp = networkController->GetServerTimeStamp();

	AClientHUD* clientHUD = Cast<AClientHUD>(playerControll->GetHUD());
	clientHUD->CleanWidgetFromName(TEXT("Reconfirm"));

	if (mCharacter)
	{
		ANetworkController* controller = Cast<ANetworkGameMode>(GetWorld()->GetAuthGameMode())->GetNetworkController();
		Protocol::C2S_DeleteCharacter packet;

		packet.set_name(UNetworkUtils::ConvertString(mCharacterData.GetName()));
		packet.set_time_stamp(timeStamp);

		clientHUD->ShowWidgetFromName(TEXT("LoadingServer"));

		SendBufferPtr pakcetBuffer = FIdentityPacketHandler::MakeSendBuffer(controller, packet);
		controller->Send(pakcetBuffer);
	}
}

void UW_SelectCharacterButton::ReviseNameCharacter()
{

}

void UW_SelectCharacterButton::CancleButton()
{
	APlayerController* playerControll = GetOwningPlayer();
	AClientHUD* clientHUD = Cast<AClientHUD>(playerControll->GetHUD());
	clientHUD->CleanWidgetFromName(TEXT("Reconfirm"));

	if (mCharacter)
	{
		mCharacter->UpdateCharacterPose(ECharacterPose::StandDown, false);
	}

}
