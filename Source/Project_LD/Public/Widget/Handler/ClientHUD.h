// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ClientHUD.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(CLIENT_HUD, Log, All);

#define HUD_LOG(Format, ...) UE_LOG(CLIENT_HUD, Warning, TEXT("[%s] %s"), *FString("ClientHUD") ,*FString::Printf(Format, ##__VA_ARGS__))

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
	UUserWidget* GetWidgetFromName(const FString& inWidgetName);

	UFUNCTION(BlueprintCallable)
	void	ShowWidgetFromName(const FString& inWidgetName);

	UFUNCTION(BlueprintCallable)
	void	CleanWidgetFromName(const FString& inWidgetName);

	UFUNCTION(BlueprintCallable)
	bool	IsInit();

protected:
	UFUNCTION(BlueprintCallable)
	UUserWidget* GetWidgetInfo(const FString& inWidgetName, int32& outNumber);

	UFUNCTION(BlueprintCallable)
	void	CollapsedWidget(UUserWidget* inWidget);

	UFUNCTION(BlueprintCallable)
	void	SelfHitTestInvisibleWidget(UUserWidget* inWidget);

public:
	void	FadeOut();
	void	FadeIn();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void DrawHUD() override;

public:
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<UUserWidget>> mCommonUIWidgets;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<UUserWidget>> mAllUIWidgets;

	UPROPERTY(EditDefaultsOnly, Category = "Default")
	TSubclassOf<class UUserWidget> mFadeWidgetClass;
	class UW_Fade* mFadeWidget;

private:
	TArray<UUserWidget*>	mWidgets;
	TArray<FString>			mWidgetNames;
	bool					mIsInit;

	TArray<bool>			mUsedWidgets;
};
