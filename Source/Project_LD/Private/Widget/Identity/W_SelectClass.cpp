// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Identity/W_SelectClass.h"

#include <Components/Button.h>

#include <Blueprint/WidgetTree.h>
#include <Widget/Handler/ClientHUD.h>

#include <Widget/WidgetUtils.h>
#include <Widget/Common/W_BackButton.h>

#include <Framework/Gameinstance/LDGameInstance.h>
#include <Network/NetworkGameMode.h>

#include <Struct/Game/CharacterDatas.h>

void UW_SelectClass::NativeConstruct()
{
	Super::NativeConstruct();

	mWarriorButton = Cast<UButton>(GetWidgetFromName(TEXT("mWarriorButton")));
	mWizardButton = Cast<UButton>(GetWidgetFromName(TEXT("mWizardButton")));

	if (mWarriorButton != nullptr)
	{
		mWarriorButton->OnClicked.AddUniqueDynamic(this, &UW_SelectClass::Click_Warrior);
	}

	if (mWizardButton != nullptr)
	{
		mWizardButton->OnClicked.AddUniqueDynamic(this, &UW_SelectClass::Click_Wizard);
	}

	mBackButton = this->WidgetTree->FindWidget(FName(TEXT("BW_BackButton")));
	if (mBackButton != nullptr)
	{
		UW_BackButton* backButton = Cast<UW_BackButton>(mBackButton);
		backButton->SetBackText(TEXT("캐릭터 선택창"));
		backButton->SetBackButton(TEXT("L_SelectCharacter"));
	}

}

void UW_SelectClass::Click_Warrior()
{
	SelectClass(TEXT("전사"), ECharacterClass::Warrior);
}

void UW_SelectClass::Click_Wizard()
{
	SelectClass(TEXT("마법사"), ECharacterClass::Wizard);
}

void UW_SelectClass::SelectClass(const FString& inClass, ECharacterClass inCharacterClass)
{
	AClientHUD* clientHUD = Cast<AClientHUD>(GetOwningPlayer()->GetHUD());
	if (nullptr == clientHUD)
	{
		return;
	}

	ANetworkGameMode* networkGameMode = Cast<ANetworkGameMode>(GetWorld()->GetAuthGameMode());
	if (nullptr == networkGameMode)
	{
		return;
	}

	ULDGameInstance* gameInstance = Cast<ULDGameInstance>(GetWorld()->GetGameInstance());
	if (nullptr == gameInstance)
	{
		return;
	}

	if (inClass.IsEmpty())
	{
		return;
	}

	FString classStr = FString::Printf(TEXT("%s로 선택하겠습니까?"), *inClass);

	FConfirmButtonDelegate confirmDelegate;
	confirmDelegate.BindLambda([=]()
		{
			gameInstance->mCharacterData.SetClass(inCharacterClass);

			networkGameMode->RequestTravelLevel(TEXT("L_CustomCharacter"));
		});

	FCancleButtonDelegate cancleDelegate;
	cancleDelegate.BindLambda([=]()
		{
			clientHUD->CleanWidgetFromName(TEXT("Reconfirm"));
		});

	bool error = UWidgetUtils::SetReconfirm(clientHUD, TEXT("클래스 선택"), classStr, TEXT("선택"), TEXT("취소"), confirmDelegate, cancleDelegate);
	if (error == false)
	{
		return;
	}
}
