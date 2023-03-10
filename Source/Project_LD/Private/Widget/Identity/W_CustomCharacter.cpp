// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Identity/W_CustomCharacter.h"
#include <Components/Button.h>
#include <Components/TextBlock.h>

#include <Blueprint/WidgetTree.h>
#include <Widget/Handler/ClientHUD.h>
#include <Widget/Common/W_ColorPicker.h>
#include <Widget/Common/W_BackButton.h>
#include <Widget/Common/W_EditBox.h>

#include <Network/NetworkUtils.h>
#include <Protobuf/Handler/FClientPacketHandler.h>
#include <Protobuf/Handler/FIdentityPacketHandler.h>

#include <Network/NetworkCharacter.h>
#include <Kismet/GameplayStatics.h>
#include <Framework/Gameinstance/LDGameInstance.h>

void UW_CustomCharacter::NativeConstruct()
{
	Super::NativeConstruct();

	mClassText		= Cast<UTextBlock>(GetWidgetFromName(TEXT("mClassText")));

	mCreateButton	= Cast<UButton>(GetWidgetFromName(TEXT("mCreateButton")));
	mTribeButton	= Cast<UButton>(GetWidgetFromName(TEXT("mTribeButton")));
	mSkinButton		= Cast<UButton>(GetWidgetFromName(TEXT("mSkinButton")));
	mHairButton		= Cast<UButton>(GetWidgetFromName(TEXT("mHairButton")));
	mEyeButton		= Cast<UButton>(GetWidgetFromName(TEXT("mEyeButton")));
	mEyebrowButton	= Cast<UButton>(GetWidgetFromName(TEXT("mEyebrowButton")));

	if (mCreateButton != nullptr)
	{
		mCreateButton->OnClicked.AddDynamic(this, &UW_CustomCharacter::Click_Create);
	}

	if (mTribeButton != nullptr)
	{
		mTribeButton->OnClicked.AddDynamic(this, &UW_CustomCharacter::Click_Tribe);
	}

	if (mSkinButton != nullptr)
	{
		mSkinButton->OnClicked.AddDynamic(this, &UW_CustomCharacter::Click_Skin);
	}

	if (mHairButton != nullptr)
	{
		mHairButton->OnClicked.AddDynamic(this, &UW_CustomCharacter::Click_Hair);
	}

	if (mEyeButton != nullptr)
	{
		mEyeButton->OnClicked.AddDynamic(this, &UW_CustomCharacter::Click_Eye);
	}

	if (mEyebrowButton != nullptr)
	{
		mEyebrowButton->OnClicked.AddDynamic(this, &UW_CustomCharacter::Click_Eyebrow);
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

	UW_EditBox* editBox = Cast<UW_EditBox>(clientHUD->GetWidgetFromName(TEXT("EditBox")));
	editBox->SetEditTitleText(TEXT("캐릭터 생성"));
	editBox->SetEditHint(TEXT("캐릭터 닉네임을 설정하세요"));
	editBox->SetConfrimButtonText(TEXT("설정"));

	editBox->mConfirmDelegate.BindLambda([=](const FString& inNickName)
		{
			clientHUD->AllCollapsedButOneWidget(TEXT("LoadingServer"));

			Protocol::C2S_CreateCharacter createCharacterPacket;
			std::string nicknameStr = UNetworkUtils::ConvertString(inNickName);

			Protocol::SCharacterData* createData = createCharacterPacket.mutable_data();
			Protocol::SCharacterAppearance* createAppearance = createCharacterPacket.mutable_appearance();
			if (mCurrentDummyCharacter)
			{
				FCharacterDatas characterDatas = mCurrentDummyCharacter->mCharacterData;
				createData->set_name(nicknameStr);
				createData->set_job(characterDatas.mClass);
				createData->set_tribe(characterDatas.mTribe);
				createData->set_position(characterDatas.mPosition);

				FCharacterAppearance characterAppearance = mCurrentDummyCharacter->mCharacterAppearance;
				createAppearance->set_body_color(characterAppearance.mBodyColor);
				createAppearance->set_hair_color(characterAppearance.mHairColor);
				createAppearance->set_eye_color(characterAppearance.mEyeColor);

				createAppearance->set_head(characterAppearance.mMeshs[0]);
				createAppearance->set_ears(characterAppearance.mMeshs[1]);
				createAppearance->set_feet(characterAppearance.mMeshs[2]);
				createAppearance->set_hair(characterAppearance.mMeshs[3]);
				createAppearance->set_facials_02(characterAppearance.mMeshs[5]);
				createAppearance->set_legs(characterAppearance.mMeshs[9]);
				createAppearance->set_hands(characterAppearance.mMeshs[11]);
				createAppearance->set_chest(characterAppearance.mMeshs[13]);
				createAppearance->set_bracers(characterAppearance.mMeshs[16]);
				createAppearance->set_boots(characterAppearance.mMeshs[18]);

			}

			SendBufferPtr pakcetBuffer = FIdentityPacketHandler::MakeSendBuffer(controller, createCharacterPacket);
			controller->Send(pakcetBuffer);
		});

	clientHUD->ShowWidgetFromName(TEXT("EditBox"));
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
	ToggleColorPicker(EPart::Head);
}

void UW_CustomCharacter::Click_Hair()
{
	ToggleColorPicker(EPart::Hair);
}

void UW_CustomCharacter::Click_Eye()
{
	ToggleColorPicker(EPart::Eye);
}

void UW_CustomCharacter::Click_Eyebrow()
{
	ToggleColorPicker(EPart::Eyebrow);
}

bool UW_CustomCharacter::CanUpdate()
{
	return (mCurrentDummyCharacter && mColorPicker->GetVisibility() == ESlateVisibility::SelfHitTestInvisible) ? true : false;
	
}

void UW_CustomCharacter::ToggleColorPicker(EPart inDummyPart)
{
	if (mCurrentDummyPart == inDummyPart)
	{
		mColorPicker->SetVisibility(ESlateVisibility::Collapsed);
		mCurrentDummyPart = EPart::None;
		mCurrentDummyCharacter = nullptr;
	}
	else
	{
		mCurrentDummyPart = inDummyPart;
		mColorPicker->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		
		FString colorPickerTarget;
		switch (inDummyPart)
		{
		case EPart::None:
			colorPickerTarget = "NONE";
			break;
		case EPart::Head:
			colorPickerTarget = TEXT("몸");
			break;
		case EPart::Hair:
			colorPickerTarget = TEXT("머리카락");
			break;
		case EPart::Eye:
			colorPickerTarget = TEXT("눈");
			break;
		case EPart::Eyebrow:
			colorPickerTarget = TEXT("눈썹");
			break;
		default:
			break;
		}

		AActor* newDummyCharacter = nullptr;
		newDummyCharacter = UGameplayStatics::GetActorOfClass(GetWorld(), ANetworkCharacter::StaticClass());
		mCurrentDummyCharacter = Cast<ANetworkCharacter>(newDummyCharacter);

		mTempCharacterAppearance.mBodyColor = UNetworkUtils::ConverLinerColorToInt(mCurrentDummyCharacter->GetPartColor(EPart::Head));
		//mTempCharacterAppearance.mHairColor = UNetworkUtils::ConverLinerColorToInt(mCurrentDummyCharacter->GetPartColor(EPart::Hair));
		mTempCharacterAppearance.mEyeColor = UNetworkUtils::ConverLinerColorToInt(mCurrentDummyCharacter->GetPartColor(EPart::Eye));

		if (mColorPicker)
		{
			mColorPicker->SetPickerTarget(colorPickerTarget);
			mColorPicker->OnUsed(mCurrentDummyCharacter->GetPartColor(inDummyPart));
		}
	}
}

void UW_CustomCharacter::UpdateDummyCharacterPartColor()
{

	if (mColorPicker && mCurrentDummyCharacter)
	{
		int32 color = UNetworkUtils::ConverLinerColorToInt(mColorPicker->GetLinearColor());

		switch (mCurrentDummyPart)
		{
		case EPart::None:
			break;
		case EPart::Boots:
		case EPart::Bracers:
		case EPart::Chest:
		case EPart::Feet:
		case EPart::Hands:
		case EPart::Head:
		case EPart::Pants:
		case EPart::Ears:
			mTempCharacterAppearance.mBodyColor = color;
			break;
		case EPart::Eye:
			mTempCharacterAppearance.mEyeColor = color;
			break;
		case EPart::Eyebrow:
			mTempCharacterAppearance.mEyeColor = color;
			break;
		case EPart::Hair:
			mTempCharacterAppearance.mHairColor = color;
			break;
		default:
			break;
		}
		
		mCurrentDummyCharacter->UpdateCharacterVisual(mTempCharacterAppearance);
	}
}

void UW_CustomCharacter::SetClassText(const int32 inClass)
{

	FString classStr;
	EClass gameClass = static_cast<EClass>(inClass);
	switch (gameClass)
	{
	case EClass::None:
		classStr = TEXT("None");
		break;
	case EClass::Warrior:
		classStr = TEXT("전사");
		break;
	case EClass::Wizard:
		classStr = TEXT("마법사");
		break;
	default:
		classStr = TEXT("None");
		break;
	}

	FText text = FText::FromString(classStr);
	mClassText->SetText(text);
	
}
