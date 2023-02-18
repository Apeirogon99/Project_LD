// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Identity/W_SelectCharacterButton.h"
#include <Components/Button.h>
#include <Components/TextBlock.h>

#include <Widget/Common/W_Reconfirm.h>
#include <Widget/Handler/ClientHUD.h>

#include <Framework/Identity/C_Dummy.h>
#include <Network/NetworkGameMode.h>
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
	mButtonText			= Cast<UTextBlock>(GetWidgetFromName(TEXT("mButtonText")));

	if (mCharacterButton != nullptr)
	{
		mCharacterButton->OnClicked.AddDynamic(this, &UW_SelectCharacterButton::Click_Character);
	}
}

void UW_SelectCharacterButton::Click_Character()
{
	APlayerController* playerControll = GetOwningPlayer();
	AClientHUD* clientHUD = Cast<AClientHUD>(playerControll->GetHUD());

	UW_Reconfirm* reconfirm = Cast<UW_Reconfirm>(clientHUD->GetWidgetFromName(TEXT("Reconfirm")));
	if (mClickMode == EClickMode::Start)
	{

		character->SetAnimation(mSelectCharacterAnimation);

		reconfirm->SetTitleText(TEXT("게임 시작"));
		reconfirm->SetReconfirmText(TEXT("해당 캐릭터로 시작하시겠습니까?"));
		reconfirm->SetConfirmButtonText(TEXT("시작"));
		reconfirm->SetCancleButtonText(TEXT("취소"));
		reconfirm->mReConfirmDelegate.BindUFunction(this, FName("StartCharacter"));
		reconfirm->mCancleDelegate.BindUFunction(this, FName("CancleButton"));
	}
	else if (mClickMode == EClickMode::Create)
	{
		reconfirm->SetTitleText(TEXT("캐릭터 생성"));
		reconfirm->SetReconfirmText(TEXT("캐릭터를 생성하시겠습니까?"));
		reconfirm->SetConfirmButtonText(TEXT("생성"));
		reconfirm->SetCancleButtonText(TEXT("취소"));
		reconfirm->mReConfirmDelegate.BindUFunction(this, FName("CreateCharacter"));
		reconfirm->mCancleDelegate.BindUFunction(this, FName("CancleButton"));
	}
	else if (mClickMode == EClickMode::Appearance)
	{
		reconfirm->SetTitleText(TEXT("외형 변경"));
		reconfirm->SetReconfirmText(TEXT("외형 변경을 하시겠습니까?"));
		reconfirm->SetConfirmButtonText(TEXT("변경"));
		reconfirm->SetCancleButtonText(TEXT("취소"));
		reconfirm->mReConfirmDelegate.BindUFunction(this, FName("AppearanceCharacter"));
		reconfirm->mCancleDelegate.BindUFunction(this, FName("CancleButton"));
	}
	else if (mClickMode == EClickMode::Delete)
	{
		reconfirm->SetTitleText(TEXT("캐릭터 삭제"));
		reconfirm->SetReconfirmText(TEXT("해당 캐릭터를 삭제하겠습니까?"));
		reconfirm->SetConfirmButtonText(TEXT("삭제"));
		reconfirm->SetCancleButtonText(TEXT("취소"));
		reconfirm->mReConfirmDelegate.BindUFunction(this, FName("DeleteCharacter"));
		reconfirm->mCancleDelegate.BindUFunction(this, FName("CancleButton"));
	}
	else if (mClickMode == EClickMode::ReviseName)
	{
		reconfirm->SetTitleText(TEXT("닉네임 변경"));
		reconfirm->SetReconfirmText(TEXT("닉네임을 변경하시겠습니까?"));
		reconfirm->SetConfirmButtonText(TEXT("변경"));
		reconfirm->SetCancleButtonText(TEXT("취소"));
		reconfirm->mReConfirmDelegate.BindUFunction(this, FName("ReviseNameCharacter"));
		reconfirm->mCancleDelegate.BindUFunction(this, FName("CancleButton"));
	}
	else
	{
		return;
	}

	clientHUD->ShowWidgetFromName(TEXT("Reconfirm"));
}

void UW_SelectCharacterButton::SetCharacterInfo(const FCharacterDatas& inCharacterDatas)
{
	FText characterTitle = FText::FromString(FString::Printf(TEXT("Lv.%ld %s"), inCharacterDatas.mLevel, *inCharacterDatas.mName));
	mCharacterInfoText->SetText(characterTitle);

	FActorSpawnParameters spawnParams;
	spawnParams.Owner = GetOwningPlayer();
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	character = GetWorld()->SpawnActor<AC_Dummy>(mDummyCharacterClass, mCharacterLocation, mCharacterRotation, spawnParams);
	character->SetCharacterDatas(inCharacterDatas);
	character->SetAnimation(mDefaultCharacterAnimation);

	SetClickMode(EClickMode::Start);
}

void UW_SelectCharacterButton::SetClickMode(EClickMode inClickMode)
{
	mClickMode = inClickMode;

	FString buttonText = FString(TEXT(""));

	if (character)
	{
		switch (mClickMode)
		{
		case EClickMode::None:
			buttonText = FString(TEXT("Error"));
			break;
		case EClickMode::Start:
			buttonText = FString(TEXT(""));
			break;
		case EClickMode::Appearance:
			buttonText = FString(TEXT("?"));
			break;
		case EClickMode::Delete:
			buttonText = FString(TEXT("-"));
			break;
		case EClickMode::ReviseName:
			buttonText = FString(TEXT("*"));
			break;
		default:
			buttonText = FString(TEXT("Error"));
			break;
		}
	}
	else
	{
		mClickMode = EClickMode::Create;
		buttonText = FString(TEXT("+"));
	}

	mButtonText->SetText(FText::FromString(buttonText));
}

void UW_SelectCharacterButton::PreviousClickMode()
{
	EClickMode previousClickMode = EClickMode::None;
	if (character)
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
	//해당 서버 아이피와 포트를 가지고 있을거니까 거기로 보내버리면됨
	//게임 모드 불러오셈
	APlayerController* playerControll = GetOwningPlayer();
	AClientHUD* clientHUD = Cast<AClientHUD>(playerControll->GetHUD());
	clientHUD->CleanWidgetFromName(TEXT("Reconfirm"));
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
		gameinstance->mCharacterDatas.mPosition = mCharacterButtonNumber;
	}

	ANetworkGameMode* networkGameMode = Cast<ANetworkGameMode>(GetWorld()->GetAuthGameMode());
	networkGameMode->RequestTravelLevel(TEXT("L_SelectClass"));
	
}

void UW_SelectCharacterButton::AppearanceCharacter()
{

}

void UW_SelectCharacterButton::DeleteCharacter()
{

}

void UW_SelectCharacterButton::ReviseNameCharacter()
{

}

void UW_SelectCharacterButton::CancleButton()
{
	APlayerController* playerControll = GetOwningPlayer();
	AClientHUD* clientHUD = Cast<AClientHUD>(playerControll->GetHUD());
	clientHUD->CleanWidgetFromName(TEXT("Reconfirm"));

	if (character)
	{
		character->SetAnimation(mDefaultCharacterAnimation);
	}

}
