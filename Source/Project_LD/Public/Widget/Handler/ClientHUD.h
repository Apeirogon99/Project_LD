// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ClientHUD.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(CLIENT_HUD, Log, All);

#define HUD_LOG(Format, ...) UE_LOG(CLIENT_HUD, Warning, TEXT("[%s] %s"), __FUNCTION__ ,*FString::Printf(Format, ##__VA_ARGS__))

class UUserWidget;

/**
 * 
 */
UCLASS()
class PROJECT_LD_API AClientHUD : public AHUD
{
	GENERATED_BODY()

public:
	AClientHUD();

	UFUNCTION(BlueprintCallable)
	UUserWidget*	GetWidgetFromName(const FString& inWidgetName);

	UFUNCTION(BlueprintCallable)
	void			ShowWidgetFromName(const FString& inWidgetName);

	UFUNCTION(BlueprintCallable)
	void			CleanWidgetFromName(const FString& inWidgetName);

	UFUNCTION(BlueprintCallable)
	void			CollapsedWidgetFromName(const FString& inWidgetName);

	UFUNCTION(BlueprintCallable)
	void			SelfHitTestInvisibleWidgetFromName(const FString& inWidgetName);

	UFUNCTION(BlueprintCallable)
	void			AllCleanWidget();

	UFUNCTION(BlueprintCallable)
	void			AllCollapsedWidget();

	UFUNCTION(BlueprintCallable)
	void			AllSelfHitTestInvisibleWidget();

	UFUNCTION(BlueprintCallable)
	void			AllCollapsedButOneWidget(const FString& inWidgetName);

	UFUNCTION(BlueprintCallable)
	void			AllSelfHitTestInvisibleButOneWidget(const FString& inWidgetName);

	UFUNCTION(BlueprintCallable)
	bool			IsInit();

protected:
	virtual void BeginPlay() override;
	virtual void DrawHUD() override;

public:
	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<UUserWidget>> mCommonUIWidgets;

	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<UUserWidget>> mAllUIWidgets;

private:
	TArray<UUserWidget*>	mWidgets;
	TArray<FString>			mWidgetNames;
	bool					mIsInit;
};
