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
        mLichSkillClass.Add(ASkill_Rise::StaticClass());                               //0 애니메이션
        mLichSkillClass.Add(ASkill_RiseSkeleton::StaticClass());                //1 애니메이션 rise 스폰 (스폰 파티클 active)
        mLichSkillClass.Add(ASkill_RiseDarkSkeleton::StaticClass());        //2 애니메이션 rise 스폰 (스폰 파티클 active)
        mLichSkillClass.Add(ASkill_RiseDarkKnight::StaticClass());           //3 애니메이션 rise 스폰 (스폰 파티클이 있다면 active)
        mLichSkillClass.Add(ASkill_BlinkAttack::StaticClass());                 //4 애니메이션, 스폰 active 처음 reaction 캐릭터 뒤
        mLichSkillClass.Add(ASkill_BlinkStun::StaticClass());                     //5 애니메이션, 스폰 active 처음 reaction 캐릭터 뒤
        mLichSkillClass.Add(ASkill_SoulSpear::StaticClass());                     //6 스폰 (관호가 함)
        mLichSkillClass.Add(ASkill_SoulSpark::StaticClass());                     //7 스폰(active 애니메이션(기모으기), reaction 애니메이션(발사), 파티클 스폰)
        mLichSkillClass.Add(ASkill_SoulShackles::StaticClass());                //8 스폰(active 파티클 2초 , reaction 파티클 5초)(애니메이션 rise)
        mLichSkillClass.Add(ASkill_Explosion::StaticClass());                      //9 스폰(애니메이션은 rise) active 파티클소환
        mLichSkillClass.Add(ASkill_MultiCasting::StaticClass());                 //10 애니메이션 remote->rich->particle active
        mLichSkillClass.Add(ASkill_RealmOfDeath::StaticClass());              //11 스폰 (reaction 안개, deactive 안개 제거) 
        mLichSkillClass.Add(ASkill_OnslaughtOfShadows::StaticClass());   //12 애니메이션 rise 스폰(appear 바닥3초, reaction 광선발사) 
        mLichSkillClass.Add(ASkill_LifeVessel::StaticClass());                    //13 애니메이션 rise 스폰(appear 스폰 파티클)
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
