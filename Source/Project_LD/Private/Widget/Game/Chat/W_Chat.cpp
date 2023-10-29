// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Game/Chat/W_Chat.h"
#include "Widget/Game/Chat/W_ChatBox.h"

#include <Components/Button.h>
#include <Components/EditableTextBox.h>
#include <Components/ScrollBox.h>

#include <NetworkController.h>
#include <FGamePacketHandler.h>
#include <NetworkUtils.h>
#include <Blueprint/WidgetLayoutLibrary.h>

void UW_Chat::NativeConstruct()
{
	Super::NativeConstruct();

	mEditMessage		= Cast<UEditableTextBox>(GetWidgetFromName(TEXT("mEditMessage")));

	mSendButton			= Cast<UButton>(GetWidgetFromName(TEXT("mSendButton")));
	mWorldTab			= Cast<UButton>(GetWidgetFromName(TEXT("mWorldTab")));
	mPartyTab			= Cast<UButton>(GetWidgetFromName(TEXT("mPartyTab")));
	mFriendTab			= Cast<UButton>(GetWidgetFromName(TEXT("mFriendTab")));
	mDragButton			= Cast<UButton>(GetWidgetFromName(TEXT("mDragButton")));

	mMessageScrollBox	= Cast<UScrollBox>(GetWidgetFromName(TEXT("mMessageScrollBox")));

	if (mEditMessage != nullptr)
	{
		mEditMessage->OnTextCommitted.AddUniqueDynamic(this, &UW_Chat::Committed_Message);
		mEditMessage->OnTextChanged.AddUniqueDynamic(this, &UW_Chat::Chanage_Message);
	}

	if (mSendButton != nullptr)
	{
		mSendButton->OnClicked.AddUniqueDynamic(this, &UW_Chat::Click_SendButton);
	}

	if (mWorldTab != nullptr)
	{
		mWorldTab->OnClicked.AddUniqueDynamic(this, &UW_Chat::Click_WorldTab);
	}

	if (mPartyTab != nullptr)
	{
		mPartyTab->OnClicked.AddUniqueDynamic(this, &UW_Chat::Click_PartyTab);
	}

	if (mFriendTab != nullptr)
	{
		mFriendTab->OnClicked.AddUniqueDynamic(this, &UW_Chat::Click_FriendTab);
	}

	if (mDragButton != nullptr)
	{
		mDragButton->OnPressed.AddUniqueDynamic(this, &UW_Chat::Pressed_Drag);
		mDragButton->OnReleased.AddUniqueDynamic(this, &UW_Chat::Released_Drag);
	}

	mChangeMessage	= FText::GetEmpty();
	mChatType		= EChat::Chat_World;
}

void UW_Chat::NativeDestruct()
{
	Super::NativeDestruct();

	for (UUserWidget* widget : mMessageLogs)
	{
		widget->RemoveFromParent();
	}
}

void UW_Chat::Committed_Message(const FText& inEditValue, ETextCommit::Type inCommitType)
{

	if (ETextCommit::OnEnter == inCommitType)
	{
		if (inEditValue.IsEmpty())
		{
			return;
		}

		this->SendMessage(inEditValue.ToString());

		mEditMessage->SetText(FText::GetEmpty());
		mChangeMessage = FText::GetEmpty();

		this->FocusChat();
	}
}

void UW_Chat::Chanage_Message(const FText& inEditValue)
{
	mChangeMessage = inEditValue;
}

void UW_Chat::Click_SendButton()
{

	if (mChangeMessage.IsEmpty())
	{
		return;
	}

	this->SendMessage(mChangeMessage.ToString());

	mEditMessage->SetText(FText::GetEmpty());
	mChangeMessage = FText::GetEmpty();

	this->FocusChat();
}

void UW_Chat::Click_WorldTab()
{
	mChatType = EChat::Chat_World;
	RefreshMessageLog();
}

void UW_Chat::Click_PartyTab()
{
	mChatType = EChat::Chat_Party;
	RefreshMessageLog();
}

void UW_Chat::Pressed_Drag()
{
	//FVector2D currentMousePoint = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
	//FVector2D currentViewportPoint = RenderTransform.Translation;
	//mPressedMousePoint = currentMousePoint - currentViewportPoint;
	//UpdateLocation();
}

void UW_Chat::Released_Drag()
{
	//if (true == GetWorld()->GetTimerManager().IsTimerActive(mUpdateLocationTimerHandle))
	//{
	//	GetWorld()->GetTimerManager().ClearTimer(mUpdateLocationTimerHandle);
	//}
}

void UW_Chat::Click_FriendTab()
{
	mChatType = EChat::Chat_Friend;
	RefreshMessageLog();
}

void UW_Chat::AddMessage(const FString& inPlayerID, const FString& inMessage, const EChat& inChatType)
{
	UW_ChatBox* newMessage = Cast<UW_ChatBox>(CreateWidget(GetWorld(), mChatBoxWidgetClass));
	if (nullptr == newMessage)
	{
		return;
	}
	newMessage->SetChatBox(inPlayerID, inMessage, inChatType);

	mMessageLogs.Add(newMessage);

	if (mMessageLogs.Num() > 200)
	{

	}

	RefreshMessageLog();
}

void UW_Chat::RefreshMessageLog()
{
	for (int32 ChildIndex = mMessageScrollBox->GetChildrenCount() - 1; ChildIndex >= 0; ChildIndex--)
	{
		mMessageScrollBox->RemoveChildAt(ChildIndex);
	}

	for (UUserWidget* widget : mMessageLogs)
	{
		UW_ChatBox* chatBox = Cast<UW_ChatBox>(widget);
		const EChat& chatType = chatBox->GetChatType();

		if (chatType == mChatType || mChatType == EChat::Chat_World)
		{
			mMessageScrollBox->AddChild(widget);
		}
	}

	mMessageScrollBox->ScrollToEnd();
}

void UW_Chat::UpdateLocation()
{
	//float WaitTime = 0.01f;
	//GetWorld()->GetTimerManager().SetTimer(mUpdateLocationTimerHandle, FTimerDelegate::CreateLambda([&]()
	//	{
	//		FVector2D currentMousePoint = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());

	//		FWidgetTransform widgetTransform;
	//		widgetTransform.Translation = currentMousePoint - mPressedMousePoint;
	//		widgetTransform.Scale = FVector2D(1, 1);
	//		widgetTransform.Shear = FVector2D(0, 0);
	//		widgetTransform.Angle = 0.0f;
	//		SetRenderTransform(widgetTransform);

	//	}), WaitTime, true);
}

void UW_Chat::FocusChat()
{
	APlayerController* owningController = GetOwningPlayer();
	if (nullptr == owningController)
	{
		return;

	}

	FInputModeGameAndUI inputMode;
	inputMode.SetWidgetToFocus(mEditMessage->GetCachedWidget());

	owningController->SetInputMode(inputMode);
	
	mEditMessage->SetKeyboardFocus();
}

bool UW_Chat::SendMessage(const FString& inMessage)
{
	APlayerController* owningController = GetOwningPlayer();
	ANetworkController* networkController = Cast<ANetworkController>(owningController);
	if (nullptr == networkController)
	{
		return false;
	}
	std::string message = UNetworkUtils::ConvertString(mChangeMessage.ToString());
	const int64 timeStamp = networkController->GetServerTimeStamp();

	if (mChatType == EChat::Chat_World)
	{
		Protocol::C2S_Chat chatPacket;
		chatPacket.set_message(message);
		chatPacket.set_timestamp(timeStamp);

		SendBufferPtr sendBuffer = FGamePacketHandler::MakeSendBuffer(nullptr, chatPacket);
		networkController->Send(sendBuffer);
	}
	else if (mChatType == EChat::Chat_Party)
	{

	}
	else if (mChatType == EChat::Chat_Friend)
	{

	}
	else
	{
		return false;
	}

	return true;
}
