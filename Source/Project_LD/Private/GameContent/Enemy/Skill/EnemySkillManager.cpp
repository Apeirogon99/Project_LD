// Fill out your copyright notice in the Description page of Project Settings.


#include "GameContent/Enemy/Skill/EnemySkillManager.h"

#include <GameContent/Enemy/E_Lich.h>
#include <GameContent/Enemy/E_DarkKnight.h>

#include <GameContent/Enemy/Skill/Lich/Skill_LifeVessel.h>
#include <GameContent/Enemy/Skill/Lich/Skill_BlinkAttack.h>
#include <GameContent/Enemy/Skill/Lich/Skill_BlinkStun.h>
#include <GameContent/Enemy/Skill/Lich/Skill_Explosion.h>
#include <GameContent/Enemy/Skill/Lich/Skill_MultiCasting.h>
#include <GameContent/Enemy/Skill/Lich/Skill_OnslaughtOfShadows.h>
#include <GameContent/Enemy/Skill/Lich/Skill_RealmOfDeath.h>
#include <GameContent/Enemy/Skill/Lich/Skill_Rise.h>
#include <GameContent/Enemy/Skill/Lich/Skill_RiseSkeleton.h>
#include <GameContent/Enemy/Skill/Lich/Skill_RiseDarkSkeleton.h>
#include <GameContent/Enemy/Skill/Lich/Skill_RiseDarkKnight.h>
#include <GameContent/Enemy/Skill/Lich/Skill_SoulShackles.h>
#include <GameContent/Enemy/Skill/Lich/Skill_SoulSpark.h>
#include <GameContent/Enemy/Skill/Lich/Skill_SoulSpear.h>

#include <GameContent/Enemy/Skill/DarkKnight/DarkKnight_Berserk.h>
#include <GameContent/Enemy/Skill/DarkKnight/DarkKnight_ChargedComboAttack.h>
#include <GameContent/Enemy/Skill/DarkKnight/DarkKnight_HandSwordSwipeAttack.h>
#include <GameContent/Enemy/Skill/DarkKnight/DarkKnight_RunningAttack.h>
#include <GameContent/Enemy/Skill/DarkKnight/DarkKnight_SwingAndSlamAttack.h>
#include <GameContent/Enemy/Skill/DarkKnight/DarkKnight_SwingAttack.h>
#include <GameContent/Enemy/Skill/DarkKnight/DarkKnight_UppercutAttack.h>
#include <GS_Game.h>

#define MINLICHSKILLCODE 5
#define MAXLICHSKILLCODE 18
#define MINDARKKNIGHTSKILLCODE 19
#define MAXDARKKNIGHTSKILLCODE 25

UEnemySkillManager::UEnemySkillManager()
{
}

UEnemySkillManager::~UEnemySkillManager()
{
}

void UEnemySkillManager::Init()
{
    {
        mLichSkillClass.Add(ASkill_Rise::StaticClass());                               //0 �ִϸ��̼�
        mLichSkillClass.Add(ASkill_RiseSkeleton::StaticClass());                //1 �ִϸ��̼� rise ���� (���� ��ƼŬ active)
        mLichSkillClass.Add(ASkill_RiseDarkSkeleton::StaticClass());        //2 �ִϸ��̼� rise ���� (���� ��ƼŬ active)
        mLichSkillClass.Add(ASkill_RiseDarkKnight::StaticClass());           //3 �ִϸ��̼� rise ���� (���� ��ƼŬ�� �ִٸ� active)
        mLichSkillClass.Add(ASkill_BlinkAttack::StaticClass());                 //4 �ִϸ��̼�, ���� active ó�� reaction ĳ���� ��
        mLichSkillClass.Add(ASkill_BlinkStun::StaticClass());                     //5 �ִϸ��̼�, ���� active ó�� reaction ĳ���� ��
        mLichSkillClass.Add(ASkill_SoulSpear::StaticClass());                     //6 ���� (��ȣ�� ��)
        mLichSkillClass.Add(ASkill_SoulSpark::StaticClass());                     //7 ����(active �ִϸ��̼�(�������), reaction �ִϸ��̼�(�߻�), ��ƼŬ ����)
        mLichSkillClass.Add(ASkill_SoulShackles::StaticClass());                //8 ����(active ��ƼŬ 2�� , reaction ��ƼŬ 5��)(�ִϸ��̼� rise)
        mLichSkillClass.Add(ASkill_Explosion::StaticClass());                      //9 ����(�ִϸ��̼��� rise) active ��ƼŬ��ȯ
        mLichSkillClass.Add(ASkill_MultiCasting::StaticClass());                 //10 �ִϸ��̼� remote->rich->particle active
        mLichSkillClass.Add(ASkill_RealmOfDeath::StaticClass());              //11 ���� (reaction �Ȱ�, deactive �Ȱ� ����) 
        mLichSkillClass.Add(ASkill_OnslaughtOfShadows::StaticClass());   //12 �ִϸ��̼� rise ����(appear �ٴ�3��, reaction �����߻�) 
        mLichSkillClass.Add(ASkill_LifeVessel::StaticClass());                    //13 �ִϸ��̼� rise ����(appear ���� ��ƼŬ)
    }
    {
        mDarkKnightSkillClass.Add(ADarkKnight_RunningAttack::StaticClass());
        mDarkKnightSkillClass.Add(ADarkKnight_ChargedComboAttack::StaticClass());
        mDarkKnightSkillClass.Add(ADarkKnight_UppercutAttack::StaticClass());
        mDarkKnightSkillClass.Add(ADarkKnight_SwingAttack::StaticClass());
        mDarkKnightSkillClass.Add(ADarkKnight_SwingAndSlamAttack::StaticClass());
        mDarkKnightSkillClass.Add(ADarkKnight_HandSwordSwipeAttack::StaticClass());
        mDarkKnightSkillClass.Add(ADarkKnight_Berserk::StaticClass());
    }
}

void UEnemySkillManager::InputActiveSkillData(UWorld* InWorld, AActor* InActor, const int32 InSkillID, FVector InLocation, FRotator InRotator, const int64 InobjectID, const int64 InremoteID)
{
    AGS_Game* gameState = Cast<AGS_Game>(InWorld->GetGameState());
    if (nullptr == gameState)
    {
        return;
    }

    if ((MINLICHSKILLCODE <= InSkillID) && (InSkillID <= MAXLICHSKILLCODE))
    {
        AE_Lich* actor = Cast<AE_Lich>(InActor);
        if (actor == nullptr)
        {
            return;
        }

        UClass* SkillClass = mLichSkillClass[InSkillID - MINLICHSKILLCODE];
           
        UE_LOG(LogTemp, Warning, TEXT("Active Skill Skill ID : %d //// Skill Class %s ///// "),InSkillID,*SkillClass->GetName());

        AActor* object = nullptr;

        switch (InSkillID - MINLICHSKILLCODE)
        {
        case 0:
            actor->PlayLichAnim(0);
            break;
        case 4:
            actor->PlayLichAnim(1);
            break;
        case 5:
            actor->PlayLichAnim(3);
            break;
        case 7:
            actor->PlayLichAnim(5);
            break;
        case 10:
            actor->PlayLichAnim(0);
            actor->ActiveMultiCastParticle();
            break;
        }

        switch (InSkillID - MINLICHSKILLCODE)
        {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 12:
        case 13:
            object = gameState->CreateGameObject(SkillClass, InLocation, InRotator, InobjectID);
            if (object && (object->GetClass()->ImplementsInterface(UEnemySkillInterface::StaticClass())))
            {
                auto InterfaceVariable = Cast<IEnemySkillInterface>(object);
                InterfaceVariable->mRemoteID = InremoteID;
                InterfaceVariable->ActiveSkill(InLocation, InRotator);
            }
            break;
        }
    }
    else if ((MINDARKKNIGHTSKILLCODE <= InSkillID) && (InSkillID <= MAXDARKKNIGHTSKILLCODE))
    {
        AE_DarkKnight* actor = Cast<AE_DarkKnight>(InActor);
        if (actor == nullptr)
        {
            return;
        }

        UClass* SkillClass = mDarkKnightSkillClass[InSkillID - MINDARKKNIGHTSKILLCODE];

        AActor* object = nullptr;
            //gameState->CreateGameObject(SkillClass, InLocation, InRotator, InobjectID);

        actor->PlayDarkKnightAnim(InSkillID - MINDARKKNIGHTSKILLCODE);

        /*
        if (object->GetClass()->ImplementsInterface(UEnemySkillInterface::StaticClass()))
        {
            auto InterfaceVariable = Cast<IEnemySkillInterface>(object);
            InterfaceVariable->ActiveSkill(InLocation, InRotator);
        }
        */
    }
    else
    {
        return;
    }
}

void UEnemySkillManager::InputReactionSkillData(UWorld* InWorld, AActor* InActor, const int32 InSkillID, FVector InLocation, FRotator InRotator, const int64 InobjectID, const int64 InremoteID)
{
    AGS_Game* gameState = Cast<AGS_Game>(InWorld->GetGameState());
    if (nullptr == gameState)
    {
        return;
    }

    if ((MINLICHSKILLCODE <= InSkillID) && (InSkillID <= MAXLICHSKILLCODE))
    {
        AE_Lich* actor = Cast<AE_Lich>(InActor);
        if (actor == nullptr)
        {
            return;
        }

        UClass* SkillClass = mLichSkillClass[InSkillID - MINLICHSKILLCODE];

        UE_LOG(LogTemp, Warning, TEXT("Reaction Skill Skill ID : %d //// Skill Class %s ///// "), InSkillID, *SkillClass->GetName());

        AActor* object = nullptr;

        switch (InSkillID - MINLICHSKILLCODE)
        {
        case 4:
            actor->PlayLichAnim(2);
            break;
        case 5:
            actor->PlayLichAnim(4);
            break;
        case 7:
            actor->PlayLichAnim(6);
            break;
        }

        switch (InSkillID - MINLICHSKILLCODE)
        {
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 11:
        case 12:
            object = gameState->FindGameObject(InobjectID);
            if (object->GetClass()->ImplementsInterface(UEnemySkillInterface::StaticClass()))
            {
                auto InterfaceVariable = Cast<IEnemySkillInterface>(object);
                InterfaceVariable->mRemoteID = InremoteID;
                InterfaceVariable->ReactionSkill(InLocation, InRotator);
            }
            break;
        }
    }
    else if ((MINDARKKNIGHTSKILLCODE <= InSkillID) && (InSkillID <= MAXDARKKNIGHTSKILLCODE))
    {
        AE_DarkKnight* actor = Cast<AE_DarkKnight>(InActor);
        if (actor == nullptr)
        {
            return;
        }

        UClass* SkillClass = mDarkKnightSkillClass[InSkillID - MINDARKKNIGHTSKILLCODE];

        AActor* object = nullptr;
            //gameState->CreateGameObject(SkillClass, InLocation, InRotator, InobjectID);

        /*
        if (object->GetClass()->ImplementsInterface(UEnemySkillInterface::StaticClass()))
        {
            auto InterfaceVariable = Cast<IEnemySkillInterface>(object);
            InterfaceVariable->ReactionSkill(InLocation, InRotator);
        }
        */
    }
    else
    {
        return;
    }
}

void UEnemySkillManager::InputDeactiveSkillData(UWorld* InWorld, AActor* InActor, const int32 InSkillID, FVector InLocation, FRotator InRotator, const int64 InobjectID, const int64 InremoteID)
{
    AGS_Game* gameState = Cast<AGS_Game>(InWorld->GetGameState());
    if (nullptr == gameState)
    {
        return;
    }

    if ((MINLICHSKILLCODE <= InSkillID) && (InSkillID <= MAXLICHSKILLCODE))
    {
        AE_Lich* actor = Cast<AE_Lich>(InActor);
        if (actor == nullptr)
        {
            return;
        }

        UClass* SkillClass = mLichSkillClass[InSkillID - MINLICHSKILLCODE];

        UE_LOG(LogTemp, Warning, TEXT("Reaction Skill Skill ID : %d //// Skill Class %s ///// "), InSkillID, *SkillClass->GetName());

        AActor* object = nullptr;
        switch (InSkillID - MINLICHSKILLCODE)
        {
        case 12:
            object = gameState->CreateGameObject(SkillClass, InLocation, InRotator, InobjectID);
            if (object->GetClass()->ImplementsInterface(UEnemySkillInterface::StaticClass()))
            {
                auto InterfaceVariable = Cast<IEnemySkillInterface>(object);
                InterfaceVariable->mRemoteID = InremoteID;
                InterfaceVariable->DeactiveSkill(InLocation, InRotator);
            }
            break;
        }
    }
    else if ((MINDARKKNIGHTSKILLCODE <= InSkillID) && (InSkillID <= MAXDARKKNIGHTSKILLCODE))
    {
        AE_DarkKnight* actor = Cast<AE_DarkKnight>(InActor);
        if (actor == nullptr)
        {
            return;
        }

        UClass* SkillClass = mDarkKnightSkillClass[InSkillID - MINDARKKNIGHTSKILLCODE];

        AActor* object = nullptr;
        //gameState->CreateGameObject(SkillClass, InLocation, InRotator, InobjectID);

    /*
    if (object->GetClass()->ImplementsInterface(UEnemySkillInterface::StaticClass()))
    {
        auto InterfaceVariable = Cast<IEnemySkillInterface>(object);
        InterfaceVariable->ReactionSkill(InLocation, InRotator);
    }
    */
    }
    else
    {
        return;
    }

}
