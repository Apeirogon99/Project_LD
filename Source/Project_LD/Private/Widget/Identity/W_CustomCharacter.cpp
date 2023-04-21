// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Identity/W_CustomCharacter.h"
#include <Components/Button.h>
#include <Components/TextBlock.h>

#include <Blueprint/WidgetTree.h>
#include <Widget/Handler/ClientHUD.h>
#include <Widget/Common/W_ColorPicker.h>
#include <Widget/WidgetUtils.h>

#include <Network/NetworkUtils.h>
#include <Protobuf/Handler/FClientPacketHandler.h>
#include <Protobuf/Handler/FIdentityPacketHandler.h>

#include <Network/NetworkCharacter.h>
#include <Framework/Character/AppearanceCharacter.h>

#include <Kismet/GameplayStatics.h>
#include <Framework/Gameinstance/LDGameInstance.h>

void UW_CustomCharacter::NativeConstruct()
{
	Super::NativeConstruct();

	mClassText		= Cast<UTextBlock>(GetWidgetFromName(TEXT("mClassText")));

	mCreateButton	= Cast<UButton>(GetWidgetFromName(TEXT("mCreateButton")));
	mRaceButton		= Cast<UButton>(GetWidgetFromName(TEXT("mRaceButton")));
	mSkinButton		= Cast<UButton>(GetWidgetFromName(TEXT("mSkinButton")));
	mHairButton		= Cast<UButton>(GetWidgetFromName(TEXT("mHairButton")));
	mEyeButton		= Cast<UButton>(GetWidgetFromName(TEXT("mEyeButton")));
	mEyebrowButton	= Cast<UButton>(GetWidgetFromName(TEXT("mEyebrowButton")));

	if (mCreateButton != nullptr)
	{
		mCreateButton->OnClicked.AddUniqueDynamic(this, &UW_CustomCharacter::Click_Create);
	}

	if (mRaceButton != nullptr)
	{
		mRaceButton->OnClicked.AddUniqueDynamic(this, &UW_CustomCharacter::Click_Tribe);
	}

	if (mSkinButton != nullptr)
	{
		mSkinButton->OnClicked.AddUniqueDynamic(this, &UW_CustomCharacter::Click_Skin);
	}

	if (mHairButton != nullptr)
	{
		mHairButton->OnClicked.AddUniqueDynamic(this, &UW_CustomCharacter::Click_Hair);
	}

	if (mEyeButton != nullptr)
	{
		mEyeButton->OnClicked.AddUniqueDynamic(this, &UW_CustomCharacter::Click_Eye);
	}

	if (mEyebrowButton != nullptr)
	{
		mEyebrowButton->OnClicked.AddUniqueDynamic(this, &UW_CustomCharacter::Click_Eyebrow);
	}

	mBackButton = this->WidgetTree->FindWidget(FName(TEXT("BW_BackButton")));
	if (mBackButton != nullptr)
	{
		UW_BackButton* backButton = Cast<UW_BackButton>(mBackButton);
		backButton->SetBackText(TEXT("클래스 선택창"));
		backButton->SetBackButton(TEXT("L_SelectClass"));
	}

	mTribeSelectWidget = this->WidgetTree->FindWidget(FName(TEXT("BW_Tribe")));
	if (mTribeSelectWidget != nullptr)
	{
		mTribeSelectWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	UWidget* tempColorPicker = this->WidgetTree->FindWidget(FName(TEXT("BW_ColorPicker")));
	if (tempColorPicker != nullptr)
	{
		mColorPicker = Cast<UW_ColorPicker>(tempColorPicker);
		mColorPicker->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UW_CustomCharacter::NativeDestruct()
{
	Super::NativeDestruct();

}

void UW_CustomCharacter::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (true == CanUpdate())
	{
		UpdateDummyCharacterPartColor();
	}
}

void UW_CustomCharacter::Click_Create()
{
	ANetworkController* controller = Cast<ANetworkController>(GetOwningPlayer());
	AClientHUD* clientHUD = Cast<AClientHUD>(controller->GetHUD());
	
	FButtonDelegate editBoxDelegate;
	editBoxDelegate.BindLambda([=](const FString& inName)
		{
			clientHUD->ShowWidgetFromName(TEXT("LoadingServer"));

			Protocol::C2S_CreateCharacter createCharacterPacket;
			std::string name = UNetworkUtils::ConvertString(inName);

			Protocol::SCharacterData* characterData = createCharacterPacket.mutable_character_data();
	
			createCharacterPacket.set_remote_id(1);
			createCharacterPacket.set_server_id(1);

			if (mCurrentDummyCharacter)
			{
				const FCharacterData& dummyCharacterData = mCurrentDummyCharacter->GetCharacterData();

				characterData->set_name(name);
				characterData->set_character_class(static_cast<Protocol::ECharacterClass>(dummyCharacterData.mClass));

				Protocol::SCharacterAppearance* newCharacterAppearance = characterData->mutable_appearance();
				newCharacterAppearance->set_race(static_cast<Protocol::ERace>(dummyCharacterData.mRace));
				newCharacterAppearance->set_seat(dummyCharacterData.mAppearance.mSeat);
				newCharacterAppearance->set_skin_color(dummyCharacterData.mAppearance.mSkin_Color);
				newCharacterAppearance->set_hair_color(dummyCharacterData.mAppearance.mHair_Color);
				newCharacterAppearance->set_eye_color(dummyCharacterData.mAppearance.mEye_Color);
				newCharacterAppearance->set_eyebrow_color(dummyCharacterData.mAppearance.mEyebrow_Color);
			}

			SendBufferPtr pakcetBuffer = FIdentityPacketHandler::MakeSendBuffer(controller, createCharacterPacket);
			controller->Send(pakcetBuffer);

			clientHUD->CleanWidgetFromName(TEXT("EditBox"));
		});

	bool ret = UWidgetUtils::SetEditBox(clientHUD, TEXT("캐릭터 생성"), TEXT("캐릭터 닉네임을 설정하세요"), TEXT("설정"), editBoxDelegate);
	if (ret == false)
	{
		UNetworkUtils::NetworkConsoleLog(TEXT("[UW_CustomCharacter::Click_Create] Error"), ELogLevel::Warning);
		return;
	}
}

void UW_CustomCharacter::Click_Tribe()
{
	if (mTribeSelectWidget->GetVisibility() == ESlateVisibility::Collapsed)
	{
		mTribeSelectWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	else
	{
		mTribeSelectWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UW_CustomCharacter::Click_Skin()
{
	ToggleColorPicker(EAppearance::Body);
}

void UW_CustomCharacter::Click_Hair()
{
	ToggleColorPicker(EAppearance::Hair);
}

void UW_CustomCharacter::Click_Eye()
{
	ToggleColorPicker(EAppearance::Eye);
}

void UW_CustomCharacter::Click_Eyebrow()
{
	ToggleColorPicker(EAppearance::Eyebrow);
}

bool UW_CustomCharacter::CanUpdate()
{
	return (mCurrentDummyCharacter && mColorPicker->GetVisibility() == ESlateVisibility::SelfHitTestInvisible) ? true : false;
}

void UW_CustomCharacter::ToggleColorPicker(EAppearance inDummyAppearance)
{
	if (mCurrentDummyAppearance == inDummyAppearance)
	{
		mColorPicker->SetVisibility(ESlateVisibility::Collapsed);
		mCurrentDummyAppearance = EAppearance::None;
		mCurrentDummyCharacter = nullptr;
	}
	else
	{
		mCurrentDummyAppearance = inDummyAppearance;
		mColorPicker->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

		AActor* newDummyCharacter = nullptr;
		newDummyCharacter = UGameplayStatics::GetActorOfClass(GetWorld(), AAppearanceCharacter::StaticClass());
		mCurrentDummyCharacter = Cast<AAppearanceCharacter>(newDummyCharacter);
		
		FString colorPickerTarget;
		switch (inDummyAppearance)
		{
		case EAppearance::None:
			colorPickerTarget = TEXT("NONE");
			break;
		case EAppearance::Body:
			colorPickerTarget = TEXT("몸");
			mTempCharacterAppearance.mSkin_Color = UNetworkUtils::ConverLinerColorToInt(mCurrentDummyCharacter->GetMeshColor(EAppearance::Body));
			break;
		case EAppearance::Hair:
			colorPickerTarget = TEXT("머리카락");
			mTempCharacterAppearance.mHair_Color = UNetworkUtils::ConverLinerColorToInt(mCurrentDummyCharacter->GetMeshColor(EAppearance::Hair));
			break;
		case EAppearance::Eye:
			colorPickerTarget = TEXT("눈");
			mTempCharacterAppearance.mEye_Color = UNetworkUtils::ConverLinerColorToInt(mCurrentDummyCharacter->GetMeshColor(EAppearance::Eye));
			break;
		case EAppearance::Eyebrow:
			colorPickerTarget = TEXT("눈썹");
			mTempCharacterAppearance.mEyebrow_Color = UNetworkUtils::ConverLinerColorToInt(mCurrentDummyCharacter->GetMeshColor(EAppearance::Eye));
			break;
		default:
			colorPickerTarget = TEXT("ERROR");
			break;
		}

		if (mColorPicker)
		{
			mColorPicker->SetPickerTarget(colorPickerTarget);
			mColorPicker->OnUsed(mCurrentDummyCharacter->GetMeshColor(inDummyAppearance));
		}
	}
}

void UW_CustomCharacter::UpdateDummyCharacterPartColor()
{

	if (mColorPicker && mCurrentDummyCharacter)
	{
		int32 color = UNetworkUtils::ConverLinerColorToInt(mColorPicker->GetLinearColor());

		switch (mCurrentDummyAppearance)
		{
		case EAppearance::None:
			break;
		case EAppearance::Body:
			mTempCharacterAppearance.mSkin_Color = color;
			break;
		case EAppearance::Eye:
			mTempCharacterAppearance.mEye_Color = color;
			break;
		case EAppearance::Eyebrow:
			mTempCharacterAppearance.mEyebrow_Color = color;
			break;
		case EAppearance::Hair:
			mTempCharacterAppearance.mHair_Color = color;
			break;
		default:
			break;
		}
		
		mCurrentDummyCharacter->UpdateCharacterAppearnce(mTempCharacterAppearance);
	}
}

void UW_CustomCharacter::SetClassText(const ECharacterClass inClass)
{
	FString classStr;
	switch (inClass)
	{
	case ECharacterClass::None:
		classStr = TEXT("None");
		break;
	case ECharacterClass::Warrior:
		classStr = TEXT("전사");
		break;
	case ECharacterClass::Wizard:
		classStr = TEXT("마법사");
		break;
	default:
		classStr = TEXT("None");
		break;
	}

	FText text = FText::FromString(classStr);
	mClassText->SetText(text);
	
}
