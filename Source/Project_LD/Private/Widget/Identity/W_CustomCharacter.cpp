// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Identity/W_CustomCharacter.h"
#include <Components/Button.h>
#include <Components/TextBlock.h>
#include <Components/Image.h>

#include <Blueprint/WidgetTree.h>
#include <Widget/Handler/ClientHUD.h>
#include <Widget/Common/W_ColorPicker.h>
#include <Widget/WidgetUtils.h>

#include <Network/NetworkUtils.h>
#include <Protobuf/Handler/FClientPacketHandler.h>
#include <Protobuf/Handler/FIdentityPacketHandler.h>

#include <Network/NetworkCharacter.h>
#include <Framework/Character/AppearanceCharacter.h>
#include <Framework/Identity/GM_CustomCharacter.h>

#include <Kismet/GameplayStatics.h>
#include <Framework/Gameinstance/LDGameInstance.h>

void UW_CustomCharacter::NativeConstruct()
{
	Super::NativeConstruct();

	mClassText				= Cast<UTextBlock>(GetWidgetFromName(TEXT("mClassText")));

	mCreateButton			= Cast<UButton>(GetWidgetFromName(TEXT("mCreateButton")));
	mMaleButton				= Cast<UButton>(GetWidgetFromName(TEXT("mMaleButton")));
	mFemaleButton			= Cast<UButton>(GetWidgetFromName(TEXT("mFemaleButton")));
	mSkinColorButton		= Cast<UButton>(GetWidgetFromName(TEXT("mSkinColorButton")));
	mHairColorButton		= Cast<UButton>(GetWidgetFromName(TEXT("mHairColorButton")));
	mEyeColorButton			= Cast<UButton>(GetWidgetFromName(TEXT("mEyeColorButton")));
	mEyebrowColorButton		= Cast<UButton>(GetWidgetFromName(TEXT("mEyebrowColorButton")));

	mSkinColor				= Cast<UImage>(GetWidgetFromName(TEXT("mSkinColor")));
	mHairColor				= Cast<UImage>(GetWidgetFromName(TEXT("mHairColor")));
	mEyeColor				= Cast<UImage>(GetWidgetFromName(TEXT("mEyeColor")));
	mEyebrowColor			= Cast<UImage>(GetWidgetFromName(TEXT("mEyebrowColor")));

	if (mCreateButton != nullptr)
	{
		mCreateButton->OnClicked.AddUniqueDynamic(this, &UW_CustomCharacter::Click_Create);
	}

	if (mMaleButton != nullptr)
	{
		mMaleButton->OnClicked.AddUniqueDynamic(this, &UW_CustomCharacter::Click_MaleRace);
	}

	if (mFemaleButton != nullptr)
	{
		mFemaleButton->OnClicked.AddUniqueDynamic(this, &UW_CustomCharacter::Click_FemaleRace);
	}

	if (mSkinColorButton != nullptr)
	{
		mSkinColorButton->OnClicked.AddUniqueDynamic(this, &UW_CustomCharacter::Click_Skin);
	}

	if (mHairColorButton != nullptr)
	{
		mHairColorButton->OnClicked.AddUniqueDynamic(this, &UW_CustomCharacter::Click_Hair);
	}

	if (mEyeColorButton != nullptr)
	{
		mEyeColorButton->OnClicked.AddUniqueDynamic(this, &UW_CustomCharacter::Click_Eye);
	}

	if (mEyebrowColorButton != nullptr)
	{
		mEyebrowColorButton->OnClicked.AddUniqueDynamic(this, &UW_CustomCharacter::Click_Eyebrow);
	}
	
	mBackButton = this->WidgetTree->FindWidget(FName(TEXT("BW_BackButton")));
	if (mBackButton != nullptr)
	{
		UW_BackButton* backButton = Cast<UW_BackButton>(mBackButton);
		backButton->SetBackText(TEXT("클래스 선택창"));
		backButton->SetBackButton(TEXT("L_SelectClass"));
	}

	UWidget* tempColorPicker = this->WidgetTree->FindWidget(FName(TEXT("BW_ColorPicker")));
	if (tempColorPicker != nullptr)
	{
		mColorPicker = Cast<UW_ColorPicker>(tempColorPicker);
		mColorPicker->SetVisibility(ESlateVisibility::Collapsed);
	}

	IsSetupCharacter = false;
}

void UW_CustomCharacter::NativeDestruct()
{
	Super::NativeDestruct();

}

void UW_CustomCharacter::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (CanUpdate())
	{
		UpdateDummyCharacterPartColor();
		UpdateColorPicker();
		UpdateEquipment();
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
			FString fName = UNetworkUtils::ConvertFString(name);

			Protocol::SCharacterData* characterData = createCharacterPacket.mutable_character_data();
			if (mCurrentDummyCharacter)
			{
				const FCharacterAppearance& appearance = mCurrentDummyCharacter->GetCharacterAppearance();
				const FCharacterEquipment& eqipment = mCurrentDummyCharacter->GetCharacterEquipment();

				characterData->set_name(name);
				characterData->set_character_class(static_cast<Protocol::ECharacterClass>(StaticCast<int32>(mCharacterClass)));
				characterData->mutable_appearance()->CopyFrom(UPacketUtils::ConvertToPAppearance(appearance));
				characterData->mutable_eqipment()->CopyFrom(UPacketUtils::ConvertToPEqipment(eqipment));
	
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

void UW_CustomCharacter::Click_MaleRace()
{
	AGM_CustomCharacter* gameMode = Cast<AGM_CustomCharacter>(GetWorld()->GetAuthGameMode());
	gameMode->CreateNewDummyCharacter(ECharacterRace::Male);

}

void UW_CustomCharacter::Click_FemaleRace()
{
	AGM_CustomCharacter* gameMode = Cast<AGM_CustomCharacter>(GetWorld()->GetAuthGameMode());
	gameMode->CreateNewDummyCharacter(ECharacterRace::Female);

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
	return (((mCurrentDummyCharacter != nullptr) && IsSetupCharacter) ? true : false);
}

void UW_CustomCharacter::ToggleColorPicker(EAppearance inDummyAppearance)
{
	if (mCurrentDummyAppearance == inDummyAppearance)
	{
		mColorPicker->SetVisibility(ESlateVisibility::Collapsed);
		mCurrentDummyAppearance = EAppearance::None;
	}
	else
	{
		mCurrentDummyAppearance = inDummyAppearance;
		
		FString colorPickerTarget;
		switch (inDummyAppearance)
		{
		case EAppearance::None:
			colorPickerTarget = TEXT("NONE");
			break;
		case EAppearance::Body:
			colorPickerTarget = TEXT("몸");
			break;
		case EAppearance::Hair:
			colorPickerTarget = TEXT("머리카락");
			break;
		case EAppearance::Eye:
			colorPickerTarget = TEXT("눈");
			break;
		case EAppearance::Eyebrow:
			colorPickerTarget = TEXT("눈썹");
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

		mColorPicker->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
}

void UW_CustomCharacter::UpdateDummyCharacterPartColor()
{
	FLinearColor skin = mCurrentDummyCharacter->GetMeshColor(EAppearance::Body);
	FLinearColor hair = mCurrentDummyCharacter->GetMeshColor(EAppearance::Hair);
	FLinearColor eye = mCurrentDummyCharacter->GetMeshColor(EAppearance::Eye);
	FLinearColor eyebrow = mCurrentDummyCharacter->GetMeshColor(EAppearance::Eyebrow);

	mSkinColor->SetColorAndOpacity(skin);
	mHairColor->SetColorAndOpacity(hair);
	mEyeColor->SetColorAndOpacity(eye);
	mEyebrowColor->SetColorAndOpacity(eyebrow);
}

void UW_CustomCharacter::UpdateColorPicker()
{
	if (mColorPicker->GetVisibility() == ESlateVisibility::SelfHitTestInvisible)
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

void UW_CustomCharacter::UpdateEquipment()
{
	mTempCharacterEquipment.mHair = mHairNumber;
	if (mOldHairNumber != mHairNumber)
	{
		mCurrentDummyCharacter->UpdateCharacterEquipment(mTempCharacterEquipment);
		mCurrentDummyCharacter->UpdateCharacterPose(ECharacterPose::Idle);
		mOldHairNumber = mHairNumber;
	}
}

void UW_CustomCharacter::SetDummyCharacter(AAppearanceCharacter* inDummyCharacter)
{
	IsSetupCharacter = false;

	mCurrentDummyCharacter = inDummyCharacter;
	mTempCharacterAppearance = mCurrentDummyCharacter->GetCharacterAppearance();

	FLinearColor skin		= mCurrentDummyCharacter->GetMeshColor(EAppearance::Body);
	FLinearColor hair		= mCurrentDummyCharacter->GetMeshColor(EAppearance::Hair);
	FLinearColor eye		= mCurrentDummyCharacter->GetMeshColor(EAppearance::Eye);
	FLinearColor eyebrow	= mCurrentDummyCharacter->GetMeshColor(EAppearance::Eyebrow);

	mTempCharacterAppearance.mSkin_Color = UNetworkUtils::ConverLinerColorToInt(skin);
	mTempCharacterAppearance.mHair_Color = UNetworkUtils::ConverLinerColorToInt(hair);
	mTempCharacterAppearance.mEye_Color = UNetworkUtils::ConverLinerColorToInt(eye);
	mTempCharacterAppearance.mEyebrow_Color = UNetworkUtils::ConverLinerColorToInt(eyebrow);

	mOldHairNumber = mHairNumber;
	mTempCharacterEquipment.mHair = mHairNumber;

	mColorPicker->SetVisibility(ESlateVisibility::Collapsed);
	mCurrentDummyAppearance = EAppearance::None;

	mCurrentDummyCharacter->UpdateCharacterAppearnce(mTempCharacterAppearance);
	mCurrentDummyCharacter->UpdateCharacterEquipment(mTempCharacterEquipment);
	//mCurrentDummyCharacter->UpdateDefaultAnimation();

	UpdateDummyCharacterPartColor();


	UWidget* box = this->WidgetTree->FindWidget(FName(TEXT("EyebrowBox")));
	if (box != nullptr)
	{
		const FCharacterAppearance& appearance = mCurrentDummyCharacter->GetCharacterAppearance();
		mCurrentDummyRace = appearance.mRace;
		if (mCurrentDummyRace == ECharacterRace::Female)
		{
			box->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		}
		else
		{
			box->SetVisibility(ESlateVisibility::Collapsed);
		}
	}

	IsSetupCharacter = true;

}

void UW_CustomCharacter::SetClassText(const ECharacterClass inClass)
{
	mCharacterClass = inClass;

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
