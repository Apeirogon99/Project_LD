// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Identity/W_SelectServer.h"
#include <Components/ListView.h>

#include <Widget/Identity/W_SelectServerButton.h>
#include <Struct/Identity/ServerData.h>

void UW_SelectServer::NativeConstruct()
{
	Super::NativeConstruct();

	mServerList = Cast<UListView>(GetWidgetFromName(TEXT("mServerList")));

	mIsBackGround = true;

	TSubclassOf<UW_SelectServerButton> buttonClass = StaticLoadClass(UW_SelectServerButton::StaticClass(), NULL, TEXT("WidgetBlueprint'/Game/Blueprint/Widget/Identity/BW_SelectServerButton.BW_SelectServerButton_C'"));
	if (buttonClass)
	{
		mButtonWidget = buttonClass;
	}
}

void UW_SelectServer::CreateServerInfoWidget(const int32 inServerID, const FString& inName, const float inState, const int32 inCharacterCount)
{

	//UServerData* newServerData = NewObject<UServerData>();
	//newServerData->SetServerID(inServerID);
	//newServerData->SetServerName(inName);
	//newServerData->SetServerState(inState);
	//newServerData->SetCharacterCount(inCharacterCount);

	UW_SelectServerButton* newSelectServerButton = Cast<UW_SelectServerButton>(CreateWidget(GetWorld(), mButtonWidget));
	if (nullptr == newSelectServerButton)
	{
		return;
	}

	newSelectServerButton->Init(inServerID, inName, inState, inCharacterCount, mIsBackGround);
	mServerList->AddItem(newSelectServerButton);
	mIsBackGround = !mIsBackGround;
}
