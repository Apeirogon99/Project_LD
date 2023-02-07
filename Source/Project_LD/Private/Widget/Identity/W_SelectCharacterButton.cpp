// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Identity/W_SelectCharacterButton.h"
#include <Components/Button.h>
#include <Components/TextBlock.h>

#include <Widget/Common/W_Reconfirm.h>
#include <Widget/Handler/ClientHUD.h>

#include <Framework/Identity/C_Dummy.h>

void UW_SelectCharacterButton::NativeConstruct()
{
	Super::NativeConstruct();

	mCharacterButton	= Cast<UButton>(GetWidgetFromName(TEXT("mCharacterButton")));
	mCharacterInfoText	= Cast<UTextBlock>(GetWidgetFromName(TEXT("mCharacterInfoText")));
	mButtonText			= Cast<UTextBlock>(GetWidgetFromName(TEXT("mButtonText")));

	mIsInfo = false;

	if (mCharacterButton != nullptr)
	{
		mCharacterButton->OnClicked.AddDynamic(this, &UW_SelectCharacterButton::Click_Character);
	}
}

void UW_SelectCharacterButton::Click_Character()
{
	APlayerController* playerControll = GetOwningPlayer();
	AClientHUD* clientHUD = Cast<AClientHUD>(playerControll->GetHUD());

	if (nullptr != character)
	{
		UW_Reconfirm* reconfirm = Cast<UW_Reconfirm>(clientHUD->GetWidgetFromName(TEXT("Reconfirm")));
		reconfirm->SetTitleText(TEXT("게임 시작"));
		reconfirm->SetReconfirmText(TEXT("해당 캐릭터로 시작하시겠습니까?"));
		reconfirm->SetConfirmButtonText(TEXT("시작"));
		reconfirm->SetCancleButtonText(TEXT("취소"));
		reconfirm->mReConfirmDelegate.BindUFunction(this, FName("StartCharacter"));
		reconfirm->mCancleDelegate.BindUFunction(this, FName("CancleExitGame"));
		clientHUD->ShowWidgetFromName(TEXT("Reconfirm"));
	}
	else
	{
		UW_Reconfirm* reconfirm = Cast<UW_Reconfirm>(clientHUD->GetWidgetFromName(TEXT("Reconfirm")));
		reconfirm->SetTitleText(TEXT("캐릭터 생성"));
		reconfirm->SetReconfirmText(TEXT("캐릭터를 생성하시겠습니까?"));
		reconfirm->SetConfirmButtonText(TEXT("생성"));
		reconfirm->SetCancleButtonText(TEXT("취소"));
		reconfirm->mReConfirmDelegate.BindUFunction(this, FName("CreateCharacter"));
		reconfirm->mCancleDelegate.BindUFunction(this, FName("CancleExitGame"));
		clientHUD->ShowWidgetFromName(TEXT("Reconfirm"));
	}
}

void UW_SelectCharacterButton::SetCharacterInfo(const FString& inLevel, const FString& inName)
{

	if (inLevel.IsEmpty() || inName.IsEmpty())
	{
		mIsInfo = false;
		return;
	}

	FText characterTitle = FText::FromString(FString::Printf(TEXT("Lv.%s %s"), *inLevel, *inName));
	mCharacterInfoText->SetText(characterTitle);

	FString buttonText = FString(TEXT(""));
	mButtonText->SetText(FText::FromString(buttonText));

	FActorSpawnParameters spawnParams;
	spawnParams.Owner = GetOwningPlayer();
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	character = GetWorld()->SpawnActor<AC_Dummy>(mDummyCharacterClass, mCharacterLocation, mCharacterRotation, spawnParams);

	mIsInfo = true;
	
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
}

void UW_SelectCharacterButton::CancleExitGame()
{
	APlayerController* playerControll = GetOwningPlayer();
	AClientHUD* clientHUD = Cast<AClientHUD>(playerControll->GetHUD());

	clientHUD->CleanWidgetFromName(TEXT("Reconfirm"));
}
