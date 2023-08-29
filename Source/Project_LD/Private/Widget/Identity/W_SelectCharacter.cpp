// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Identity/W_SelectCharacter.h"
#include <Widget/Identity/W_SelectCharacterButton.h>

#include <Blueprint/WidgetTree.h>
#include <Widget/Common/W_BackButton.h>
#include <Widget/Common/W_Button.h>

#include <CharacterDatas.h>

void UW_SelectCharacter::NativeConstruct()
{
	Super::NativeConstruct();

	mBackButton = this->WidgetTree->FindWidget(FName(TEXT("BW_BackButton")));
	if (mBackButton != nullptr)
	{
		UW_BackButton* backButton = Cast<UW_BackButton>(mBackButton);
		backButton->SetBackText(TEXT("로그인 화면"));
		backButton->SetBackButton(TEXT("L_LoginScreen"));
	}

	mAppearanceButton = this->WidgetTree->FindWidget(FName(TEXT("BW_AppearanceButton")));
	if (mAppearanceButton != nullptr)
	{
		UW_Button* appearanceButton = Cast<UW_Button>(mAppearanceButton);
		appearanceButton->mButtonDelegate.BindUFunction(this, FName(TEXT("OnAppearanceButton")));
	}

	mDeleteButton = this->WidgetTree->FindWidget(FName(TEXT("BW_DeleteCharacterButton")));
	if (mDeleteButton != nullptr)
	{
		UW_Button* deleteButton = Cast<UW_Button>(mDeleteButton);
		deleteButton->mButtonDelegate.BindUFunction(this, FName(TEXT("OnDeleteButton")));
	}

	mReviseNameButton = this->WidgetTree->FindWidget(FName(TEXT("BW_NicknameEditButton")));
	if (mReviseNameButton != nullptr)
	{
		UW_Button* reviseNameButton = Cast<UW_Button>(mReviseNameButton);
		reviseNameButton->mButtonDelegate.BindUFunction(this, FName(TEXT("OnReviseNameButton")));
	}

	mCurrentClickMode = EClickMode::None;
}

void UW_SelectCharacter::CreateCharacter(FCharacterData& inCharacterData)
{
	if (mCharacterButtonWidgets.Num() == 0)
	{
		LoadChild();
	}

	int32 seat = inCharacterData.GetAppearance().GetSeat();
	if (!(0 <= seat && seat < mCharacterButtonWidgets.Num()))
	{
		return;
	}

	UW_SelectCharacterButton* characterButton = Cast<UW_SelectCharacterButton>(mCharacterButtonWidgets[seat]);
	if (characterButton)
	{
		characterButton->SetCharacterInfo(inCharacterData);
	}
}

void UW_SelectCharacter::LoadChild()
{
	mCharacterButtonWidgets.AddUnique(this->WidgetTree->FindWidget(FName(TEXT("BW_SelectCharacterButton_1"))));
	mCharacterButtonWidgets.AddUnique(this->WidgetTree->FindWidget(FName(TEXT("BW_SelectCharacterButton_2"))));
	mCharacterButtonWidgets.AddUnique(this->WidgetTree->FindWidget(FName(TEXT("BW_SelectCharacterButton_3"))));
	mCharacterButtonWidgets.AddUnique(this->WidgetTree->FindWidget(FName(TEXT("BW_SelectCharacterButton_4"))));

	//or
	//TArray<UWidget*> Children;
	//this->WidgetTree->GetAllWidgets(Children);
	//for (auto Child : Children)
	//{
	//	if (UW_SelectCharacterButton* button = Cast<UW_SelectCharacterButton>(Child))
	//	{
	//		mCharacterButtonWidgets.Add(button);
	//	}
	//}
}

void UW_SelectCharacter::OnAppearanceButton()
{
	if (mCharacterButtonWidgets.Num() == 0)
	{
		LoadChild();
	}

	if (mCurrentClickMode == EClickMode::Appearance)
	{
		PreviousAllButtonMode();
		return;
	}

	mCurrentClickMode = EClickMode::Appearance;
	ChangeAllButtonMode(EClickMode::Appearance);
}

void UW_SelectCharacter::OnDeleteButton()
{
	if (mCharacterButtonWidgets.Num() == 0)
	{
		LoadChild();
	}

	if (mCurrentClickMode == EClickMode::Delete)
	{
		PreviousAllButtonMode();
		return;
	}

	mCurrentClickMode = EClickMode::Delete;
	ChangeAllButtonMode(EClickMode::Delete);

}

void UW_SelectCharacter::OnReviseNameButton()
{
	if (mCharacterButtonWidgets.Num() == 0)
	{
		LoadChild();
	}

	if (mCurrentClickMode == EClickMode::ReviseName)
	{
		PreviousAllButtonMode();
		return;
	}

	mCurrentClickMode = EClickMode::ReviseName;
	ChangeAllButtonMode(EClickMode::ReviseName);

}

void UW_SelectCharacter::PreviousAllButtonMode()
{
	for (UWidget* widget : mCharacterButtonWidgets)
	{
		UW_SelectCharacterButton* characterButton = Cast<UW_SelectCharacterButton>(widget);
		if (characterButton)
		{
			characterButton->PreviousClickMode();
		}
	}
	mCurrentClickMode = EClickMode::None;
}

void UW_SelectCharacter::ChangeAllButtonMode(EClickMode inClickMode)
{
	for (UWidget* widget : mCharacterButtonWidgets)
	{
		UW_SelectCharacterButton* characterButton = Cast<UW_SelectCharacterButton>(widget);
		if (characterButton)
		{
			characterButton->SetClickMode(inClickMode);
		}
	}
}
