// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Controller/MovementController.h"
#include "PC_Game.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_LD_API APC_Game : public AMovementController
{
	GENERATED_BODY()

public:
	APC_Game();
	~APC_Game();

public:
	void SwitchUIMode();
	void SwitchInventory();
	void SwitchChat();
	void SwitchSkillTree();
	void SwitchFriend();
	void SwitchParty();

	void UseSkill_Q_Pressed();
	void UseSkill_Q_Released();
	void UseSkill_W_Pressed();
	void UseSkill_W_Released();
	void UseSkill_E_Pressed();
	void UseSkill_E_Released();
	void UseSkill_R_Pressed();
	void UseSkill_R_Released();
	void UseSkill_Dash_Pressed();
	void UseSkill_Dash_Released();

public:
	virtual void BeginPlay() override;
	
public:
	virtual bool	OnRecvPacket(BYTE* buffer, const uint32 len) override;
	virtual bool	OnSend(int32 len) override;
	virtual bool	OnConnect() override;
	virtual bool	OnDisconnect() override;
	virtual bool	OnTick() override;

public:
	virtual void	OnPossess(APawn* InPawn) override;

protected:
	virtual void SetupInputComponent() override;
};
	