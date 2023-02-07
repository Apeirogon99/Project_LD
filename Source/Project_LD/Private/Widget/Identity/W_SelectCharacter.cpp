// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Identity/W_SelectCharacter.h"
#include <Widget/Identity/W_SelectCharacterButton.h>
#include <Blueprint/WidgetTree.h>

void UW_SelectCharacter::NativeConstruct()
{
	Super::NativeConstruct();

}

void UW_SelectCharacter::LoadCharacterInfo(int32 inNumber, const FString& inLevel, const FString& inName)
{
	if (mCharacterButtonWidgets.Num() == 0)
	{
		LoadChild();
	}

	if (!(0 <= inNumber && inNumber < mCharacterButtonWidgets.Num()))
	{
		return;
	}

	UW_SelectCharacterButton* characterButton = Cast<UW_SelectCharacterButton>(mCharacterButtonWidgets[inNumber]);
	if (characterButton)
	{
		characterButton->SetCharacterInfo(inLevel, inName);
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
