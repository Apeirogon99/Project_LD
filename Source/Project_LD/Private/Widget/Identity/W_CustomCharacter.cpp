﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Identity/W_CustomCharacter.h"
#include <Widget/Common/W_EditBox.h>
#include <Protobuf/Handler/FIdentityPacketHandler.h>

void UW_CustomCharacter::NativeConstruct()
{
	Super::NativeConstruct();

	if (mEditBoxClass)
	{
		mEditNickNameBox = CreateWidget<UUserWidget>(GetWorld(), mEditBoxClass);
		UW_EditBox* editBox = Cast<UW_EditBox>(mEditNickNameBox);
		editBox->SetEditTitleText(TEXT("캐릭터 이름"));
		editBox->SetEditHint(TEXT("이름"));
		editBox->SetConfrimButtonText(TEXT("확인"));
		editBox->mConfirmDelegate.BindUFunction(this, FName("SendNickName"));
		editBox->AddToPlayerScreen();
	}
}

void UW_CustomCharacter::NativeDestruct()
{
	mEditNickNameBox->RemoveFromParent();
}

void UW_CustomCharacter::SendNickName(const FString& inNickName)
{
	UE_LOG(LogTemp, Warning, TEXT("SendNickName"));
}

void UW_CustomCharacter::ResultNickName(const bool inResult)
{

}
