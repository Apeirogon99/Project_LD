// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NetworkGameMode.generated.h"

/**
 * 
 */
DECLARE_DELEGATE_OneParam(FConnectCallBack, bool)
DECLARE_DELEGATE_OneParam(FDisconnectCallBack, bool)
DECLARE_DELEGATE_OneParam(FPossessCallBack, bool)
DECLARE_DELEGATE_OneParam(FUnPossessCallBack, bool)

class ANetworkController;
class AClientHUD;
using NetworkControllerPtr = TSharedPtr<class ANetworkController>;

UCLASS(Abstract)
class PROJECT_LD_API ANetworkGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ANetworkGameMode();
	virtual ~ANetworkGameMode();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void BeginNetwork();

public:
	UFUNCTION(BlueprintCallable, Category = "Network")
	bool RequestConnectServer(const FString& inIpAddr, const int32 inPort);

	UFUNCTION(BlueprintCallable, Category = "Network")
	bool RequestKeepConnectServer(const FString& inIpAddr, const int32 inPort);

	UFUNCTION(BlueprintCallable, Category = "Network")
	bool RequestDisconnectServer();

	UFUNCTION(BlueprintCallable, Category = "Network")
	bool RequestPossessController();

	UFUNCTION(BlueprintCallable, Category = "Network")
	bool RequestUnPossessController();

	UFUNCTION(BlueprintCallable, Category = "Network")
	void RequestTravelLevel(const FString& inLevel);

	UFUNCTION(BlueprintCallable, Category = "Network")
	void RequestTravelServer(const FString& inLevel);

	UFUNCTION(BlueprintCallable, Category = "Network")
	bool RequestExitGame();

public:
	UFUNCTION(BlueprintCallable, Category = "Utils")
	bool IsNetworkInit();

public:
	UFUNCTION()
	void ProcessClientHUD(bool inInitHUD);

	UFUNCTION()
	void ProcessConnect(bool inIsConnect);

	UFUNCTION()
	void ProcessDisconnect(bool inIsDisConnect);

	UFUNCTION()
	void PossessNetwork(bool inIsPossess);

	UFUNCTION()
	void UnPossessNetwork(bool inIsUnPossess);

	UFUNCTION()
	void ProcessOpenLevel(const FString& inLevel);

	UFUNCTION()
	void ShowNetworkNotification(const FString& inNotification);

public:

public:
	DECLARE_EVENT_OneParam(ANetworkGameMode, FTravel, const FString&);

public:
	UPROPERTY(EditDefaultsOnly, Category = "Default")
	TSubclassOf<class UUserWidget> mServerLoadingWidgetClass;
	class UUserWidget* mServerLoadingWidget;
	
	UPROPERTY(EditDefaultsOnly, Category = "Default")
	TSubclassOf<class UUserWidget> mNetworkNotificationWidgetClass;
	class UW_Notification* mNetworkNotificationWidget;

	UPROPERTY(EditDefaultsOnly, Category = "Default")
	TSubclassOf<class AHUD> mDefaultHUDClass;

protected:
	AClientHUD* mClientHUD;

private:
	FConnectCallBack	mConnectCallBack;
	FDisconnectCallBack mDisConnectCallBack;
	FPossessCallBack	mPossessCallBack;
	FUnPossessCallBack	mUnPossessCallBack;
	FTravel				mTravel;

	bool mIsHUD;
	bool mIsConnect;
	bool mIsPossess;
	FString mTravelLevel;
};
