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

#include <Identity/C_Dummy.h>
#include <Kismet/GameplayStatics.h>
#include <Framework/Gameinstance/LDGameInstance.h>
#include <Struct/Game/CharacterDatas.h>

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

	if (mClassText != nullptr)
	{
		SetClassText();
	}

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

			Protocol::SCharacterData* createCharacter = createCharacterPacket.mutable_character();
			if (mCurrentDummyCharacter)
			{
				createCharacter->set_name(nicknameStr);
				createCharacter->set_job(static_cast<int32>(mCurrentDummyCharacter->GetClass()));
				createCharacter->set_tribe(static_cast<int32>(mCurrentDummyCharacter->GetTribe()));

				createCharacter->set_skin(mCurrentDummyCharacter->GetPartColorToInt((EPart::Body), 0));
				createCharacter->set_hair(mCurrentDummyCharacter->GetPartColorToInt((EPart::Hair), 0));
				createCharacter->set_eye(mCurrentDummyCharacter->GetPartColorToInt((EPart::Eye), 0));
				createCharacter->set_eyebrow(mCurrentDummyCharacter->GetPartColorToInt((EPart::Eyebrow), 0));
			}

			ULDGameInstance* gameinstance = Cast<ULDGameInstance>(GetWorld()->GetGameInstance());
			if (gameinstance)
			{
				int32 positon = gameinstance->mCharacterDatas.mPosition;
				createCharacter->set_position(positon);
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
	ToggleColorPicker(EPart::Body);

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
		case EPart::Body:
			colorPickerTarget = TEXT("피부");
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

		AActor* dummy = nullptr;
		dummy = UGameplayStatics::GetActorOfClass(GetWorld(), AC_Dummy::StaticClass());
		mCurrentDummyCharacter = Cast<AC_Dummy>(dummy);

		if (mColorPicker)
		{
			mColorPicker->SetPickerTarget(colorPickerTarget);
			mColorPicker->OnUsed(mCurrentDummyCharacter->GetPartColor(mCurrentDummyPart, 0));
		}
	}
}

void UW_CustomCharacter::UpdateDummyCharacterPartColor()
{
	if (mColorPicker && mCurrentDummyCharacter)
	{
		FLinearColor color = mColorPicker->GetLinearColor();
		mCurrentDummyCharacter->SetPartColor(mCurrentDummyPart, color, 0);
	}
}

void UW_CustomCharacter::SetClassText()
{
	ULDGameInstance* gameInstance = Cast<ULDGameInstance>(GetWorld()->GetGameInstance());
	if (gameInstance)
	{
		FString classStr;
		EClass gameClass = static_cast<EClass>(gameInstance->mCharacterDatas.mClass);
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
}
