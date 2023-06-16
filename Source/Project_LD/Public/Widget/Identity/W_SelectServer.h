// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_SelectServer.generated.h"

class UListView;
/**
 * 
 */
UCLASS()
class PROJECT_LD_API UW_SelectServer : public UUserWidget
{
	GENERATED_BODY()
	
public:
	//virtual void NativeOnInitialized() override;
	//virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	//virtual void NativeDestruct() override;
	//virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:
	UPROPERTY(Meta = (BindWidget))
		UListView* mServerList;

public:
	UFUNCTION()
		void CreateServerInfoWidget(const int32 inServerID, const FString& inName, const FString& inState, const int32 inCharacterCount);

private:
	UPROPERTY()
	TSubclassOf<UUserWidget> mButtonWidget;

	UPROPERTY()
		bool mIsBackGround;
};
